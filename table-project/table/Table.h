#pragma once

#include <vector>

#include <table-project/tabletypes/Type.h>
#include <ostream>

class FormulaType;

class Table {
	friend class FormulaType;

// Expose private members for testing
// Not the best, not the worst, but it is easy
//#ifdef TABLE_TEST
//	public:
//#endif
	
	std::vector<std::vector<Type *>> table;
	
	void trunc();
	void readFromFile(const char * filePath);
	
	static char indexToColumnLetter(std::size_t i);
public:
	Table() = default;
	Table(const char * filePath);
	
	~Table();
	
	Table(const Table & other);
	Table & operator=(const Table & other);
	
	Table(Table && other) noexcept;
	Table & operator=(Table && other) noexcept;
	
	Type & get(int i, int j);
	const Type & get(int i, int j) const;
	
	void put(int i, int j, const Type & t);
	
	friend std::ostream & operator<<(std::ostream & os, const Table & table);
	friend std::istream & operator>>(std::istream & is, Table & table);
};