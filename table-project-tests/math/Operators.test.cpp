#include <memory>

#include <table-project-tests/doctest.h>

#include <table-project/math/Operators.h>

using namespace TableProject;

TEST_CASE("operator+(IntegerType, IntegerType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(3);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(4);

	// Act
	std::unique_ptr<Type> c = a + b;

	// Assert
	auto c_cast = dynamic_cast<IntegerType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(7 == c_cast->getNumber());
}

TEST_CASE("operator-(IntegerType, IntegerType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(3);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(4);

	// Act
	std::unique_ptr<Type> c = a - b;

	// Assert
	auto c_cast = dynamic_cast<IntegerType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(-1 == c_cast->getNumber());
}

TEST_CASE("operator*(IntegerType, IntegerType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(3);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(4);

	// Act
	std::unique_ptr<Type> c = a * b;

	// Assert
	auto c_cast = dynamic_cast<IntegerType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(12 == c_cast->getNumber());
}

TEST_CASE("operator/(IntegerType, IntegerType)_NoRemainder_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(8);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(4);

	// Act
	std::unique_ptr<Type> c = a / b;

	// Assert
	auto c_cast = dynamic_cast<IntegerType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(2 == c_cast->getNumber());
}

TEST_CASE("operator/(IntegerType, IntegerType)_WithRemainder_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(7);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(4);

	// Act
	std::unique_ptr<Type> c = a / b;

	// Assert
	auto c_cast = dynamic_cast<DoubleType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(TableProject::DoubleUtil::isEqual(7.0 / 4.0, c_cast->getNumber(), 0.00001));
}

TEST_CASE("operator^(IntegerType, IntegerType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(2);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(3);

	// Act
	std::unique_ptr<Type> c = a ^b;

	// Assert
	auto c_cast = dynamic_cast<IntegerType *>(c.get());

	REQUIRE(nullptr != c_cast);
	REQUIRE(8 == c_cast->getNumber());
}

// ---------------------------------------------------------------------------------------------------------------------

TEST_CASE("operator+(IntegerType, DoubleType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(3);
	std::unique_ptr<Type> b = std::make_unique<DoubleType>(4.5);

	// Act
	std::unique_ptr<Type> c = a + b;

	// Assert
	auto c_cast = dynamic_cast<DoubleType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(7.5 == c_cast->getNumber());
}

TEST_CASE("operator-(IntegerType, DoubleType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(3);
	std::unique_ptr<Type> b = std::make_unique<DoubleType>(4.5);

	// Act
	std::unique_ptr<Type> c = a - b;

	// Assert
	auto c_cast = dynamic_cast<DoubleType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(-1.5 == c_cast->getNumber());
}

TEST_CASE("operator*(IntegerType, DoubleType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(2);
	std::unique_ptr<Type> b = std::make_unique<DoubleType>(4.5);

	// Act
	std::unique_ptr<Type> c = a * b;

	// Assert
	auto c_cast = dynamic_cast<DoubleType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(9 == c_cast->getNumber());
}

TEST_CASE("operator/(IntegerType, DoubleType)_NoRemainder_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(9);
	std::unique_ptr<Type> b = std::make_unique<DoubleType>(4.5);

	// Act
	std::unique_ptr<Type> c = a / b;

	// Assert
	auto c_cast = dynamic_cast<IntegerType *>(c.get());

	REQUIRE(nullptr != c_cast);
	REQUIRE(2 == c_cast->getNumber());
}

TEST_CASE("operator/(IntegerType, DoubleType)_WithRemainder_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(7);
	std::unique_ptr<Type> b = std::make_unique<DoubleType>(4.5);

	// Act
	std::unique_ptr<Type> c = a / b;

	// Assert
	auto c_cast = dynamic_cast<DoubleType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(TableProject::DoubleUtil::isEqual(((long double) 7.0) / 4.5, c_cast->getNumber(), 0.00001));
}

TEST_CASE("operator^(IntegerType, DoubleType)_GoodParams_ReturnedEquals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(2);
	std::unique_ptr<Type> b = std::make_unique<DoubleType>(4.5);

	// Act
	std::unique_ptr<Type> c = a ^b;

	// Assert
	auto c_cast = dynamic_cast<DoubleType *>(c.get());
	REQUIRE(nullptr != c_cast);
	REQUIRE(TableProject::DoubleUtil::isEqual(22.627416998, c_cast->getNumber(), 0.001));
}

TEST_CASE("operator+/operator*(IntegerType, IntegerType)_AssocDistrib_Equals") {
	// Arrange
	std::unique_ptr<Type> a = std::make_unique<IntegerType>(2);
	std::unique_ptr<Type> b = std::make_unique<IntegerType>(3);
	std::unique_ptr<Type> c = std::make_unique<IntegerType>(4);

	// Act and Assert
	REQUIRE(*(a + b) == *(b + a));
	REQUIRE(*(a * b) == *(b * a));

	REQUIRE(*(a + b + c) == *(c + b + a));
	REQUIRE(*(a * b * c) == *(c * b * a));

	REQUIRE(*((a + b) * c) == *(a * c + b * c));
	REQUIRE(*(c * (a + b)) == *(c * a + c * b));
}

// ---------------------------------------------------------------------------------------------------------------------
