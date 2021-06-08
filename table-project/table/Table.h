#pragma once

#include <vector>
#include <ostream>

#include <table-project/tabletypes/Type.h>
#include <table-project/tabletypes/FormulaType.h>


namespace TableProject {
	class FormulaType;

	/**
	 * Class representing a jagged matrix with various Types.
	 * Can do simple calculations and grid visualisations.
	 */
	class Table {

	protected:
		friend class FormulaType;

		std::vector<std::vector<std::shared_ptr<Type>>> table;

	public:
		~Table() = default;
		Table() = default;

		/**
		 * Creates table using the contents of a CSV-formatted file.
		 *
		 * @param filePath File path to be used
		 */
		explicit Table(const std::string & filePath);

		Table(const Table & other);
		Table & operator=(const Table & other);
		Table(Table && other) noexcept;
		Table & operator=(Table && other) noexcept;

		/**
		 * Check for element at specified "rowIndex" and "columnIndex".
		 *
		 * @param rowIndex
		 * @param columnIndex
		 * @return Object at specified indices
		 *
		 * @throws
		 * 		std::out_of_range If indices are out of bounds.
		 * 		NoSuchElementError If no element is at that position.
		 */
		Type & get(std::size_t rowIndex, std::size_t columnIndex);

		/**
		 * Check for element at specified "rowIndex" and "columnIndex".
		 *
		 * @param rowIndex
		 * @param columnIndex
		 * @return Object at specified indices
		 *
		 * @throws
		 * 		std::out_of_range If indices are out of bounds.
		 * 		NoSuchElementError If no element is at that position.
		 */
		const Type & get(std::size_t rowIndex, std::size_t columnIndex) const;

		/**
		 * Places a copy of the specified element at the specified position.
		 *
		 * @param rowIndex
		 * @param columnIndex
		 * @param type
		 *
		 * @throws
		 * 		std::out_of_range If "columnIndex" is greater than 25
		 */
		void put(std::size_t rowIndex, std::size_t columnIndex, const Type & type);

		/**
		 * Convert object to CSV-formatted string.
		 * Uses ',' for column separation and '\n' for row separation.
		 *
		 * @return CSV-formatted string
		 */
		std::string toCSV() const;

		/**
		 * Calculates all formulas
		 */
		void calculate();

		friend std::ostream & operator<<(std::ostream & os, Table & table);

		/**
		 * Convert index (starts from 0) to column letter (A-Z).
		 *
		 * @param i index to be converted
		 * @return Column letter
		 *
		 * @throws
		 * 		std::out_of_range If i is outside alphabet (currently alphabet has size 26)
		 */
		static char indexToColumnLetter(std::size_t i);

		/**
		 * Convert letter to index.
		 *
		 * @param c
		 * @return
		 */
		static std::size_t columnLetterToIndex(char c);

		/**
		 * Convert cell location to indices.
		 *
		 * @param cellCoords
		 * @return (rowIndex, colIndex)
		 *
		 * @throws
		 * 		std::invalid_argument If string is not a cell coordinate
		 */
		static std::pair<std::size_t, std::size_t> cellCoordsToIndices(const std::string & cellCoords);
	};
}