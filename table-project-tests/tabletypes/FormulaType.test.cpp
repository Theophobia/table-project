#include <table-project-tests/doctest.h>

using namespace TableProject;

TEST_CASE("FormulaType_tryParse_StartsWith=_ReturnedMatches") {
    // Arrange
    FormulaType ft;
    std::string formula = "A1+A2+10";

    // Act and Assert
	REQUIRE_NOTHROW(ft.tryParse('=' + formula));
	REQUIRE(formula == ft.getFormula());
}

TEST_CASE("FormulaType_tryParse_DoesntStartWith=_Throws") {
	// Arrange
	FormulaType ft;
	std::string formula = "A1+A2+10";

	// Act and Assert
	REQUIRE_THROWS(ft.tryParse(formula));
}

TEST_CASE("FormulaType_tryParse_EmptyString_Throws") {
	// Arrange
	FormulaType ft;
	std::string formula = "";

	// Act and Assert
	REQUIRE_THROWS(ft.tryParse(formula));
}