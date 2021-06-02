#include "main/doctest.h"

#include "../src/table/Table.h"

TEST_CASE("Table_put_IntegerType_Matches") {
	// Arrange
	Table t;
	IntegerType it(123);
	
	// Act
	t.put<IntegerType>(0, 0, it);
	
	// Assert
	REQUIRE(it == *(t.table[0][0]));
}

TEST_CASE("Table_put_DoubleType_Matches") {
	// Arrange
	Table t;
	DoubleType dt(123.4);
	
	// Act
	t.put<DoubleType>(0, 0, dt);
	
	// Assert
	REQUIRE(dt == *(t.table[0][0]));
}

TEST_CASE("Table_put_StringType_Matches") {
	// Arrange
	Table t;
	StringType st("asd");
	
	// Act
	t.put<StringType>(0, 0, st);
	
	// Assert
	REQUIRE(st == *(t.table[0][0]));
}

TEST_CASE("Table_put_FormulaType_Matches") {
	// Arrange
	Table t;
	FormulaType ft("A1+B2");
	
	// Act
	t.put<FormulaType>(0, 0, ft);
	
	// Assert
	REQUIRE(ft == *(t.table[0][0]));
}