#pragma once

#include <string>
#include <vector>
#include <table-project/util/VectorUtil.h>
#include <table-project/tabletypes/StringType.h>

/**
 * Contains functions for doing simple arithmetic with exponents, multiplication, division, addition, subtraction.
 */
namespace TableProject::Parser {

	static const std::vector<char> & getBinaryOperations() {
		static const std::vector<char> binOps = {'^', '*', '/', '+', '-'};
		return binOps;
	};

	static std::string computeSimpleExpression(const std::string & lhs, char op, const std::string & rhs) {
		static const std::vector<char> & binOps = getBinaryOperations();

		if (!TableProject::VectorUtil::contains(binOps, op)) {
			std::string errMsg;
			errMsg += "Operation is invalid, passed '";
			errMsg += op;
			errMsg += "' as operation";
			throw std::invalid_argument(errMsg);
		}

		std::shared_ptr<Type> result;
		switch (op) {
			case ('^'): {
				result = Type::fromString(lhs) ^ Type::fromString(rhs);
				break;
			}
			case ('*'): {
				result = Type::fromString(lhs) * Type::fromString(rhs);
				break;
			}
			case ('/'): {
				result = Type::fromString(lhs) / Type::fromString(rhs);
				break;
			}
			case ('+'): {
				result = Type::fromString(lhs) + Type::fromString(rhs);
				break;
			}
			case ('-'): {
				result = Type::fromString(lhs) - Type::fromString(rhs);
				break;
			}
			default: {
				std::string errMsg;
				errMsg += "Binary operations have been changed, but code has not been fully adjusted";
				throw std::runtime_error(errMsg);
			}
		}

		return result->toString();
	}

	static std::string parse(std::string s) {
		static const std::vector<char> & binOps = getBinaryOperations();

		std::vector<std::string> tokens;
		std::string buffer;

		// Remove whitespace in "s"
		// Keep track of removed whitespaces
		// for error logging
		std::size_t removedWhitespaces = 0;
		for (std::size_t i = 0; i < s.size(); i++) {
			if (s[i] != ' ') {
				buffer += s[i];
			}
			else {
				removedWhitespaces++;
			}
		}
		s = buffer;
		buffer.clear();

		// For every operation
		for (std::size_t binOpIndex = 0; binOpIndex < binOps.size(); binOpIndex++) {
			char currOp = binOps[binOpIndex];


			// Iterate over "s" to compute over and over "currOp"
			for (std::size_t sIndex = 0; sIndex < s.size(); sIndex++) {
				const std::size_t sSize = s.size(); // DEBUG

				if (s[sIndex] != currOp) {
					// Ignore everything except current operation
					continue;
				}

				// So we found our current operation
				// s[sIndex] == currOp
				// Start moving to start to get LHS's string
				std::string lhs;
				std::size_t opStart;
				bool isLHSDouble = false;
				bool isLHSNegative = false;

				for (opStart = sIndex; opStart > 0; opStart--) {
					// If we have a digit, we need to check if our number is negative
					// If it is, then we need to stop
					if (std::isdigit(s[opStart - 1])) {
						if (isLHSNegative) {
							break;
						}
						lhs = (s[opStart - 1] + lhs);
						continue;
					}

					// If we find a '-' we must keep
					// track if we find another one
					if (s[opStart - 1] == '-' && currOp != '^') {

						if (isLHSNegative) {
							// Error
							std::string errMsg;
							errMsg += "Found double negative sign at index ";
							errMsg += std::to_string(removedWhitespaces + opStart - 1);
							throw std::runtime_error(errMsg);
						}
						else {
							isLHSNegative = true;
							lhs = (s[opStart - 1] + lhs); // Also append '-'

							continue;
						}
					}

					// If we find '.' we must keep
					// track if we find another one
					if (s[opStart - 1] == '.') {
						if (isLHSDouble) {
							// Error
							std::string errMsg;
							errMsg += "Found double dot sign at index ";
							errMsg += std::to_string(removedWhitespaces + opStart - 1);
							throw std::runtime_error(errMsg);
						}
						else {
							isLHSDouble = true;
							lhs = (s[opStart - 1] + lhs); // Also append '.'
							continue;
						}
					}

					// Check if end of number character sequence
					if (TableProject::VectorUtil::contains(binOps, s[opStart - 1])) {
						// Now index "opStart-1" has an operation
						// So index "opStart" is the start of the LHS of the operation
						break;
					}
				}

				bool lhsEmpty = lhs.empty();
				if (lhsEmpty) {
					continue;
				}

				// Found start of the operation, namely "opStart"
				// Now we need to find the end

				std::string rhs;
				std::size_t opEnd;
				bool isRHSDouble = false;

				for (opEnd = sIndex + 1; opEnd < s.size(); opEnd++) {
					// Nothing special if we have a digit,
					// append it and keep going
					if (std::isdigit(s[opEnd])) {
						rhs += s[opEnd];
						continue;
					}

					// If we find a '-' it must be at the start of the iteration
					// in order for it to be appended
					if (s[opEnd] == '-' && opEnd == sIndex + 1) {
						rhs += s[opEnd];
						continue;
					}

					// If we find '.' we must keep
					// track if we find another one
					if (s[opEnd] == '.') {
						if (isRHSDouble) {
							// Error
							std::string errMsg;
							errMsg += "Found double dot sign at index ";
							errMsg += std::to_string(removedWhitespaces + opEnd); // Might be incorrect
							throw std::runtime_error(errMsg);
						}
						else {
							isRHSDouble = true;
							rhs = s[opEnd]; // Also append '.'
							continue;
						}
					}

					// Check if end of number character sequence
					if (TableProject::VectorUtil::contains(binOps, s[opEnd])) {
						// Now index "opEnd" has an operation
						// So index "opEnd - 1" is the end of the RHS of the operation
						break;
					}
				}

				bool rhsEmpty = rhs.empty();
				if (rhsEmpty) {
					continue;
				}

				// Check if LHS and RHS are correctly formed numbers
				std::shared_ptr<Type> lhsPtr;
				std::shared_ptr<Type> rhsPtr;
				try {
					lhsPtr = Type::fromString(lhs);
				}
				catch (std::exception & e) {
					throw std::runtime_error("LHS number could not be parsed");
				}
				try {
					rhsPtr = Type::fromString(rhs);
				}
				catch (std::exception & e) {
					throw std::runtime_error("RHS number could not be parsed");
				}

				// Compute the operation
				// "sIndex" is index of operation
				const std::string lhsString = s.substr(opStart, sIndex - opStart);
				const std::string rhsString = s.substr(sIndex + 1, opEnd - sIndex - 1);
				std::string operationResult = computeSimpleExpression(lhsString, currOp, rhsString);

				if (operationResult == StringType::getError().toString()) {
					return operationResult;
				}

				std::string sStart = s.substr(0, opStart - 0);
				std::string sEnd = s.substr(opEnd);

				// Restructure "s"
				s = sStart + operationResult + sEnd;

				// Try to find a computation of current operation over again
				// sIndex++ makes this 0
				sIndex = -1;
			}
			// End of "s" iteration
		}
		// End of operation iteration

		return s;
	}
}
