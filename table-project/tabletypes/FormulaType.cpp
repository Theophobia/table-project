#include <sstream>
#include <memory>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/math/Operators.h>

bool FormulaType::isOperationChar(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
		return true;
	}
	return false;
}

bool FormulaType::isOperationChar(const std::string & s) {
	if (s.size() != 1) {
		return false;
	}
	return FormulaType::isOperationChar(s[0]);
}

std::deque<std::string> FormulaType::tokeniseFormula(const std::string & s) {
	std::deque<std::string> tokens;
	std::string buffer;
	
	for (std::size_t i = 0; i < s.size(); i++) {
		char c = s[i];

//		if (c == '-' && isOperationChar(buffer)) {
//			tokens.push_back(buffer);
//			buffer.clear();
//			buffer += c;
//			continue;
//		}
		
		if (isOperationChar(c)) {
			if (buffer.empty()) {
				if (c == '-' && isOperationChar(tokens[tokens.size() - 1])) {
					buffer += c;
					continue;
				}
				else {
					throw std::invalid_argument(
						"Formula contains error, unexpected character at position " + std::to_string(i)
					);
				}
			}
			
			tokens.push_back(buffer);
			buffer.clear();
			
			tokens.push_back(std::string() + c);
//			buffer += c;
			continue;
		}
		
		if (std::isdigit(c)) {
			buffer += c;
			continue;
		}
		
		throw std::invalid_argument("Unexpected character at position " + std::to_string(i));
	}
	
	if (isOperationChar(buffer)) {
		throw std::invalid_argument("Expected argument after operation at end of formula");
	}
	
	if (!buffer.empty()) {
		tokens.push_back(buffer);
	}
	
	return tokens;
}

void FormulaType::calculate(const Table & table, std::size_t thisRow, std::size_t thisCol, int depth) {
	delete obj;
	obj = nullptr;
	
	std::ostringstream oss;
	for (std::size_t i = 0; i < formula.size(); i++) {
		// Check for operations
		if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^') {
			if (i == formula.size() - 1) {
				// Missing operand as operation is last character
				obj = new StringType("#ERROR");
				return;
			}
			
			oss << formula[i];
		}
		
		// Check for constants
		else if (std::isdigit(formula[i])) {
			oss << formula[i];
		}
		
		// Check for cell references
		else if (std::isalpha(formula[i])) {
			if (i == formula.size() - 1) {
				// Incomplete cell reference
				obj = new StringType("#ERROR");
				return;
			}
			
			std::size_t rowNumber = 0;
			
			// Read integer after column char
			std::size_t j;
			for (j = i + 1; j < formula.size(); j++) {
				if (std::isdigit(formula[j])) {
					rowNumber = 10 * rowNumber + (formula[j] - '0');
				}
				else {
					break;
				}
			}
			std::size_t columnNumber = 1 + (std::toupper(formula[i]) - 'A');
			
			// Recursion check
			if (thisRow == rowNumber && thisCol == columnNumber) {
				obj = new StringType("#ERROR");
				return;
			}
			
			// Set to last char of cell reference,
			// because i++ from loop puts it on relevant chars
			i = j - 1;
			
			// Append element
			const Type & elem = table.get(rowNumber - 1, columnNumber - 1);
			
			const FormulaType * maybeFormulaType = dynamic_cast<const FormulaType *>(&elem);
			if (maybeFormulaType != nullptr) {
				oss << maybeFormulaType->getCalculatedValue(table, rowNumber - 1, columnNumber - 1, depth - 1);
			}
			else {
				oss << table.get(rowNumber - 1, columnNumber - 1);
			}
//			std::string s(oss.str());
//			s = oss.str();
//
		}
	}
	
	auto arr = tokeniseFormula(oss.str());
	
	const char operations[5] = {'^', '*', '/', '+', '-'};
	const std::size_t operationsCount = 5;
	
	for (std::size_t stage = 0; stage < operationsCount; stage++) {
		for (std::size_t i = 0; i < arr.size(); i++) {
			char c = arr[i][0];
			if (c == operations[stage]) {
				if (i < 1 || i > arr.size() - 1) {
					throw std::invalid_argument("Improper c string");
				}
				const std::string & leftStr = arr[i - 1];
				const std::string & rightStr = arr[i + 1];
				
				std::shared_ptr<Type> leftPtr = std::shared_ptr<Type>(Type::fromString(leftStr.c_str()));
				std::shared_ptr<Type> rightPtr = std::shared_ptr<Type>(Type::fromString(rightStr.c_str()));
				
				if (leftPtr->getClass() != IntegerType().getClass() && leftPtr->getClass() != DoubleType().getClass()) {
					throw std::invalid_argument("Left string is not number");
				}
				
				if (rightPtr->getClass() != IntegerType().getClass()
					&& rightPtr->getClass() != DoubleType().getClass()) {
					throw std::invalid_argument("Right string is not number");
				}
				
				switch (stage) {
					case 0: {
						arr.at(i + 1) = (leftPtr ^ rightPtr)->toString();
						break;
					}
					case 1: {
						arr.at(i + 1) = (leftPtr * rightPtr)->toString();
						break;
					}
					case 2: {
						arr.at(i + 1) = (leftPtr / rightPtr)->toString();
						break;
					}
					case 3: {
						arr.at(i + 1) = (leftPtr + rightPtr)->toString();
						break;
					}
					case 4: {
						arr.at(i + 1) = (leftPtr - rightPtr)->toString();
						break;
					}
				}
				arr.erase(arr.begin() + i - 1, arr.begin() + i + 1);
				
				i = 0; // reset to start
			}
			
		}
	}
	
	if (arr.size() != 1) {
		throw std::runtime_error("Unexpected error, could not process formula");
	}
	
	obj = Type::fromString(arr[0].c_str());
}

FormulaType::FormulaType(const char * str) {
	this->formula = str;
}

FormulaType::FormulaType(const std::string & str) {
	this->formula = str;
}

FormulaType::~FormulaType() {
	delete obj;
}

FormulaType::FormulaType(const FormulaType & other) {
	*this = other;
}

FormulaType & FormulaType::operator=(const FormulaType & other) {
	if (this == &other) {
		return *this;
	}
	
	this->formula = other.formula;
	
	delete this->obj;
	this->obj = nullptr;
	if (other.obj != nullptr) {
		this->obj = Type::createCopy(*other.obj);
	}
	
	return *this;
}

FormulaType::FormulaType(FormulaType && other) noexcept {
	*this = std::move(other);
}

FormulaType & FormulaType::operator=(FormulaType && other) noexcept {
	if (this == &other) {
		return *this;
	}
	
	this->formula = std::move(other.formula);
	
	delete this->obj;
	this->obj = other.obj;
	
	return *this;
}

void FormulaType::tryParse(const std::string & str) {

}

std::string FormulaType::toString() const {
	return formula;
}

std::string FormulaType::toCSV() const {
	return "=" + formula;
}

std::string FormulaType::getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol, int depth) const {
	if (this->obj == nullptr) {
		throw std::runtime_error("Formula cannot be computed");
	}
	return this->obj->toString();
}

std::string FormulaType::getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol, int depth) {
	if (obj == nullptr) {
		calculate(table, thisRow, thisCol, depth);
	}
	
	return this->obj->toString();
}

bool FormulaType::operator==(const Type & t) const {
	const FormulaType * casted = dynamic_cast<const FormulaType *>(&t);
	
	if (casted == nullptr) {
		return false;
	}
	
	if (casted == this) {
		return true;
	}
	
	return this->formula == casted->formula; // TODO: Check obj
}

const std::string & FormulaType::getClass() const {
	static const std::string className = "FormulaType";
	return className;
}
