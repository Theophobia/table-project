#include "StringType.h"
#include "../exception/ParseError.h"

StringType::StringType(const std::string & text) {
	this->text = text;
}

const std::string & StringType::getText() const {
	return text;
}

void StringType::setText(const std::string & text) {
	this->text = text;
}

//int StringType::getClassId() const {
//	return 0;
//}

void StringType::tryParse(const std::string & str) {
	if (str.size() < 2) {
		throw ParseError<StringType>("Minimum length not met");
	}
	
	if (str.front() != '"' || str.back() != '"') {
		throw ParseError<StringType>("String is not surrounded by quotes (\")");
	}
	
	const std::size_t start = 1;
	const std::size_t end = str.size() - 1;
	
	// Check for unescaped "
	for (std::size_t i = start; i < end; i++) {
		if (str[i] == '"' && str[i - 1] != '\\') {
			std::string msg = "Quotes (\") at string index "
							  + std::to_string(i)
							  + " are not escaped by back slash (\\)";
			throw ParseError<StringType>(msg);
		}
	}
	
	// str without the 2 quotes, hence size()-2
	text = str.substr(1, str.size() - 2);
}

std::string StringType::toString() const {
	return '"' + text + '"';
}
