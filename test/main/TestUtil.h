#ifndef TABLE_TESTUTIL_H
#define TABLE_TESTUTIL_H

class TestUtil {

public:
	static bool isEqual(long double a, long double b, long double epsilon) {
		long double diff = a - b;
		if (diff < 0) {
			diff = -diff;
		}
		
		return diff < epsilon;
	}
};

#endif //TABLE_TESTUTIL_H
