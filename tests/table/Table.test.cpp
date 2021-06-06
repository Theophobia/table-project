#include "tests/doctest.h"

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/tabletypes/StringType.h>

TEST_CASE("Table_operator<<_FormulaCastingZero") {
	// Arrange
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

	const std::string expectedPrint =
			"\n"
			"   |   A |   B |\n"
			" 1 | asd | 123 |\n"
			" 2 | 123 | 123 |\n"
			" 3 | 123 | 246 |";

	std::ostringstream os;

	// Act
	os << table;

	// Assert
	REQUIRE("123" == ((FormulaType &) table.get(2, 0)).get);
}