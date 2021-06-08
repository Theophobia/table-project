#include <table-project-tests/doctest.h>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/tabletypes/StringType.h>

using namespace TableProject;

TEST_CASE("Table_get_MissingElement_Throws") {
	// Arrange
	Table t;

	// Act and Assert
	REQUIRE_THROWS(t.get(0, 0));
}

TEST_CASE("Table_get_MissingAndOutOfBounds_Throws") {
	// Arrange
	Table t;

	// Act and Assert
	REQUIRE_THROWS(t.get(0, 26));
}

TEST_CASE("Table_getConst_MissingElement_Throws") {
	// Arrange
	const Table t;

	// Act and Assert
	REQUIRE_THROWS(t.get(0, 0));
}

TEST_CASE("Table_getConst_MissingAndOutOfBounds_Throws") {
	// Arrange
	const Table t;

	// Act and Assert
	REQUIRE_THROWS(t.get(0, 26));
}

TEST_CASE("Table_put_Column25_NoThrow") {
	// Arrange
	Table t;
	IntegerType it(123);

	// Act and Assert
	REQUIRE_NOTHROW(t.put(0, 25, it));
}

TEST_CASE("Table_put_Column26_Throws") {
	// Arrange
	Table t;
	IntegerType it(123);

	// Act and Assert
	REQUIRE_THROWS(t.put(0, 26, it));
}

TEST_CASE("Table_put/get_PutAllTypes_AllMatch") {
    // Arrange
    Table t;
    IntegerType elem00(123);
	DoubleType elem01(123.4);
	StringType elem02("asd");
	FormulaType elem03("=A1+A2");

    // Act and Assert
	t.put(0, 0, elem00);
	t.put(0, 1, elem01);
	t.put(0, 2, elem02);
	t.put(0, 3, elem03);

	REQUIRE(elem00 == t.get(0, 0));
	REQUIRE(elem01 == t.get(0, 1));
	REQUIRE(elem02 == t.get(0, 2));
	REQUIRE(elem03 == t.get(0, 3));
}

TEST_CASE("Table_toCSV()_EmptyTable_EmptyCSV") {
	// Arrange
	Table t;
	std::string expected = "";

	// Act
	std::string actual = t.toCSV();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("Table_toCSV()_AllTypesInTable_ResultMatches") {
	// Arrange
	Table t;
	t.put(0, 0, IntegerType(123));
	t.put(0, 1, DoubleType(123.4));
	t.put(0, 2, StringType("asd"));
	t.put(0, 3, FormulaType("A1+A2"));
	std::string expected = "123,123.4,\"asd\",=A1+A2";

    // Act
    std::string actual = t.toCSV();

    // Assert
	REQUIRE(expected == actual);
}

TEST_CASE("Table_calculate()_FormulaPlusMinusCancellation_CorrectValues") {
	// Arrange
	Table table;
	table.put(0, 0, IntegerType(2));

	table.put(2, 0, FormulaType("A1-A1"));

	// Act
	table.calculate();

	// Assert
	REQUIRE("0" == table.get(2, 0).toString());
}

TEST_CASE("Table_calculate()_FormulaPlusMinusCancellation2_CorrectValues") {
	// Arrange
	Table table;
	table.put(0, 0, IntegerType(2));

	table.put(2, 0, FormulaType("0-A1+A1"));

	// Act
	table.calculate();

	// Assert
	REQUIRE("0" == table.get(2, 0).toString());
}

TEST_CASE("Table_calculate()_FormulaArithmeticCasting_CorrectValues") {
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

	// Act
	table.calculate();

	// Assert
	REQUIRE("123" == table.get(2, 0).toString());
	REQUIRE("246" == table.get(2, 1).toString());
}

TEST_CASE("Table_calculate()_FormulaPrecedenceStringCast_CorrectValues") {
	// Arrange
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

	// Act
	table.calculate();

	// Assert
	REQUIRE("15220.125" == table.get(2, 0).toString());
}

TEST_CASE("Table_indexToColumnLetter_FirstIndex_FirstLetter") {
	// Act and Assert
    REQUIRE('A' == Table::indexToColumnLetter(0));
}

TEST_CASE("Table_indexToColumnLetter_LastIndex_LastLetter") {
	// Act and Assert
	REQUIRE('Z' == Table::indexToColumnLetter(25));
}

TEST_CASE("Table_indexToColumnLetter_SomeIndex_SomeLetter") {
	// Act and Assert
	for (std::size_t i = 0; i < 25; i++) {
		REQUIRE('A' + i == Table::indexToColumnLetter(0 + i));
	}
}

TEST_CASE("Table_indexToColumnLetter_IndexAbove25_Throws") {
	// Act and Assert
	REQUIRE_THROWS(Table::indexToColumnLetter(26));
}

TEST_CASE("Table_columnLetterToIndex_FirstLetter_FirstIndex") {
	// Act and Assert
	REQUIRE(0 == Table::columnLetterToIndex('A'));
}

TEST_CASE("Table_columnLetterToIndex_LastLetter_LastIndex") {
	// Act and Assert
	REQUIRE(25 == Table::columnLetterToIndex('Z'));
}

TEST_CASE("Table_indexToColumnLetter_CharBeforeUppercaseMin_Throws") {
	// Act and Assert
	REQUIRE_THROWS(Table::columnLetterToIndex('A' - 1));
}

TEST_CASE("Table_indexToColumnLetter_CharAfterUppercaseMax_Throws") {
	// Act and Assert
	REQUIRE_THROWS(Table::columnLetterToIndex('Z' + 1));
}

TEST_CASE("Table_columnLetterToIndex_LowercaseFirstLetter_FirstIndex") {
	// Act and Assert
	REQUIRE(0 == Table::columnLetterToIndex('a'));
}

TEST_CASE("Table_columnLetterToIndex_LowercaseLastLetter_LastIndex") {
	// Act and Assert
	REQUIRE(25 == Table::columnLetterToIndex('z'));
}

TEST_CASE("Table_indexToColumnLetter_CharBeforeLowercaseMin_Throws") {
	// Act and Assert
	REQUIRE_THROWS(Table::columnLetterToIndex('a' - 1));
}

TEST_CASE("Table_indexToColumnLetter_CharAfterLowercaseMax_Throws") {
	// Act and Assert
	REQUIRE_THROWS(Table::columnLetterToIndex('z' + 1));
}

TEST_CASE("Table_columnLetterToIndex_SomeLetter_SomeIndex") {
	// Act and Assert
	for (char c = 'A'; c < 'Z'; c++) {
		REQUIRE(c - 'A' == Table::columnLetterToIndex(c));
	}
}

TEST_CASE("Table_cellCoordsToIndices_FirstRowFirstCol_Returns(0, 0)") {
    // Arrange
    std::string cellCoords = "A1";
	std::pair<std::size_t, std::size_t> cellIndices(0, 0);

    // Act and Assert
    REQUIRE(cellIndices == Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_FirstRowLastCol_Returns(0, 25)") {
	// Arrange
	std::string cellCoords = "Z1";
	std::pair<std::size_t, std::size_t> cellIndices(0, 25);

	// Act and Assert
	REQUIRE(cellIndices == Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_FifthRowLastCol_Returns(4, 25)") {
	// Arrange
	std::string cellCoords = "Z5";
	std::pair<std::size_t, std::size_t> cellIndices(4, 25);

	// Act and Assert
	REQUIRE(cellIndices == Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_FirstRowLowercaseFirstCol_Returns(0, 0)") {
	// Arrange
	std::string cellCoords = "a1";
	std::pair<std::size_t, std::size_t> cellIndices(0, 0);

	// Act and Assert
	REQUIRE(cellIndices == Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_FirstRowLowercaseLastCol_Returns(0, 25)") {
	// Arrange
	std::string cellCoords = "z1";
	std::pair<std::size_t, std::size_t> cellIndices(0, 25);

	// Act and Assert
	REQUIRE(cellIndices == Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_FifthRowLowercaseLastCol_Returns(4, 25)") {
	// Arrange
	std::string cellCoords = "z5";
	std::pair<std::size_t, std::size_t> cellIndices(4, 25);

	// Act and Assert
	REQUIRE(cellIndices == Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_UppercaseColMissingRow_Throws") {
	// Arrange
	std::string cellCoords = "Z";

	// Act and Assert
	REQUIRE_THROWS(Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_LowercaseColMissingRow_Throws") {
	// Arrange
	std::string cellCoords = "z";

	// Act and Assert
	REQUIRE_THROWS(Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_MissingCol_Throws") {
	// Arrange
	std::string cellCoords = "123";

	// Act and Assert
	REQUIRE_THROWS(Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_EmptyString_Throws") {
	// Arrange
	std::string cellCoords;

	// Act and Assert
	REQUIRE_THROWS(Table::cellCoordsToIndices(cellCoords));
}

TEST_CASE("Table_cellCoordsToIndices_Reversed_Throws") {
	// Arrange
	std::string cellCoords = "123Z";

	// Act and Assert
	REQUIRE_THROWS(Table::cellCoordsToIndices(cellCoords));
}