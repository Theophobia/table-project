#pragma once

#include <vector>
#include <ostream>

#include <table-project/tabletypes/Type.h>

class FormulaType;

class Table {
	friend class FormulaType;
	
	std::vector<std::vector<Type *>> table;
	
	void trunc();
	void readFromFile(const char * filePath);
	
	/**
	 * Convert index (starts from 0) to column letter (A-Z)
	 *
	 * @param i index to be converted
	 * @return Column letter
	 * @throws std::out_of_range If i is outside alphabet (currently alphabet has size 26)
	 */
	static char indexToColumnLetter(std::size_t i);
	
	static std::size_t columnLetterToIndex(char c);
	static std::pair<std::size_t, std::size_t> cellCoordsToIndices(const std::pair<char, std::size_t> & cellCoords);
public:
	Table() = default;
	Table(const char * filePath);
	
	~Table();
	
	Table(const Table & other);
	Table & operator=(const Table & other);
	
	Table(Table && other) noexcept;
	Table & operator=(Table && other) noexcept;
	
	Type & get(std::size_t i, std::size_t j);
	const Type & get(std::size_t i, std::size_t j) const;
	
	/**
	 *
	 * @param i
	 * @param j
	 * @param t
	 *
	 * @throws std::out_of_range If "j" is greater than or equal to 26
	 */
	void put(std::size_t i, std::size_t j, const Type & t);
	
	std::string toCSV() const;
	
	friend std::ostream & operator<<(std::ostream & os, const Table & table);
//	friend std::istream & operator>>(std::istream & is, Table & table);
};