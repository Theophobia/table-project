#pragma once

#include <vector>

#include "../tabletypes/base/Type.h"
#include "../tabletypes/IntegerType.h"
#include "../tabletypes/DoubleType.h"
#include "../tabletypes/StringType.h"
#include "../tabletypes/FormulaType.h"
#include "../exception/NoSuchElementError.h"

class FormulaType;

class Table {
	friend class FormulaType;

// Expose private members for testing
// Not the best, not the worst, but it is easy
#ifdef TABLE_TEST
	public:
#endif
	
	std::vector<std::vector<Type *>> table;
	
	template<class T>
	T * get(int i, int j) const {
		const std::vector<Type *> & row = table.at(i);
		if (row.empty()) {
			throw NoSuchElementError("There is no element at the specified location");
		}
		
		Type * elem = row.at(j);
		if (elem == nullptr) {
			throw NoSuchElementError("There is no element at the specified location");
		}
		
		T * tptr = dynamic_cast<T *>(elem);
		if (tptr == nullptr) {
			throw std::invalid_argument("Cell could not be cast");
		}
		
		return tptr;
	}
	
	template<class T>
	void put(int i, int j, const T & t) {
		Type * copied = new T(t);
		
		// Check if row exists, if not add empty
		while (table.size() <= i) {
			table.push_back(std::vector<Type *>());
		}
		std::vector<Type *> & specifiedRow = table.at(i);
		
		// Check if column exists, if not add empty
		while (specifiedRow.size() <= j) {
			specifiedRow.push_back(nullptr);
		}
		auto & specifiedElement = specifiedRow.at(j);
		
		// If element exists, remove it
		if (specifiedElement != nullptr) {
			delete specifiedElement;
		}
		
		specifiedElement = copied;
	}

public:
	Table() = default;
	~Table();
	
	Table(const Table & other);
	Table & operator=(const Table & other);
	
	Table(Table && other) noexcept;
	Table & operator=(Table && other) noexcept;
	
	const Type & getType(int i, int j) const;
	
	const IntegerType & getInteger(int i, int j) const;
	const DoubleType & getDouble(int i, int j) const;
	const StringType & getString(int i, int j) const;
	const FormulaType & getFormula(int i, int j) const;
	
};