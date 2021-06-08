#include <table-project-tests/doctest.h>

#include <table-project/tabletypes/IntegerType.h>

using namespace TableProject;

TEST_CASE("IntegerType_toString_PositiveNumber_StringMatches") {
	// Arrange
	std::int64_t i = 123;
	IntegerType it(i);
	std::string expected = std::to_string(i);

	// Act
	std::string actual = it.toString();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("IntegerType_toCSV_PositiveNumber_StringMatches") {
	// Arrange
	std::int64_t i = 123;
	IntegerType it(i);
	std::string expected = std::to_string(i);

	// Act
	std::string actual = it.toCSV();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("IntegerType_toCSVtoString_PositiveNumber_BothStringsMatch") {
	// Arrange
	std::int64_t i = 123;
	IntegerType it(i);

	// Act
	std::string csv = it.toCSV();
	std::string str = it.toString();

	// Assert
	REQUIRE(str == csv);
}

TEST_CASE("IntegerType_toString_NegativeNumber_StringMatches") {
	// Arrange
	std::int64_t i = -123;
	IntegerType it(i);
	std::string expected = std::to_string(i);

	// Act
	std::string actual = it.toString();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("IntegerType_toCSV_NegativeNumber_StringMatches") {
	// Arrange
	std::int64_t i = -123;
	IntegerType it(i);
	std::string expected = std::to_string(i);

	// Act
	std::string actual = it.toCSV();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("IntegerType_toCSVtoString_NegativeNumber_BothStringsMatch") {
	// Arrange
	std::int64_t i = -123;
	IntegerType it(i);

	// Act
	std::string csv = it.toCSV();
	std::string str = it.toString();

	// Assert
	REQUIRE(str == csv);
}

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