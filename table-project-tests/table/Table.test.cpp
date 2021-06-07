#include <table-project-tests/doctest.h>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/tabletypes/StringType.h>

using namespace TableProject;

TEST_CASE("Table_calculate()_FormulaPlusMinusCancellation_CorrectValues") {
	Table table;
	table.put(0, 0, IntegerType(2));

	table.put(2, 0, FormulaType("A1-A1"));

	table.calculate();

	// Assert
	REQUIRE("0" == table.get(2, 0).toString());
}

TEST_CASE("Table_calculate()_FormulaPlusMinusCancellation2_CorrectValues") {
	Table table;
	table.put(0, 0, IntegerType(2));

	table.put(2, 0, FormulaType("0-A1+A1"));

	table.calculate();

	// Assert
	REQUIRE("0" == table.get(2, 0).toString());
}

TEST_CASE("Table_calculate()_FormulaArithmeticCasting_CorrectValues") {
	Table table;
	table.put(0, 0, StringType("asd"));
	table.put(0, 1, StringType("123"));

	table.put(1, 0, IntegerType(123));
	table.put(1, 1, IntegerType(123));

	table.put(2, 0, FormulaType("A1+A2"));
	table.put(2, 1, FormulaType("B1+B2"));

	//	"asd","123"
	//	123,123
	//	=A1+A2,=B1+B2
	table.calculate();

	// Assert
	REQUIRE("123" == table.get(2, 0).toString());
	REQUIRE("246" == table.get(2, 1).toString());
}

TEST_CASE("Table_calculate()_FormulaPrecedence_CorrectValues") {
	Table table;
	table.put(0, 0, StringType("asd"));
	table.put(0, 1, StringType("123"));
	table.put(0, 2, StringType("4.5"));

	table.put(1, 0, IntegerType(123));
	table.put(1, 1, IntegerType(2));
	table.put(1, 2, StringType("3"));

	table.put(2, 0, FormulaType("B1^B2+A1*A2+C1^C2-C2+C2+D8"));
	// 123^2 + 0 * 123 + 4.5^3 - 2 + 2 + 0
	// = 15129 + 0 + 91.125
	// = 15220.125

	table.calculate();

	// Assert
	REQUIRE("15220.125" == table.get(2, 0).toString());
}