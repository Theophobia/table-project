#include <table-project-tests/doctest.h>

using namespace TableProject;

#include <table-project/util/DoubleUtil.h>

TEST_CASE("DoubleUtil_isEqual_CancellingMultiplicationAndDivision_True") {
    // Arrange
    long double a = ((long double) 22)/7 * 7 / 22;
	long double b = ((long double) 7)/22 * 22 / 7;

    // Act and Assert
    REQUIRE(true == TableProject::DoubleUtil::isEqual(a, b, 0.000001));
}

TEST_CASE("DoubleUtil_isEqual_SummedDoubles_True") {
	// Arrange
	long double a = 1 + 0.1 + 0.01 + 0.001;
	long double b = 1.111;

	// Act and Assert
	REQUIRE(true == TableProject::DoubleUtil::isEqual(a, b, 0.000001));
}

TEST_CASE("DoubleUtil_isEqual_ApproxSameLowEpsilon_false") {
	// Arrange
	long double a = 0.99999;
	long double b = 1;

	// Act and Assert
	REQUIRE(false == TableProject::DoubleUtil::isEqual(a, b, 0.0000001));
}

TEST_CASE("DoubleUtil_isEqual_ApproxSameGoodEpsilon_True") {
	// Arrange
	long double a = 0.99999;
	long double b = 1;

	// Act and Assert
	REQUIRE(true == TableProject::DoubleUtil::isEqual(a, b, 0.00001));
}

TEST_CASE("DoubleUtil_isWhole_ApproxSameGoodEpsilon_True") {
	// Arrange
	long double a = 0.99999;

	// Act and Assert
	REQUIRE(true == TableProject::DoubleUtil::isWhole(a, 0.00001));
}

TEST_CASE("DoubleUtil_isWhole_ApproxSameLowEpsilon_False") {
	// Arrange
	long double a = 0.99999;

	// Act and Assert
	REQUIRE(false == TableProject::DoubleUtil::isWhole(a, 0.000001));
}