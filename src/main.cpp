#include <iostream>

#include "Type.h"
#include "IntegerType.h"
#include "FloatingType.h"

int main() {
	IntegerType it(123);
	FloatingType ft(123.4);
	
	std::cout << it << std::endl;
	std::cout << ft << std::endl;

	return 0;
}
