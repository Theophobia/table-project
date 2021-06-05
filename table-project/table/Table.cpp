#include <fstream>
#include <iomanip>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/FormulaType.h>

void Table::trunc() {
	this->table.clear();
}

void Table::readFromFile(const char * filePath) {
	std::ifstream fileIn(filePath, std::ios::in);
	if (!fileIn) {
		throw std::runtime_error("File could not be opened for reading into table");
	}
	
	std::ostringstream buffer;
	std::size_t currRow = 0;
	std::size_t currCol = 0;
	
	char c; // TODO check
	while (true) {
		fileIn >> c;
		
		if (!fileIn) {
			break;
		}
		
		if (c == ',') {
			if (!buffer.str().empty()) {
				// TODO parse and table.put() here
			}
			
			currCol++;
			buffer.clear();
			continue;
		}
		if (c == '\n') {
			if (!buffer.str().empty()) {
				// TODO parse and table.put() here
			}
			
			currRow++;
			currCol = 0;
			buffer.clear();
			continue;
		}
		
		buffer << c;
	}
	
}

char Table::indexToColumnLetter(std::size_t i) {
	static const std::string digits = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return digits.at(i);
}

std::size_t Table::columnLetterToIndex(char c) {
	bool isBetween_AZ = (c >= 'A' && c <= 'Z');
	bool isBetween_az = (c >= 'a' && c <= 'z');
	
	if (!isBetween_AZ && !isBetween_az) {
		throw std::invalid_argument("Column letter character must be between 'A' and 'Z' or 'a' and 'z'");
	}
	
	return c - 'A';
}

std::pair<std::size_t, std::size_t> Table::cellCoordsToIndices(const std::pair<char, std::size_t> & cellCoords) {
	std::pair<std::size_t, std::size_t> result;
	return result;
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

Type & Table::get(std::size_t i, std::size_t j) {
	if (table.size() <= i) {
		throw std::out_of_range("Row out of bounds");
	}
	
	const std::vector<Type *> & row = table[i];
	
	if (row.size() <= j) {
		throw std::out_of_range("Column out of bounds");
	}
	
	Type * elem = row[j];
	return *elem;
}

const Type & Table::get(std::size_t i, std::size_t j) const {
	return const_cast<Table *>(this)->get(i, j);
}

void Table::put(std::size_t i, std::size_t j, const Type & t) {
	// To prevent adding empty columns before
	// actually checking if "j" is outside bounds
	if (j >= 26) {
		throw std::out_of_range("Cannot insert element outside column 26");
	}
	
	Type * copied = Type::createCopy(t);
	
	// Check if row exists, if not add empty
	while (table.size() <= i) {
		table.emplace_back();
	}
	std::vector<Type *> & specifiedRow = table.at(i);
	
	// Check if column exists, if not add empty
	while (specifiedRow.size() <= j) {
		specifiedRow.push_back(nullptr);
	}
	auto & specifiedElement = specifiedRow.at(j);
	
	// If element exists, remove it
	delete specifiedElement;
	
	specifiedElement = copied;
}

std::string Table::toCSV() const {
	std::ostringstream result;
	for (std::size_t i = 0; i < table.size(); i++) {
		if (i != 0) {
			result << '\n';
		}
		
		auto row = table[i];
		for (std::size_t j = 0; j < row.size(); j++) {
			if (j != 0) {
				result << ',';
			}
			
			auto elem = row[j];
			if (elem != nullptr) {
				result << elem->toCSV();
			}
		}
	}
	return result.str();
}

std::ostream & operator<<(std::ostream & os, const Table & t) {
	std::size_t columns = 0;
	std::size_t rows = t.table.size();
	std::size_t maxElemLen = 0;
	
	for (const auto & row : t.table) {
		if (row.size() > columns) {
			columns = row.size();
		}
	}
	
	// Pre-calculate formula type cells
	// This is done to correctly calculate max size
	for (std::size_t j = 0; j < columns; j++) {
		for (std::size_t i = 0; i < rows; i++) {
			try {
				Type * elem = t.table.at(i).at(j);
				if (elem == nullptr) {
					continue;
				}
				auto * maybeFormulaType = dynamic_cast<FormulaType *>(elem);
				if (maybeFormulaType != nullptr) {
					maybeFormulaType->getCalculatedValue(t, i, j).size();
				}
			}
			catch (std::exception &) {}
		}
	}
	
	std::size_t * colMaxElemLen = new std::size_t[columns](); // zeroes elements
	
	for (std::size_t j = 0; j < columns; j++) {
		for (std::size_t i = 0; i < rows; i++) {
			try {
				Type * elem = t.table.at(i).at(j);
				if (elem == nullptr) {
					continue;
				}
				
				std::size_t elemLen = elem->toString().size();
				
				auto * maybeFormulaType = dynamic_cast<FormulaType *>(elem);
				if (maybeFormulaType != nullptr) {
					elemLen = maybeFormulaType->getCalculatedValue(t, i, j).size();
				}
				
				if (elemLen > colMaxElemLen[j]) {
					colMaxElemLen[j] = elemLen;
				}
			}
			catch (std::exception &) {
			
			}
		}
	}
	
	const std::size_t rowsStrLen = std::to_string(columns).size();
	if (rowsStrLen > maxElemLen) {
		maxElemLen = rowsStrLen;
	}
	
	const std::size_t ELEMENTS_IN_ALPHABET = 26;
	if (columns > ELEMENTS_IN_ALPHABET) {
		delete[] colMaxElemLen;
		throw std::runtime_error("Table has more than 26 columns");
	}
	
	// Print column header
	// First is the empty part where column and row headers meet
	os << "\n " << std::setw(rowsStrLen) << std::setfill(' ') << ' ' << " |";
	for (std::size_t i = 0; i < columns; i++) {
		// This is the column letter part
		os << ' ' << std::setw(colMaxElemLen[i]) << std::setfill(' ') << Table::indexToColumnLetter(i) << " |";
	}
	
	for (std::size_t i = 0; i < rows; i++) {
		const auto & row = t.table[i];
		os << "\n " << std::setw(rowsStrLen) << std::setfill(' ') << std::to_string(i + 1) << " |";
		
		for (std::size_t j = 0; j < columns; j++) {
			Type * elem = nullptr;
			try {
				elem = t.table.at(i).at(j);
			}
			catch (std::exception &) {}
			
			os << ' ' << std::setw(colMaxElemLen[j]) << std::setfill(' ');
			if (elem == nullptr) {
				os << ' ';
			}
			else {
				FormulaType * casted = dynamic_cast<FormulaType *>(elem);
				
				// Check if FormulaType, else normal output
				if (casted == nullptr) {
					os << *elem;
				}
				else {
					os << casted->getCalculatedValue(t, i, j);
				}
			}
			
			os << " |";
		}
	}
	os << std::endl;
	
	delete[] colMaxElemLen;
	return os;
}
