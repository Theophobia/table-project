#pragma once

#include <cmath>

/**
 * Contains utilities for working with floating point numbers.
 */
namespace TableProject::DoubleUtil {
	static bool isEqual(long double a, long double b, long double epsilon) {
		long double diff = a - b;
		if (diff < 0) {
			diff = -diff;
		}
		
		return diff < epsilon;
	}

	static bool isWhole(long double d, long double epsilon) {
		long double rounded = std::roundl(d);
		return isEqual(d, rounded, epsilon);
	}
}