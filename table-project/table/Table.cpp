#include <fstream>
#include <iomanip>
#include <memory>

#include <table-project/TableProject.h>
#include <table-project/exception/NoSuchElementError.h>

namespace TableProject {
	Table::Table(const std::string & filePath) {
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
					std::shared_ptr<Type> typePtr(Type::fromString(buffer));
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
		if (!buffer.empty()) {
			std::shared_ptr<Type> typePtr(Type::fromString(buffer));
			this->put(row, col, *typePtr);
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
		if (elem == nullptr) {
			throw TableProject::NoSuchElementError("Element is null");
		}

		return *elem;
	}

	const Type & Table::get(std::size_t rowIndex, std::size_t columnIndex) const {
		return const_cast<Table *>(this)->get(rowIndex, columnIndex);
	}

//std::string Table::getStringRepresentation(std::size_t rowIndex, std::size_t columnIndex) {
//	calculate();
//	return get(rowIndex, columnIndex).toString();
//}

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

	void Table::calculate() {
		for (std::size_t rowIndex = 0; rowIndex < table.size(); rowIndex++) {
			auto & row = table[rowIndex];
			for (std::size_t colIndex = 0; colIndex < row.size(); colIndex++) {
				std::shared_ptr<Type> & elem = row[colIndex];
				if (elem != nullptr && elem->getClass() == FormulaType().getClass()) {
					((FormulaType &) *elem).calculate(*this, rowIndex + 1, colIndex + 1);
				}
			}
		}
	}

	std::ostream & operator<<(std::ostream & os, Table & t) {
		std::size_t columns = 0;
		std::size_t rows = t.table.size();
		std::size_t maxElemLen = 0;

		for (const auto & row : t.table) {
			if (row.size() > columns) {
				columns = row.size();
			}
		}

		// Nothing to print if there are no rows or columns
		if (rows == 0 || columns == 0) {
			return os;
		}

		// Pre-calculate formula type cells
		// This is done to correctly calculate max size
		t.calculate();

		std::vector<std::size_t> colMaxElemLen(columns);

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
			throw std::runtime_error("Table has more than 26 columns");
		}

		// Print column header
		// First is the empty part where column and row headers meet
		os << "\n " << std::setw(rowsStrLen) << std::setfill(' ') << ' ' << " |";
		for (std::size_t i = 0; i < columns; i++) {
			// This is the column letter part
			os << ' ' << std::setw(colMaxElemLen[i]) << std::setfill(' ') << TableProject::Table::indexToColumnLetter(i)
			   << " |";
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
				if (elem != nullptr) {
					os << *elem;
				}
				else {
					os << ' ';
				}
				os << " |";
			}
		}
		os << std::endl;

		return os;
	}

	char TableProject::Table::indexToColumnLetter(std::size_t i) {
		static const std::string digits = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		return digits.at(i);
	}

	std::size_t TableProject::Table::columnLetterToIndex(char c) {
		bool isBetween_AZ = (c >= 'A' && c <= 'Z');
		bool isBetween_az = (c >= 'a' && c <= 'z');

		if (isBetween_az) {
			return c - 'a';
		}
		else if (isBetween_AZ) {
			return c - 'A';
		}
		else {
			throw std::invalid_argument("Column letter character must be between 'A' and 'Z' or 'a' and 'z'");
		}
	}

	std::pair<std::size_t, std::size_t> TableProject::Table::cellCoordsToIndices(const std::string & cellCoords) {
		if (cellCoords.size() < 2) {
			throw std::invalid_argument("Invalid cell coordinates, size must be at least of length 2");
		}

		if (!std::isalpha(cellCoords[0])) {
			throw std::invalid_argument("Invalid cell coordinates, first character must be a letter");
		}

		std::size_t rowIndex = 0;
		for (std::size_t i = 1; i < cellCoords.size(); i++) {
			if (!std::isdigit(cellCoords[i])) {
				std::string errMsg;
				errMsg += "Invalid cell coordinates, character at index " + std::to_string(i) + " must be a digit";
				throw std::invalid_argument(errMsg);
			}
			rowIndex = 10 * rowIndex + cellCoords[i] - '0';
		}
		rowIndex--;
		std::size_t colIndex = columnLetterToIndex(cellCoords[0]);

		return std::pair<std::size_t, std::size_t>(rowIndex, colIndex);
	}
}