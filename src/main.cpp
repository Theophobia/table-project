#define TABLE_TEST

#include <iostream>

#include "tabletypes/base/Type.h"
#include "tabletypes/IntegerType.h"
#include "tabletypes/DoubleType.h"
#include "exception/ParseError.h"
#include "table/Table.h"

int main() {
	Table t;
	
	t.put(3, 3, IntegerType(123));
	
	const IntegerType & it = t.getInteger(3, 3);
	const DoubleType & dt = t.getDouble(3, 3);
	
	return 0;
}
