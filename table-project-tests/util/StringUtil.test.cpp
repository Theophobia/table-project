#include <table-project-tests/doctest.h>

TEST_CASE("StringUtil_isZeroFractionalDouble_SingleZero_True") {
	REQUIRE(true == TableProject::StringUtil::isZeroFractionalDouble("123.0"));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_MultipleZero_True") {
	REQUIRE(true == TableProject::StringUtil::isZeroFractionalDouble("123.00000"));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_OnlyZeroFractionalPart_True") {
	REQUIRE(true == TableProject::StringUtil::isZeroFractionalDouble(".0"));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_NoDigitsAfterDecimalPoint_False") {
	REQUIRE(false == TableProject::StringUtil::isZeroFractionalDouble("123."));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_OnlyDecimalPoint_False") {
	REQUIRE(false == TableProject::StringUtil::isZeroFractionalDouble("."));
}

TEST_CASE("StringUtil_isZeroFractionalDouble_OnlyNonZeroFractionalPart_False") {
	REQUIRE(false == TableProject::StringUtil::isZeroFractionalDouble(".1"));
}