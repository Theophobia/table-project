#include <iostream>
#include <fstream>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>s
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/math/Operators.h>

void createPrintAndSaveTable() {
	Table t;
	
	t.put(0, 0, FormulaType("D2+D4"));
	t.put(3, 3, IntegerType(123));
	t.put(1, 2, StringType("asdasd"));
	t.put(1, 3, DoubleType(123.4));
	
	const Type & it = t.get(3, 3);
	std::cout << t << '\n';
	
	// Real men don't check if file is opened properly
	std::ofstream fileOut("tmp.csv", std::ios::out | std::ios::trunc);
	fileOut << t.toCSV() << std::endl;
	fileOut.close();
	
}

void asd() {
	Table t;
	t.put(0, 0, FormulaType("B1+D1^E1"));
	t.put(0, 1, FormulaType("C1+D1+10"));
	t.put(0, 2, IntegerType(123));
	t.put(0, 3, IntegerType(456));
	t.put(0, 4, IntegerType(2));
	std::cout << t;

//	std::ofstream fileOut("tmp.csv", std::ios::out | std::ios::trunc);
//	fileOut << t.toCSV() << std::endl;
//	fileOut.close();
}

int main() {
	asd();
	return 0;
}
