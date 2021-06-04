#include <iostream>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/StringType.h>

int main() {
	Table t;
	
	t.put(3, 3, IntegerType(123));
	t.put(1, 2, StringType("asdasd"));
	t.put(1, 3, DoubleType(123.4));
	
	const Type & it = t.get(3, 3);
	std::cout << t;
	
	return 0;
}
