#include <table-project-tests/doctest.h>

using namespace TableProject;

TEST_CASE("VectorUtil_contains_EmptyVector_False") {
    // Arrange
    std::vector<int> v;

    // Act and Assert
    REQUIRE(false == TableProject::VectorUtil::contains(v, 0));
}

TEST_CASE("VectorUtil_contains_NonEmptyVectorWithoutElement_False") {
	// Arrange
	std::vector<int> v = {1, 2, 3, 4};

	// Act and Assert
	REQUIRE(false == TableProject::VectorUtil::contains(v, 0));
}

TEST_CASE("VectorUtil_contains_NonEmptyVectorWithElement_True") {
	// Arrange
	std::vector<int> v = {0, 1, 2, 3, 4};

	// Act and Assert
	REQUIRE(true == TableProject::VectorUtil::contains(v, 0));
}