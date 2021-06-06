#pragma once

#include <deque>

#include <table-project/tabletypes/Type.h>

class Table;

class FormulaType : public Type {
	static const int FORMULA_DEFAULT_DEPTH = 5;

protected:
	std::string formula;
	std::shared_ptr<Type> obj;

	void calculate(const Table & table, std::size_t thisRow, std::size_t thisCol, int depth = FORMULA_DEFAULT_DEPTH);

	static bool isOperationChar(char c);
	static bool isOperationChar(const std::string & s);
	static std::deque<std::string> tokeniseFormula(const std::string & s);

public:
	FormulaType() = default;
	explicit FormulaType(const char * str);
	explicit FormulaType(const std::string & str);

	~FormulaType() = default;
	FormulaType(const FormulaType & other);
	FormulaType & operator=(const FormulaType & other);
	FormulaType(FormulaType && other) noexcept;
	FormulaType & operator=(FormulaType && other) noexcept;

	void tryParse(const std::string & str) override;
	std::string toString() const override;
	std::string toCSV() const override;
	const std::string & getClass() const override;

	std::string getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol,
								   int depth = FORMULA_DEFAULT_DEPTH) const;

	std::string getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol,
								   int depth = FORMULA_DEFAULT_DEPTH);

	bool operator==(const Type & t) const override;
};