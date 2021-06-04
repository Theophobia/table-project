#include <table-project/tabletypes/FormulaType.h>

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
	this->formula = other.formula;
	return *this;
}

FormulaType::FormulaType(FormulaType && other) noexcept {
	*this = std::move(other);
}

FormulaType & FormulaType::operator=(FormulaType && other) noexcept {
	this->formula = std::move(other.formula);
	return *this;
}
void FormulaType::tryParse(const std::string & str) {

}

std::string FormulaType::toString() const {
	return std::string();
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

void FormulaType::calculate(const Table & table) {
	delete obj;
	
}
