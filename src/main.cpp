#include <iostream>

#include "celltypes/base/Type.h"
#include "celltypes/IntegerType.h"
#include "celltypes/DoubleType.h"
#include "exception/ParseError.h"

int main() {
	ParseError<DoubleType> be = ParseError<DoubleType>("asd");
	return 0;
}
