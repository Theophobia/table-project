#include <table-project-tests/doctest.h>

using namespace TableProject;

TEST_CASE("StringUtil_isInteger_EmptyString_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isInteger(""));
}

TEST_CASE("StringUtil_isInteger_OnlyDecimalPoint_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isInteger("."));
}

TEST_CASE("StringUtil_isInteger_NoFracPartDouble_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isInteger("4."));
}

TEST_CASE("StringUtil_isInteger_NoWholePartDouble_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isInteger(".4"));
}

TEST_CASE("StringUtil_isInteger_NormalDouble_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isInteger("123.4"));
}

TEST_CASE("StringUtil_isInteger_PositiveInteger_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isInteger("123"));
}

TEST_CASE("StringUtil_isInteger_NegativeInteger_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isInteger("123"));
}

TEST_CASE("StringUtil_isInteger_Zero_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isInteger("0"));
}

// ------------------------------------------

TEST_CASE("StringUtil_isDouble_EmptyString_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isDouble(""));
}

TEST_CASE("StringUtil_isDouble_OnlyDecimalPoint_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isDouble("."));
}

TEST_CASE("StringUtil_isDouble_NoFracPartDouble_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isDouble("4."));
}

TEST_CASE("StringUtil_isDouble_NoWholePartDouble_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isDouble(".4"));
}

TEST_CASE("StringUtil_isDouble_Integer_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isDouble("123"));
}

TEST_CASE("StringUtil_isDouble_NormalDouble_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isDouble("123.4"));
}

TEST_CASE("StringUtil_toInt64_IntegerStringPassed_NoThrow") {
	// Arrange
	std::int64_t expected = 123;
	std::string s = std::to_string(expected);

	// Act
	std::int64_t actual = TableProject::StringUtil::toInt64(s, true);

	// Assert
	REQUIRE(expected == actual);
}

TEST_CASE("StringUtil_toInt64_DoubleStringPassed_Throws") {
	// Arrange
	std::string s = "123.4";

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toInt64(s, true));
}

TEST_CASE("StringUtil_toInt64_SomeStringPassed_Throws") {
	// Arrange
	std::string s = "123.4a";

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toInt64(s, true));
}

TEST_CASE("StringUtil_toInt64_EmptyStringPassed_Throw") {
	// Arrange
	std::string s = "";

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toInt64(s, true));
}

TEST_CASE("StringUtil_toLongDouble_EmptyStringPassed_Throw") {
	// Arrange
	std::string s = "";

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toLongDouble(s, true));
}

TEST_CASE("StringUtil_toLongDouble_DoubleStringPassed_NoThrow") {
	// Arrange
	long double expected = 123.456;
	std::string s = std::to_string(expected);

	// Act
	long double actual = TableProject::StringUtil::toLongDouble(s, true);

	// Assert
	REQUIRE(true == TableProject::DoubleUtil::isEqual(expected, actual, 0.000001));
}

TEST_CASE("StringUtil_toLongDouble_IntegerStringPassed_Throws") {
	// Arrange
	long double expected = 123;
	std::string s = std::to_string(expected);

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toLongDouble(s, true));
}

TEST_CASE("StringUtil_toLongDouble_DoubleDecimalPoint_Throws") {
	// Arrange
	std::string s = "123.4.5";

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toLongDouble(s, true));
}

TEST_CASE("StringUtil_toLongDouble_String_Throws") {
	// Arrange
	std::string s = "123aa";

	// Act and Assert
	REQUIRE_THROWS(TableProject::StringUtil::toLongDouble(s, true));
}

TEST_CASE("StringUtil_removeWrappedQuotes_WrappedString_QuotesRemoved") {
	// Arrange
	std::string unwrapped = "asd";
	std::string wrapped = '"' + unwrapped + '"';

	// Act and Assert
	REQUIRE(unwrapped == TableProject::StringUtil::removeWrappedQuotes(wrapped));
}

TEST_CASE("StringUtil_removeWrappedQuotes_StringWithQuoteStart_SameString") {
	// Arrange
	std::string s = "\"asd";

	// Act and Assert
	REQUIRE(s == TableProject::StringUtil::removeWrappedQuotes(s));
}


TEST_CASE("StringUtil_removeWrappedQuotes_StringWithQuoteEnd_SameString") {
	// Arrange
	std::string s = "asd\"";

	// Act and Assert
	REQUIRE(s == TableProject::StringUtil::removeWrappedQuotes(s));
}

TEST_CASE("StringUtil_removeWrappedQuotes_UnwrappedString_SameString") {
	// Arrange
	std::string unwrapped = "asd";

	// Act and Assert
	REQUIRE(unwrapped == TableProject::StringUtil::removeWrappedQuotes(unwrapped));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_SingleZero_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isZeroFractionalDouble("123.0"));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_MultipleZero_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isZeroFractionalDouble("123.00000"));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_OnlyZeroFractionalPart_True") {
	// Act and Assert
	REQUIRE(true == TableProject::StringUtil::isZeroFractionalDouble(".0"));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_NoDigitsAfterDecimalPoint_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isZeroFractionalDouble("123."));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_OnlyDecimalPoint_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isZeroFractionalDouble("."));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_OnlyNonZeroFractionalPart_False") {
	// Act and Assert
	REQUIRE(false == TableProject::StringUtil::isZeroFractionalDouble(".1"));
}