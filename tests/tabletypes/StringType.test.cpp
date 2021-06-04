#include <tests/doctest.h>

#include <table-project/tabletypes/StringType.h>

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