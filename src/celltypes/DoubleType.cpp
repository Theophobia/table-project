#include "DoubleType.h"
#include "../exception/ParseError.h"

DoubleType::DoubleType(long double number) {
	this->number = number;
}

long double DoubleType::getNumber() const {
	return number;
}

void DoubleType::setNumber(long double number) {
	this->number = number;
}

//int DoubleType::getClassId() const {
//	return 756064317340920913;
//}

void DoubleType::tryParse(const std::string & str) {
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
			throw ParseError<DoubleType>("Illegal character while parsing floating point, nondigit in whole part");
		}
		
		tmp = 10 * tmp + (str[i] - '0');
		hasWholePart = true;
	}
	
	// Parse fractional part
	bool hasFractionalPart = false;
	long double magnitude = 0.1;
	for (; i < size; i++) {
		if (!std::isdigit(str[i])) {
			throw ParseError<DoubleType>("Illegal character while parsing floating point, nondigit in fractional part");
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
		throw ParseError<DoubleType>("No whole part while parsing floating point");
	}
	if (!hasFractionalPart) {
		throw ParseError<DoubleType>("No fractional part while parsing floating point");
	}
	
	// Add negative sign if needed
	if (isNegative) {
		tmp = -tmp;
	}
	
	number = tmp;
}

std::string DoubleType::toString() const {
	return std::to_string(number);
}
