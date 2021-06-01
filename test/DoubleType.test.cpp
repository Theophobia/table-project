#include <vector>

#include "main/doctest.h"
#include "main/TestUtil.h"

#include "../src/celltypes/DoubleType.h"

TEST_CASE("FloatingType_tryParse_NormalFloating_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("123.4"));
	REQUIRE(TestUtil::isEqual(123.4, ft.getNumber(), 0.000000000001));
}

TEST_CASE("FloatingType_tryParse_LeadingZero_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("0001.1"));
	REQUIRE(TestUtil::isEqual(1.1, ft.getNumber(), 0.000000000001));
}

TEST_CASE("FloatingType_tryParse_TrailingZero_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("10.01000"));
	REQUIRE(TestUtil::isEqual(10.01, ft.getNumber(), 0.000000000001));
}

TEST_CASE("FloatingType_tryParse_ZeroWholePart_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("000.1"));
	REQUIRE(TestUtil::isEqual(0.1, ft.getNumber(), 0.000000000001));
}

TEST_CASE("FloatingType_tryParse_ZeroFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("3.0"));
}

TEST_CASE("FloatingType_tryParse_NoFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("34"));
}

TEST_CASE("FloatingType_tryParse_NoWholePart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse(".3"));
}

TEST_CASE("FloatingType_tryParse_NoWholeOrFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("."));
}

TEST_CASE("FloatingType_tryParse_ZeroWholeAndFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("0.0"));
}

TEST_CASE("FloatingType_tryParse_MultiplePoints_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("12.34.23"));
}