#pragma once

#include <table-project/tabletypes/Type.h>

namespace TableProject {
	class Table;

	/**
	 * Type used in cells to represent a formula, which can contain simple arithmetic and cell references.
	 */
	class FormulaType final : public Type {
		friend class Table;

		/**
		 * Specifies default amount of references into other formulas one FormulaType can execute.
		 */
		static const int FORMULA_DEFAULT_DEPTH = 5;

	protected:
		std::string formula;
		std::shared_ptr<Type> obj;

		/**
		 * Calculate underlying object specified by the given formula.
		 *
		 * @param table Table this object is in.
		 * @param thisRow Row number (n>=1) of this object.
		 * @param thisCol Column number (1 <= n <= 26) of this object.
		 * @param depth Optional, used for calculating references to other formula types.
		 * Gets reduced every time another reference of FormulaType is found.
		 */
		void calculate(Table & table, std::size_t thisRow, std::size_t thisCol, int depth = FORMULA_DEFAULT_DEPTH);

	public:
		~FormulaType() override = default;
		FormulaType() = default;
		explicit FormulaType(const char * str);
		explicit FormulaType(const std::string & str);

		const std::string & getFormula() const;

		void tryParse(const std::string & str) override;
		std::string toString() const override;
		std::string toCSV() const override;
		const std::string & getClass() const override;

		/**
		 * Get underlying calculated object if it exists.
		 * Does not calculate anything.
		 *
		 * @return String representation of calculated object.
		 *
		 * @throws std::runtime_error If calculated object does not exist.
		 */
		std::string getCalculatedValue() const;

		/**
		 * Get underlying calculated object if it exists.
		 * If it doesn't, calculates it using given parameters.
		 *
		 * @param table Table this object is in.
		 * @param thisRow Row number (n>=1) of this object.
		 * @param thisCol Column number (1 <= n <= 26) of this object.
		 * @param depth Optional, used for calculating references to other formula types.
		 * Gets reduced every time another reference of FormulaType is found.
		 *
		 * @return String representation of calculated object.
		 */
		std::string getCalculatedValue(
			Table & table, std::size_t thisRow, std::size_t thisCol,
			int depth = FORMULA_DEFAULT_DEPTH
		);

		bool operator==(const Type & t) const override;
	};
}