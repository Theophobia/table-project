#include <sstream>
#include <deque>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>

void FormulaType::calculate(const Table & table, std::size_t thisRow, std::size_t thisCol) {
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
				oss << maybeFormulaType->getCalculatedValue(table, rowNumber - 1, columnNumber - 1);
			}
			else {
				oss << table.get(rowNumber - 1, columnNumber - 1);
			}
//			std::string s(oss.str());
//			s = oss.str();
//
		}
	}
	
	obj = new StringType(oss.str());
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

std::string FormulaType::getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol) const {
	if (this->obj == nullptr) {
		throw std::runtime_error("Formula cannot be computed");
	}
	return this->obj->toString();
}

std::string FormulaType::getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol) {
	if (obj == nullptr) {
		calculate(table, thisRow, thisCol);
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
