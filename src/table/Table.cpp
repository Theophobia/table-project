#include "Table.h"
#include "../exception/NoSuchElementError.h"

Table::~Table() {
	for (const std::vector<Type *> & row : table) {
		for (const Type * elem : row) {
			delete elem;
		}
	}
}

Table::Table(const Table & other) {
	*this = other;
}

Table & Table::operator=(const Table & other) {
	return *this;
}

Table::Table(Table && other) noexcept {
	*this = std::move(other);
}

Table & Table::operator=(Table && other) noexcept {
	this->table = std::move(other.table);
	return *this;
}

//const Type & Table::getType(int i, int j) const {
//	get<Type>
//	return <#initializer#>;
//}

const IntegerType & Table::getInteger(int i, int j) const {
	return *this->get<IntegerType>(i, j);
}

const DoubleType & Table::getDouble(int i, int j) const {
	return *this->get<DoubleType>(i, j);
}

const StringType & Table::getString(int i, int j) const {
	return *this->get<StringType>(i, j);
}

const FormulaType & Table::getFormula(int i, int j) const {
	return *this->get<FormulaType>(i, j);
}
