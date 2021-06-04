#include <fstream>

#include <table-project/table/Table.h>
#include <iomanip>

char Table::indexToColumnLetter(std::size_t i) {
	static char digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return digits[i];
}

Table::Table(const char * filePath) {
	std::ifstream fileIn(filePath, std::ios::in);
	if (!fileIn) {
		throw std::invalid_argument("Could not open file");
	}
	
	
}

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

Type & Table::get(int i, int j) {
	if (table.size() <= i) {
		throw std::out_of_range("Row out of bounds");
	}
	
	const std::vector<Type *> & row = table.at(i);
	
	if (row.size() <= j) {
		throw std::out_of_range("Column out of bounds");
	}
	
	Type * elem = row.at(j);
	return *elem;
}

const Type & Table::get(int i, int j) const {
	return const_cast<Table *>(this)->get(i, j);
}

void Table::put(int i, int j, const Type & t) {
	Type * copied = Type::createCopy(t);
	
	// Check if row exists, if not add empty
	while (table.size() <= i) {
		table.emplace_back();
	}
	std::vector<Type *> & specifiedRow = table.at(i);
	
	// Check if column exists, if not add empty
	while (specifiedRow.size() <= j) {
//		specifiedRow.emplace_back();
		specifiedRow.push_back(nullptr);
	}
	auto & specifiedElement = specifiedRow.at(j);
	
	// If element exists, remove it
	delete specifiedElement;
	
	specifiedElement = copied;
}

std::ostream & operator<<(std::ostream & os, const Table & table) {
	
	std::size_t columns = 0;
	std::size_t rows = table.table.size();
	std::size_t maxElemLen = 0;
	
	for (const auto & row : table.table) {
		if (row.size() > columns) {
			columns = row.size();
		}
		
		for (const auto & elem : row) {
			if (elem == nullptr) {
				continue;
			}
			
			auto elemLen = elem->toString().size();
			if (elemLen > maxElemLen) {
				maxElemLen = elemLen;
			}
		}
	}
	
	const std::size_t rowsStrLen = std::to_string(columns).size();
	if (rowsStrLen > maxElemLen) {
		maxElemLen = rowsStrLen;
	}
	
	const std::size_t ELEMENTS_IN_ALPHABET = 26; // TODO extract this somewhere
	if (columns > ELEMENTS_IN_ALPHABET) {
		throw std::runtime_error("Table has more than 26 columns");
	}
//	const std::size_t columnsStrLen = 1 + (rows - 1) / ELEMENTS_IN_ALPHABET;
//	if (columnsStrLen > maxElemLen) {
//		maxElemLen = columnsStrLen;
//	}
	
	os << "\n " << std::setw(rowsStrLen) << std::setfill(' ') << ' ' << " |"; // TODO check this
	for (std::size_t i = 0; i < columns; i++) {
		os << ' ' << std::setw(maxElemLen) << std::setfill(' ') << Table::indexToColumnLetter(i) << " |";
	}
	
	for (std::size_t i = 0; i < rows; i++) {
		auto row = table.table[i];
		os << "\n " << std::setw(rowsStrLen) << std::setfill(' ') << std::to_string(i + 1) << " |";
		for (std::size_t j = 0; j < columns; j++) {
			std::string elemToString = " ";
			try {
				table.table.at(i).at(j);
				Type * elem = table.table[i][j];
				if (elem != nullptr) {
					elemToString = elem->toString();
				}
			}
			catch (std::exception &) {
			
			}
			
			os << ' ' << std::setw(maxElemLen) << std::setfill(' ') << elemToString << " |";
		}
	}
	os << std::endl;
	
	
	return os;
}
