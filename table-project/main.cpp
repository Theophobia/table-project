#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>s
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/math/Operators.h>


void createPrintAndSaveTable() {
	Table t;
	
	t.put(0, 0, FormulaType("D2+D4"));
	t.put(3, 3, IntegerType(123));
	t.put(1, 2, StringType("asdasd"));
	t.put(1, 3, DoubleType(123.4));
	
	const Type & it = t.get(3, 3);
	std::cout << t << '\n';
	
	// Real men don't check if file is opened properly
	std::ofstream fileOut("tmp.csv", std::ios::out | std::ios::trunc);
	fileOut << t.toCSV() << std::endl;
	fileOut.close();
	
}

void asd() {
	Table t;
	t.put(0, 0, FormulaType("B1+D1^E1-F1"));
	t.put(0, 1, FormulaType("C1+D1+10"));
	t.put(0, 2, IntegerType(1));
	t.put(0, 3, IntegerType(2));
	t.put(0, 4, IntegerType(3));
	t.put(0, 5, IntegerType(4));
	std::cout << t;

//	std::ofstream fileOut("tmp.csv", std::ios::out | std::ios::trunc);
//	fileOut << t.toCSV() << std::endl;
//	fileOut.close();
}

bool isOperationChar(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
		return true;
	}
	return false;
}

bool isOperationChar(const std::string & s) {
	if (s.size() != 1) {
		return false;
	}
	return isOperationChar(s[0]);
}

std::deque<std::string> tokeniseFormula(const std::string & s) {
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

int main() {
	asd();
//	asd();
//
//	auto arr = tokeniseFormula("123+-456+10+456^-2");
//	for (std::size_t i = 0; i < arr.size(); i++) {
//		std::cout << arr[i] << ' ';
//	}
//
//	const char operations[5] = {'^', '*', '/', '+', '-'};
//	const std::size_t operationsCount = 5;
//
//	for (std::size_t stage = 0; stage < operationsCount; stage++) {
//		for (std::size_t i = 0; i < arr.size(); i++) {
//			char c = arr[i][0];
//			if (c == operations[stage]) {
//				if (i < 1 || i > arr.size() - 1) {
//					throw std::invalid_argument("Improper c string");
//				}
//				const std::string & leftStr = arr[i - 1];
//				const std::string & rightStr = arr[i + 1];
//
//				std::shared_ptr<Type> leftPtr = std::shared_ptr<Type>(Type::fromString(leftStr.c_str()));
//				std::shared_ptr<Type> rightPtr = std::shared_ptr<Type>(Type::fromString(rightStr.c_str()));
//
//				if (leftPtr->getClass() != IntegerType().getClass() && leftPtr->getClass() != DoubleType().getClass()) {
//					throw std::invalid_argument("Left string is not number");
//				}
//
//				if (rightPtr->getClass() != IntegerType().getClass()
//					&& rightPtr->getClass() != DoubleType().getClass()) {
//					throw std::invalid_argument("Right string is not number");
//				}
//
//				switch (stage) {
//					case 0: {
//						arr.at(i + 1) = (leftPtr ^ rightPtr)->toString();
//						break;
//					}
//					case 1: {
//						arr.at(i + 1) = (leftPtr * rightPtr)->toString();
//						break;
//					}
//					case 2: {
//						arr.at(i + 1) = (leftPtr / rightPtr)->toString();
//						break;
//					}
//					case 3: {
//						arr.at(i + 1) = (leftPtr + rightPtr)->toString();
//						break;
//					}
//					case 4: {
//						arr.at(i + 1) = (leftPtr - rightPtr)->toString();
//						break;
//					}
//				}
//				arr.erase(arr.begin() + i - 1, arr.begin() + i + 1);
//
//				i = 0; // reset to start
//			}
//
//		}
//	}
//
//	if (arr.size() != 1) {
//		throw std::runtime_error("Unexpected error, could not process formula");
//	}
//
//	std::shared_ptr<Type> leftPtr = std::shared_ptr<Type>(Type::fromString(arr[0].c_str()));
	
	
	return 0;
}