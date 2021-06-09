#include <memory>
#include <sstream>
#include <table-project/math/Operators.h>
#include <table-project/table/Table.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/math/Parser.h>

namespace TableProject {

	void FormulaType::calculate(Table & table, std::size_t thisRow, std::size_t thisCol, int depth) {

		std::ostringstream oss;
		for (std::size_t i = 0; i < formula.size(); i++) {
			// Check for operations
			if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/' || formula[i] == '^') {
				if (i == formula.size() - 1) {
					// Missing operand as operation is last character
					obj = std::make_unique<StringType>(StringType::getError());
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
					obj = std::make_unique<StringType>(StringType::getError());
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
				std::size_t columnNumber = 1 + Table::columnLetterToIndex(formula[i]);

				// Recursion check
				if (thisRow == rowNumber && thisCol == columnNumber) {
					obj = std::make_unique<StringType>(StringType::getError());
					return;
				}

				// Set to last char of cell reference,
				// because i++ from loop puts it on relevant chars
				i = j - 1;

				// Get referred element
				Type * elem = nullptr;
				try {
					elem = &table.get(rowNumber - 1, columnNumber - 1);
				}
				catch (std::exception &) {
					elem = nullptr;
				}

				// If error occurred cell is probably out of bounds
				if (elem == nullptr) {
					oss << '0';
					continue;
				}

				auto * maybeStringType = dynamic_cast<StringType *>(elem);
				auto * maybeFormulaType = dynamic_cast<FormulaType *>(elem);

				// Handle string to integer/double and formula calculation
				if (maybeStringType) {
					if (maybeStringType->isIntegerCastable()) {
						const IntegerType & it = (const IntegerType) *maybeStringType;
						oss << std::to_string(it.getNumber());
					}
					else if (maybeStringType->isDoubleCastable()) {
						const DoubleType & dt = (const DoubleType) *maybeStringType;
						oss << std::to_string(dt.getNumber());
					}
					else {
						oss << '0';
					}
				}
				else if (maybeFormulaType) {
					oss << maybeFormulaType->getCalculatedValue(table, rowNumber - 1, columnNumber - 1, depth - 1);
				}
				else {
					// IntegerType and DoubleType are
					// trivially printable as integer or double
					oss << table.get(rowNumber - 1, columnNumber - 1);
				}
			}
			// End check for cell reference
		}
		// End of conversion to only numbers/arithmetic string

		std::string result = TableProject::Parser::parse(oss.str());

		obj = Type::fromString(result);
	}

	FormulaType::FormulaType(const char * str) {
		this->formula = str;
	}

	FormulaType::FormulaType(const std::string & str) {
		this->formula = str;
	}

	const std::string & FormulaType::getFormula() const {
		return formula;
	}

	void FormulaType::tryParse(const std::string & str) {
		if (str.empty()) {
			throw std::invalid_argument("Formula cannot be empty");
		}

		if (str[0] != '=') {
			throw std::invalid_argument("Formula must start with '='");
		}

		this->formula = str.substr(1);
	}

	std::string FormulaType::toString() const {
		if (this->obj == nullptr) {
			throw std::runtime_error("Value is null");
		}
		return this->obj->toString();
	}

	std::string FormulaType::toCSV() const {
		return "=" + formula;
	}

	std::string FormulaType::getCalculatedValue() const {
		if (this->obj == nullptr) {
			throw std::runtime_error("Formula cannot be computed");
		}
		return this->obj->toString();
	}

	std::string FormulaType::getCalculatedValue(Table & table, std::size_t thisRow, std::size_t thisCol, int depth) {
		if (this->obj == nullptr) {
			calculate(table, thisRow, thisCol, depth);
		}

		auto a = this->obj;
		auto b = a->toString();

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

		// Do not check object, as it does not matter
		return this->formula == casted->formula;
	}

	const std::string & FormulaType::getClass() const {
		static const std::string className = "FormulaType";
		return className;
	}
}