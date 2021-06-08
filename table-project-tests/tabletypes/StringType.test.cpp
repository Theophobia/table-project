#include <table-project-tests/doctest.h>

#include <table-project/tabletypes/StringType.h>

using namespace TableProject;

TEST_CASE("StringType_isIntegerCastable_PositiveInteger_True") {
	// Arrange
	StringType st("123");

	// Act and Assert
	REQUIRE(true == st.isIntegerCastable());
}

TEST_CASE("StringType_isIntegerCastable_NegativeInteger_True") {
	// Arrange
	StringType st("-123");

	// Act and Assert
	REQUIRE(true == st.isIntegerCastable());
}

TEST_CASE("StringType_isIntegerCastable_Double_False") {
	// Arrange
	StringType st("123.4");

	// Act and Assert
	REQUIRE(false == st.isIntegerCastable());
}

TEST_CASE("StringType_isIntegerCastable_SomeString_False") {
	// Arrange
	StringType st("123a");

	// Act and Assert
	REQUIRE(false == st.isIntegerCastable());
}

TEST_CASE("StringType_isIntegerCastable_EmptyString_False") {
	// Arrange
	StringType st("");

	// Act and Assert
	REQUIRE(false == st.isIntegerCastable());
}

TEST_CASE("StringType_isDoubleCastable_PositiveDouble_True") {
	// Arrange
	StringType st("123.4");

	// Act and Assert
	REQUIRE(true == st.isDoubleCastable());
}

TEST_CASE("StringType_isDoubleCastable_NegativeDouble_True") {
	// Arrange
	StringType st("-123.4");

	// Act and Assert
	REQUIRE(true == st.isDoubleCastable());
}

TEST_CASE("StringType_isDoubleCastable_Integer_False") {
	// Arrange
	StringType st("123");

	// Act and Assert
	REQUIRE(false == st.isDoubleCastable());
}

TEST_CASE("StringType_isDoubleCastable_SomeString_False") {
	// Arrange
	StringType st("123.4a");

	// Act and Assert
	REQUIRE(false == st.isDoubleCastable());
}

TEST_CASE("StringType_isDoubleCastable_EmptyString_False") {
	// Arrange
	StringType st("");

	// Act and Assert
	REQUIRE(false == st.isDoubleCastable());
}

TEST_CASE("StringType_tryParse_SurroundedString_NoThrow") {
    // Arrange
    StringType st;
    
    // Act and Assert
    REQUIRE_NOTHROW(st.tryParse("\"string\""));
}

TEST_CASE("StringType_tryParse_EscapedQuotes_NoThrow") {
	// Arrange
	StringType st;
	
	// Act and Assert
	REQUIRE_NOTHROW(st.tryParse("\"str\\\"123\""));
}

TEST_CASE("StringType_tryParse_EmptyString_NoThrow") {
	// Arrange
	StringType st;
	
	// Act and Assert
	REQUIRE_NOTHROW(st.tryParse("\"\""));
}

TEST_CASE("StringType_tryParse_SingleQuote_Throws") {
	// Arrange
	StringType st;
	
	// Act and Assert
	REQUIRE_THROWS(st.tryParse("\""));
}

TEST_CASE("StringType_tryParse_NotSurroundedString_Throws") {
	// Arrange
	StringType st;
	
	// Act and Assert
	REQUIRE_THROWS(st.tryParse("asd"));
}