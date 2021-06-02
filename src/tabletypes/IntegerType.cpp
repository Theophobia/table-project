#include "IntegerType.h"
#include "../exception/ParseError.h"

IntegerType::IntegerType(std::int64_t number) {
	this->number = number;
}

IntegerType::IntegerType(const IntegerType & other) {
	*this = other;
}

IntegerType & IntegerType::operator=(const IntegerType & other) {
	this->number = other.number;
	return *this;
}

IntegerType::IntegerType(IntegerType && other) noexcept {
	*this = std::move(other);
}

IntegerType & IntegerType::operator=(IntegerType && other) noexcept {
	this->number = other.number;
	
	other.number = 0;
	return *this;
}

std::int64_t IntegerType::getNumber() const {
	return number;
}

void IntegerType::setNumber(std::int64_t number) {
	this->number = number;
}

void IntegerType::tryParse(const std::string & str) {
	bool isNegative = false;
	std::int64_t tmp = 0;
	const std::size_t size = str.size();
	
	// Check for sign
	int i = 0;
	if (str[i] == '+') {
		i++;
		isNegative = false;
	}
	else if (str[i] == '-') {
		i++;
		isNegative = true;
	}
	
	// Loop over rest
	for (; i < size; i++) {
		if (!std::isdigit(str[i])) {
			throw ParseError<IntegerType>("Illegal character while parsing integer");
		}
		
		tmp = 10 * tmp + (str[i] - '0');
	}
	
	// Add negative sign if needed
	if (isNegative) {
		tmp = -tmp;
	}
	
	number = tmp;
}

std::string IntegerType::toString() const {
	return std::to_string(number);
}

bool IntegerType::operator==(const Type & t) const {
	const IntegerType * casted = dynamic_cast<const IntegerType *>(&t);
	
	if (casted == nullptr) {
		return false;
	}
	
	if (casted == this) {
		return true;
	}
	
	return this->getNumber() == casted->getNumber();
}
