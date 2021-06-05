#pragma once

#include <table-project/tabletypes/Type.h>

class Table;

class FormulaType : public Type {

protected:
	std::string formula;
	Type * obj = nullptr;
	
	void calculate(const Table & table, std::size_t thisRow, std::size_t thisCol);
	
public:
	FormulaType() = default;
	explicit FormulaType(const char * str);
	explicit FormulaType(const std::string & str);
	
	~FormulaType();
	
	FormulaType(const FormulaType & other);
	FormulaType & operator=(const FormulaType & other);
	
	FormulaType(FormulaType && other) noexcept;
	FormulaType & operator=(FormulaType && other) noexcept;
	
	void tryParse(const std::string & str) override;
	std::string toString() const override;
	std::string toCSV() const override;
	
	std::string getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol) const;
	std::string getCalculatedValue(const Table & table, std::size_t thisRow, std::size_t thisCol);
	
	bool operator==(const Type & t) const override;
};