#include <table-project-tests/doctest.h>

#include <table-project/TableProject.h>

using namespace TableProject;

TEST_CASE("Parser_computeSimpleExpression()_IT+IT_Equals") {
    // Arrange
    std::int64_t num1 = 123;
	std::int64_t num2 = 124;
	std::int64_t num3 = num1 + num2;

    IntegerType t1(num1);
	IntegerType t2(num2);
	IntegerType t3(num3);

    // Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

    // Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_IT+DT_Equals") {
	// Arrange
	std::int64_t num1 = 123;
	long double num2 = 123.4;
	long double num3 = num1 + num2;

	IntegerType t1(num1);
	DoubleType t2(num2);
	DoubleType t3(num3);

	// Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

	// Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_DT+DT_Equals") {
	// Arrange
	long double num1 = 1.2;
	long double num2 = 1.3;
	long double num3 = num1 + num2;

	DoubleType t1(num1);
	DoubleType t2(num2);
	DoubleType t3(num3);

	// Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

	// Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_ST(castIT)+IT_Equals") {
	// Arrange
	std::string num1 = "1";
	std::int64_t num2 = 2;
	std::int64_t num3 = std::stoi(num1) + num2;

	StringType t1(num1);
	IntegerType t2(num2);
	IntegerType t3(num3);

	// Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

	// Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_ST(castDT)+IT_Equals") {
	// Arrange
	std::string num1 = "1.2";
	std::int64_t num2 = 2;
	long double num3 = std::stold(num1) + num2;

	StringType t1(num1);
	IntegerType t2(num2);
	DoubleType t3(num3);

	// Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

	// Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_ST(castIT)+DT_Equals") {
	// Arrange
	std::string num1 = "1";
	long double num2 = 2.3;
	long double num3 = std::stoi(num1) + num2;

	StringType t1(num1);
	DoubleType t2(num2);
	DoubleType t3(num3);

	// Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

	// Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_ST(castDT)+DT_Equals") {
	// Arrange
	std::string num1 = "1.2";
	long double num2 = 2.3;
	long double num3 = std::stold(num1) + num2;

	StringType t1(num1);
	DoubleType t2(num2);
	DoubleType t3(num3);

	// Act
	std::string computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());

	// Assert
	REQUIRE(t3.toString() == computed);
}


TEST_CASE("Parser_computeSimpleExpression()_ST(castIT)@IT_Equals") {
	// Arrange
	std::string num1 = "12";
	std::int64_t num2 = 13;
	std::int64_t num3;

	StringType t1(num1);
	IntegerType t2(num2);
	IntegerType t3;
	std::string computed;

	SUBCASE("@ = +") {
		num3 = std::stoll(num1) + num2;
		t3 = IntegerType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());
	}
	SUBCASE("@ = -") {
		num3 = std::stoll(num1) - num2;
		t3 = IntegerType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '-', t2.toString());
	}
	SUBCASE("@ = *") {
		num3 = std::stoll(num1) * num2;
		t3 = IntegerType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '*', t2.toString());
	}
//	SUBCASE("@ = /") {
//		num3 = std::stoll(num1) / num2;
//		t3 = IntegerType(num3);
//
//		// Act
//		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '/', t2.toString());
//	}
	SUBCASE("@ = ^") {
		num3 = std::pow(std::stoll(num1), num2);
		t3 = IntegerType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '^', t2.toString());
	}

	// Assert
	REQUIRE(t3.toString() == computed);
}

TEST_CASE("Parser_computeSimpleExpression()_ST(castDT)@DT_Equals") {
	// Arrange
	std::string num1 = "1.2";
	long double num2 = 2.3;
	long double num3;

	StringType t1(num1);
	DoubleType t2(num2);
	DoubleType t3;
	std::string computed;

	SUBCASE("@ = +") {
		num3 = std::stold(num1) + num2;
		t3 = DoubleType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '+', t2.toString());
	}
	SUBCASE("@ = -") {
		num3 = std::stold(num1) - num2;
		t3 = DoubleType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '-', t2.toString());
	}
	SUBCASE("@ = *") {
		num3 = std::stold(num1) * num2;
		t3 = DoubleType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '*', t2.toString());
	}
	SUBCASE("@ = /") {
		num3 = std::stold(num1) / num2;
		t3 = DoubleType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '/', t2.toString());
	}
	SUBCASE("@ = ^") {
		num3 = std::pow(std::stold(num1), num2);
		t3 = DoubleType(num3);

		// Act
		computed = TableProject::Parser::computeSimpleExpression(t1.toString(), '^', t2.toString());
	}

	// Assert
	REQUIRE(TableProject::DoubleUtil::isEqual(std::stold(t3.toString()), std::stold(computed), 0.0001));
}

TEST_CASE("Parser_parse()_123+123_Equals256") {
    // Arrange

    // Act
    std::string result = TableProject::Parser::parse("123+123");

    // Assert
	REQUIRE("246" == result);
}

TEST_CASE("Parser_parse()_12-11_Equals1") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("12-11");

	// Assert
	REQUIRE("1" == result);
}

TEST_CASE("Parser_parse()_-12+11_Equals-1") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("-12+11");

	// Assert
	REQUIRE("-1" == result);
}

TEST_CASE("Parser_parse()_12-12_Equals0") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("12-12");

	// Assert
	REQUIRE("0" == result);
}

TEST_CASE("Parser_parse()_-12+12_Equals0") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("-12+12");

	// Assert
	REQUIRE("0" == result);
}

TEST_CASE("Parser_parse()_12*12_Equals144") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("12*12");

	// Assert
	REQUIRE("144" == result);
}


TEST_CASE("Parser_parse()_1-3*4+2_Equals-9") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("1-3*4+2");

	// Assert
	REQUIRE("-9" == result);
}

TEST_CASE("Parser_parse()_-1+3^2-5*3+2*1_Equals-5") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("-1+3^2-5*3+2*1");

	// Assert
	REQUIRE("-5" == result);
}

TEST_CASE("Parser_parse()_-1-3^2-5_Equals-15") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("-1-3^2-5");

	// Assert
	REQUIRE("-15" == result);
}

TEST_CASE("Parser_parse()_4^-2_Equals0.0625") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("4^-2");

	// Assert
	REQUIRE("0.0625" == result);
}

TEST_CASE("Parser_parse()_-4^-2_Equals-0.0625") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("-4^-2");

	// Assert
	REQUIRE("-0.0625" == result);
}

TEST_CASE("Parser_parse()_-4^-2*2*8_Equals-1") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("-4^-2*2*8");

	// Assert
	REQUIRE("-1" == result);
}

TEST_CASE("Parser_parse()_5+3*3-2^6+45/2_Equals-27.5") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("5+3*3-2^6+45/2");

	// Assert
	REQUIRE("-27.5" == result);
}

TEST_CASE("Parser_parse()_5+3*3-2^6+3*2/3^4/2_Equals-49.962963") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("5+3*3-2^6+3*2/3^4/2");

	// Assert
	REQUIRE("-49.962963" == result);
}

TEST_CASE("Parser_parse()_5-3*3-2^5+3*2/3^4/2_Equals-35.962963") {
	// Arrange

	// Act
	std::string result = TableProject::Parser::parse("5-3*3-2^5+3*2/3^4/2");

	// Assert
	REQUIRE("-35.962963" == result);
}

/*
 * Checked with https://www.wolframalpha.com
 */