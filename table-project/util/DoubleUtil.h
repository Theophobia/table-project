#pragma once

namespace DoubleUtil {
	static bool isEqual(long double a, long double b, long double epsilon) {
		long double diff = a - b;
		if (diff < 0) {
			diff = -diff;
		}
		
		return diff < epsilon;
	}
}