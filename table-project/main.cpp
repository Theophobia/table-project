#include <fstream>
#include <iostream>

#include <table-project/math/Operators.h>
#include <table-project/table/Table.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/StringType.h>

using namespace std;

int main() {
	Table t;

	t.put(0, 0, StringType("asd"));
	t.put(0, 1, StringType("123"));
	t.put(1, 0, IntegerType(123));
	t.put(1, 1, IntegerType(123));
	t.put(2, 0, FormulaType("A1+A2"));
	t.put(2, 1, FormulaType("B1+B2"));

	cout << t << endl
		 << t.toCSV() << endl

	ofstream("tmp2.csv") << t.toCSV(); // Auto close with process end

	return 0;
}