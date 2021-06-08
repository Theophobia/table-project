#include <table-project-tests/doctest.h>
#include <table-project/util/DoubleUtil.h>

#include <table-project/tabletypes/DoubleType.h>

using namespace TableProject;

TEST_CASE("DoubleType_toString_PositiveNumber_StringMatches") {
	// Arrange
	long double d = 123.4;
	DoubleType dt(d);
	// From: https://stackoverflow.com/a/20729194
	char buf[64];
	std::sprintf(buf, "%-.*LG", 16, d);
	std::string expected = buf;

	// Act
	std::string actual = dt.toString();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("DoubleType_toCSV_PositiveNumber_StringMatches") {
	// Arrange
	long double d = 123.4;
	DoubleType dt(d);
	// From: https://stackoverflow.com/a/20729194
	char buf[64];
	std::sprintf(buf, "%-.*LG", 16, d);
	std::string expected = buf;

	// Act
	std::string actual = dt.toCSV();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("DoubleType_toCSVtoString_PositiveNumber_BothStringsMatch") {
	// Arrange
	long double d = 123.4;
	DoubleType dt(d);

	// Act
	std::string csv = dt.toCSV();
	std::string str = dt.toString();

	// Assert
	REQUIRE(str == csv);
}

TEST_CASE("DoubleType_toString_NegativeNumber_StringMatches") {
	// Arrange
	long double d = -123.4;
	DoubleType dt(d);
	// From: https://stackoverflow.com/a/20729194
	char buf[64];
	std::sprintf(buf, "%-.*LG", 16, d);
	std::string expected = buf;

	// Act
	std::string actual = dt.toString();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("DoubleType_toCSV_NegativeNumber_StringMatches") {
	// Arrange
	long double d = -123.4;
	DoubleType dt(d);
	// From: https://stackoverflow.com/a/20729194
	char buf[64];
	std::sprintf(buf, "%-.*LG", 16, d);
	std::string expected = buf;

	// Act
	std::string actual = dt.toCSV();

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("DoubleType_toCSVtoString_NegativeNumber_BothStringsMatch") {
	// Arrange
	long double d = 123.4;
	DoubleType dt(d);

	// Act
	std::string csv = dt.toCSV();
	std::string str = dt.toString();

	// Assert
	REQUIRE(str == csv);
}

TEST_CASE("DoubleType_tryParse_NormalDouble_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("123.4"));
	REQUIRE(TableProject::DoubleUtil::isEqual(123.4, ft.getNumber(), 0.000000000001));
}

TEST_CASE("DoubleType_tryParse_LeadingZero_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("0001.1"));
	REQUIRE(TableProject::DoubleUtil::isEqual(1.1, ft.getNumber(), 0.000000000001));
}

TEST_CASE("DoubleType_tryParse_TrailingZero_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("10.01000"));
	REQUIRE(TableProject::DoubleUtil::isEqual(10.01, ft.getNumber(), 0.000000000001));
}

TEST_CASE("DoubleType_tryParse_ZeroWholePart_NoThrow") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse("000.1"));
	REQUIRE(TableProject::DoubleUtil::isEqual(0.1, ft.getNumber(), 0.000000000001));
}

TEST_CASE("DoubleType_tryParse_NoWholePart_NoThrow") {
	// Arrange
	DoubleType ft;

	// Act and Assert
	REQUIRE_NOTHROW(ft.tryParse(".1"));
	REQUIRE(TableProject::DoubleUtil::isEqual(0.1, ft.getNumber(), 0.000000000001));
}

TEST_CASE("DoubleType_tryParse_ZeroFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("3.0"));
}

TEST_CASE("DoubleType_tryParse_NoFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("34"));
}

TEST_CASE("DoubleType_tryParse_NoWholeOrFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("."));
}

TEST_CASE("DoubleType_tryParse_ZeroWholeAndFractionalPart_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("0.0"));
}

TEST_CASE("DoubleType_tryParse_MultiplePoints_Throws") {
	// Arrange
	DoubleType ft;
	
	// Act and Assert
	REQUIRE_THROWS(ft.tryParse("12.34.23"));
}