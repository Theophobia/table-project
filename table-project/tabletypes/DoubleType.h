#pragma once

#include <table-project/tabletypes/Type.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/StringType.h>

namespace TableProject {
	/**
	 * Type used in cells to represent a floating point number.
	 */
	class DoubleType final : public Type {

	protected:
		long double number = 0;

	public:
		~DoubleType() = default;
		DoubleType() = default;
		explicit DoubleType(long double number);

		/**
		 * Dynamically allocate a copy of this object and return a unique_ptr to it.
		 *
		 * @return
		 */
		operator std::unique_ptr<DoubleType>() const;

		/**
		 * Getter for underlying number.
		 *
		 * @return Floating point number of this object.
		 */
		long double getNumber() const;

		/**
		 * Setter for underlying number.
		 *
		 * @param number
		 */
		void setNumber(long double number);

		void tryParse(const std::string & str) override;
		std::string toString() const override;
		std::string toCSV() const override;
		const std::string & getClass() const override;

		bool operator==(const Type & t) const override;

	};
}