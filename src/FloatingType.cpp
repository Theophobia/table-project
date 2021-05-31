#include "FloatingType.h"

FloatingType::FloatingType(long double number) {
	this->number = number;
}

long double FloatingType::getNumber() const {
	return number;
}

void FloatingType::setNumber(long double number) {
	this->number = number;
}

long FloatingType::getClassId() const {
	return 756064317340920913;
}

void FloatingType::tryParse(const std::string & str) {
	bool isNegative = false;
	long double tmp = 0;
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
	
	// Parse whole part
	bool hasWholePart = false;
	for (; i < size; i++) {
		if (str[i] == '.') {
			i++;
			break;
		}
		
		if (!std::isdigit(str[i])) {
			throw std::runtime_error("Illegal character while parsing floating point, nondigit in whole part");
		}
		
		tmp = 10 * tmp + (str[i] - '0');
		hasWholePart = true;
	}
	
	// Parse fractional part
	bool hasFractionalPart = false;
	long double magnitude = 0.1;
	for (; i < size; i++) {
		if (!std::isdigit(str[i])) {
			throw std::runtime_error("Illegal character while parsing floating point, nondigit in fractional part");
		}
		
		int digit = str[i] - '0';
		
		if (digit != 0) {
			tmp = tmp + magnitude * digit;
			hasFractionalPart = true;
		}
		
		magnitude /= 10;
	}
	
	// Check if has both whole and fractional part
	// ex: ".1", "1.0", "1.0000"
	if (!hasWholePart) {
		throw std::invalid_argument("No whole part while parsing floating point");
	}
	if (!hasFractionalPart) {
		throw std::invalid_argument("No fractional part while parsing floating point");
	}
	
	// Add negative sign if needed
	if (isNegative) {
		tmp = -tmp;
	}
	
	number = tmp;
}

std::string FloatingType::toString() const {
	return std::to_string(number);
}
