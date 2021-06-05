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
	std::cout << t << '\n';
	
//	std::ofstream fileOut("tmp.csv", std::ios::out | std::ios::trunc);
//	fileOut << t.toCSV() << std::endl;
//	fileOut.close();
}

void asd() {
	Table t;
	t.put(0, 0, FormulaType("B1+D1^E1-F1"));
	t.put(0, 1, FormulaType("C1+D1+10"));
	t.put(0, 2, IntegerType(1));
	t.put(0, 3, IntegerType(2));
	t.put(0, 4, IntegerType(3));
	t.put(0, 5, IntegerType(4));
	std::cout << t;

	std::ofstream fileOut("tmp.csv", std::ios::out | std::ios::trunc);
	fileOut << t.toCSV() << std::endl;
	fileOut.close();
}

int main() {
//	asd();
	Table t("tmp.csv");
	
	std::cout << t;
	
	return 0;
}