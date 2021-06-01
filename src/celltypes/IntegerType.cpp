#include "IntegerType.h"
#include "../exception/ParseError.h"

IntegerType::IntegerType(std::int64_t number) {
	this->number = number;
}

std::int64_t IntegerType::getNumber() const {
	return number;
}

void IntegerType::setNumber(std::int64_t number) {
	this->number = number;
}

//int IntegerType::getClassId() const {
//	return -1240479155001108647;
//}

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