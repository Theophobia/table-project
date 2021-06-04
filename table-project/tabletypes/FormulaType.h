#pragma once

#include <table-project/tabletypes/Type.h>

class Table;

class FormulaType : public Type {

protected:
	std::string formula;
	Type * obj = nullptr;
	
	void calculate(const Table & table);
	
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
	
	bool operator==(const Type & t) const override;
};