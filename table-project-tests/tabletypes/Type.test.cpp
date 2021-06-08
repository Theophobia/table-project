#include <table-project-tests/doctest.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>

using namespace TableProject;

TEST_CASE("Type_getClass_AllSubtypes_AllHaveDifferentValues") {
	// Can use hashing here, but whatever,
	// this works without hashing containers

    // Arrange
	std::string is = IntegerType().getClass();
	std::string ds = DoubleType().getClass();
	std::string ss = StringType().getClass();
	std::string fs = FormulaType().getClass();

    // Assert
	REQUIRE(is != ds);
	REQUIRE(is != ss);
	REQUIRE(is != fs);

	REQUIRE(ds != is);
	REQUIRE(ds != ss);
	REQUIRE(ds != fs);

	REQUIRE(ss != is);
	REQUIRE(ss != ds);
	REQUIRE(ss != fs);

	REQUIRE(fs != is);
	REQUIRE(fs != ss);
	REQUIRE(fs != ss);
}

TEST_CASE("Type_createCopy_IntegerType_ExactCopy") {
	// Arrange
	IntegerType it(123);

	// Act
	std::shared_ptr<Type> copy = Type::createCopy(it);

	// Assert
	REQUIRE(copy != nullptr);
	REQUIRE(it == *copy);
}

TEST_CASE("Type_createCopy_DoubleType_ExactCopy") {
	// Arrange
	DoubleType dt(123.4);

	// Act
	std::shared_ptr<Type> copy = Type::createCopy(dt);

	// Assert
	REQUIRE(copy != nullptr);
	REQUIRE(dt == *copy);
}

TEST_CASE("Type_createCopy_StringType_ExactCopy") {
	// Arrange
	StringType st("123");

	// Act
	std::shared_ptr<Type> copy = Type::createCopy(st);

	// Assert
	REQUIRE(copy != nullptr);
	REQUIRE(st == *copy);
}

TEST_CASE("Type_createCopy_FormulaType_ExactCopy") {
	// Arrange
	FormulaType ft("A1+A2");

	// Act
	std::shared_ptr<Type> copy = Type::createCopy(ft);

	// Assert
	REQUIRE(copy != nullptr);
	REQUIRE(ft == *copy);
}

TEST_CASE("Type_fromString_PositiveInteger_ReturnsIntegerType") {
	// Arrange
	std::int64_t i = 123;
	std::string s = std::to_string(i);

	// Act
	std::shared_ptr<Type> returned = Type::fromString(s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(IntegerType().getClass() == returned->getClass());
	REQUIRE(IntegerType(i) == *returned);
}

TEST_CASE("Type_fromString_NegativeInteger_ReturnsIntegerType") {
	// Arrange
	std::int64_t i = -123;
	std::string s = std::to_string(i);

	// Act
	std::shared_ptr<Type> returned = Type::fromString(s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(IntegerType().getClass() == returned->getClass());
	REQUIRE(IntegerType(i) == *returned);
}

TEST_CASE("Type_fromString_PositiveDouble_ReturnsDoubleType") {
	// Arrange
	long double d = 123.4;
	std::string s = std::to_string(d);

	// Act
	std::shared_ptr<Type> returned = Type::fromString(s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(DoubleType().getClass() == returned->getClass());
	REQUIRE(DoubleType(d) == *returned);
}

TEST_CASE("Type_fromString_NegativeDouble_ReturnsDoubleType") {
	// Arrange
	long double d = -123.4;
	std::string s = std::to_string(d);

	// Act
	std::shared_ptr<Type> returned = Type::fromString(s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(DoubleType().getClass() == returned->getClass());
	REQUIRE(DoubleType(d) == *returned);
}

TEST_CASE("Type_fromString_String_ReturnsStringType") {
	// Arrange
	std::string s = "asd";

	// Act
	std::shared_ptr<Type> returned = Type::fromString('"' + s + '"');

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(StringType().getClass() == returned->getClass());
	REQUIRE(StringType(s) == *returned);
}

TEST_CASE("Type_fromString_Formula_ReturnsFormulaType") {
	// Arrange
	std::string s = "A1+A2+10";

	// Act
	std::shared_ptr<Type> returned = Type::fromString('=' + s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(FormulaType().getClass() == returned->getClass());
	REQUIRE(FormulaType(s) == *returned);
}

TEST_CASE("Type_fromString_ZeroFractionalDouble_ReturnsIntegerType") {
	// Arrange
	std::int64_t i = 123;
	std::string s = std::to_string(i) + ".00000";

	// Act
	std::shared_ptr<Type> returned = Type::fromString(s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(IntegerType().getClass() == returned->getClass());
	REQUIRE(IntegerType(i) == *returned);
}

TEST_CASE("Type_fromString_ZeroFractionalDouble_ReturnsIntegerType") {
	// Arrange
	std::int64_t i = 123;
	std::string s = std::to_string(i) + ".00000";

	// Act
	std::shared_ptr<Type> returned = Type::fromString(s);

	// Assert
	REQUIRE(returned != nullptr);
	REQUIRE(IntegerType().getClass() == returned->getClass());
	REQUIRE(IntegerType(i) == *returned);
}