#include <fstream>
#include <iomanip>
#include <memory>

#include <table-project/table/Table.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/tabletypes/StringType.h>

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
	
	std::size_t row = 0;
	std::size_t col = 0;
	
	std::string buffer;
	char c;
	while (fileIn.get(c)) {
		if (c == ',' || c == '\n') {
			try {
				std::shared_ptr<Type> typePtr(Type::fromString(buffer.c_str()));
				this->put(row, col, *typePtr);
			}
			catch (std::exception & e) {
				std::string s;
				s += "Could not read table from file: ";
				s += "(rowIndex=" + std::to_string(row) + ", ";
				s += "colIndex=" + std::to_string(col) + "): ";
				s += e.what();
				throw std::runtime_error(s);
			}
			
			if (c == ',') {
				col++;
				buffer.clear();
			}
			else { // c == '\n'
				col = 0;
				row++;
				buffer.clear();
			}
		}
		else {
			buffer += c;
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

Type & Table::get(std::size_t rowIndex, std::size_t columnIndex) {
	if (table.size() <= rowIndex) {
		throw std::out_of_range("Row out of bounds");
	}

	std::vector<std::shared_ptr<Type>> & row = table[rowIndex];
	
	if (row.size() <= columnIndex) {
		throw std::out_of_range("Column out of bounds");
	}

	std::shared_ptr<Type> elem = row[columnIndex];
	return *elem;
}

const Type & Table::get(std::size_t rowIndex, std::size_t columnIndex) const {
	return const_cast<Table *>(this)->get(rowIndex, columnIndex);
}

void Table::put(std::size_t rowIndex, std::size_t columnIndex, const Type & type) {
	// To prevent adding empty columns before
	// actually checking if "columnIndex" is outside bounds
	if (columnIndex >= 26) {
		throw std::out_of_range("Cannot insert element outside column 26");
	}

	std::shared_ptr<Type> copied = Type::createCopy(type);
	
	// Check if row exists, if not add empty
	while (table.size() <= rowIndex) {
		table.emplace_back();
	}
	std::vector<std::shared_ptr<Type>> & specifiedRow = table.at(rowIndex);
	
	// Check if column exists, if not add empty
	while (specifiedRow.size() <= columnIndex) {
		specifiedRow.push_back(nullptr);
	}
	auto & specifiedElement = specifiedRow.at(columnIndex);
	
	// If element exists, remove it
//	delete specifiedElement;
	
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
				const std::shared_ptr<Type> & elem = t.table.at(i).at(j);
				if (elem == nullptr) {
					continue;
				}
				auto * maybeFormulaType = dynamic_cast<FormulaType *>(elem.get());
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
				const std::shared_ptr<Type> & elem = t.table.at(i).at(j);
				if (elem == nullptr) {
					continue;
				}
				
				std::size_t elemLen = elem->toString().size();
				
				auto * maybeFormulaType = dynamic_cast<FormulaType *>(elem.get());
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
			std::shared_ptr<Type> elem = nullptr;
			try {
				elem = t.table.at(i).at(j);
			}
			catch (std::exception &) {}
			
			os << ' ' << std::setw(colMaxElemLen[j]) << std::setfill(' ');
			if (elem == nullptr) {
				os << ' ';
			}
			else {
				FormulaType * casted = dynamic_cast<FormulaType *>(elem.get());
				
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
