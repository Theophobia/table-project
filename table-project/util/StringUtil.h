#pragma once

#include <string>

namespace TableProject::StringUtil {
	static bool isInteger(const std::string & s) {
		for (std::size_t i = 0; i < s.size(); i++) {
			char c = s[i];

			if (c == '-' && i == 0) {
				continue;
			}

			if (c >= '0' && c <= '9') {
				continue;
			}

			return false;
		}
		return true;
	}

	static bool isDouble(const std::string & s) {
		bool isPointFound = false;
		for (std::size_t i = 0; i < s.size(); i++) {
			char c = s[i];

			if (c == '-' && i == 0) {
				continue;
			}

			if (c == '.') {
				if (isPointFound) {
					// Multiple decimal points found
					return false;
				}
				else {
					isPointFound = true;
					continue;
				}
			}

			if (c >= '0' && c <= '9') {
				continue;
			}

			return false;
		}
		return true;
	}

	/**
	 * Convert string to int64
	 *
	 * @param s
	 * @param doCheckBeforehand Whether to check for validity before any conversion
	 * @return
	 *
	 * @throws std::invalid_argument If invalid string
	 */
	static std::int64_t toInt64(const std::string & s, bool doCheckBeforehand = false) {
		if (doCheckBeforehand) {
			if (!isInteger(s)) {
				throw std::invalid_argument("String is not integer");
			}
		}

		bool isNegative = false;
		std::int64_t result = 0;
		const std::size_t size = s.size();

		// Check for sign
		int i = 0;
		if (s[i] == '+') {
			i++;
			isNegative = false;
		}
		else if (s[i] == '-') {
			i++;
			isNegative = true;
		}

		// Loop over rest
		for (; i < size; i++) {
			if (!std::isdigit(s[i])) {
				throw std::invalid_argument("Illegal character while parsing integer");
			}

			result = 10 * result + (s[i] - '0');
		}

		// Add negative sign if needed
		if (isNegative) {
			result = -result;
		}

		return result;
	}

	/**
	 * Convert string to long double
	 *
	 * @param s
	 * @param doCheckBeforehand Whether to check for validity before any conversion
	 * @return
	 *
	 * @throws std::invalid_argument If invalid string
	 */
	static long double toLongDouble(const std::string & s, bool doCheckBeforehand = false) {
		if (doCheckBeforehand) {
			if (!isDouble(s)) {
				throw std::invalid_argument("String is not double");
			}
		}

		bool isNegative = false;
		long double result = 0;
		const std::size_t size = s.size();

		// Check for sign
		int i = 0;
		if (s[i] == '+') {
			i++;
			isNegative = false;
		}
		else if (s[i] == '-') {
			i++;
			isNegative = true;
		}

		// Parse whole part
		bool hasWholePart = false;
		for (; i < size; i++) {
			if (s[i] == '.') {
				i++;
				break;
			}

			if (!std::isdigit(s[i])) {
				throw std::invalid_argument("Illegal character while parsing floating point, nondigit in whole part");
			}

			result = 10 * result + (s[i] - '0');
			hasWholePart = true;
		}

		// Parse fractional part
		bool hasFractionalPart = false;
		long double magnitude = 0.1;
		for (; i < size; i++) {
			if (!std::isdigit(s[i])) {
				std::string errMsg;
				errMsg += "Illegal character while parsing floating point, nondigit in fractional part";
				throw std::invalid_argument(errMsg);
			}

			int digit = s[i] - '0';

			if (digit != 0) {
				result = result + magnitude * digit;
				hasFractionalPart = true;
			}

			magnitude /= 10;
		}

		// Check if has both whole and fractional part
		// ex: ".1", "1.0", "1.0000"
//		if (!hasWholePart) {
//			throw ParseError<DoubleType>("No whole part while parsing floating point");
//		}
		if (!hasFractionalPart) {
			throw std::invalid_argument("No fractional part while parsing floating point");
		}

		// Add negative sign if needed
		if (isNegative) {
			result = -result;
		}

		return result;
	}
}