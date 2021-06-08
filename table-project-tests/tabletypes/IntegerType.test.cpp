#include <table-project-tests/doctest.h>

#include <table-project/tabletypes/IntegerType.h>

using namespace TableProject;

TEST_CASE("IntegerType_tryParse_NormalInteger_NoThrow") {
	// Arrange
	IntegerType it;
	
	// Act and Assert
	REQUIRE_NOTHROW(it.tryParse("123"));
	REQUIRE(123 == it.getNumber());
}

TEST_CASE("IntegerType_tryParse_LeadingZeros_NoThrow") {
	// Arrange
	IntegerType it;
	
	// Act and Assert
	REQUIRE_NOTHROW(it.tryParse("000123"));
	REQUIRE(123 == it.getNumber());
}

TEST_CASE("IntegerType_tryParse_OnlyZeros_NoThrow") {
	// Arrange
	IntegerType it;
	
	// Act and Assert
	REQUIRE_NOTHROW(it.tryParse("00000"));
	REQUIRE(0 == it.getNumber());
}

TEST_CASE("IntegerType_tryParse_SingleZeroFractionalDouble_NoThrow") {
	// Arrange
	IntegerType it;

	// Act and Assert
	REQUIRE_NOTHROW(it.tryParse("123.0"));
	REQUIRE(123 == it.getNumber());
}

TEST_CASE("IntegerType_tryParse_MultiZeroFractionalDouble_NoThrow") {
	// Arrange
	IntegerType it;

	// Act and Assert
	REQUIRE_NOTHROW(it.tryParse("123.0000000"));
	REQUIRE(123 == it.getNumber());
}

TEST_CASE("IntegerType_tryParse_DoublePassed_Throws") {
	// Arrange
	IntegerType it;
	
	// Act and Assert
	REQUIRE_THROWS(it.tryParse("123.4"));
}

TEST_CASE("IntegerType_tryParse_NumberWithLetter_Throws") {
	// Arrange
	IntegerType it;
	
	// Act and Assert
	REQUIRE_THROWS(it.tryParse("1234a"));
}

TEST_CASE("IntegerType_tryParse_NumberWithString_Throws") {
	// Arrange
	IntegerType it;
	
	// Act and Assert
	REQUIRE_THROWS(it.tryParse("\"1234\""));
}