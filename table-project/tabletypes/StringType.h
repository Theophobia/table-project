#pragma once

#include <memory>
#include <table-project/tabletypes/Type.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>

namespace TableProject {
	class IntegerType;

	class DoubleType;

	/**
	 * Type used in cells to represent a string
	 */
	class StringType final : public Type {

	protected:
		std::string text;

	public:
		~StringType() = default;
		StringType() = default;
		explicit StringType(const std::string & text);

		const std::string & getText() const;
		void setText(const std::string & text);

		void tryParse(const std::string & str) override;
		std::string toString() const override;
		std::string toCSV() const override;
		const std::string & getClass() const override;

		/**
		 * @return true if object's text representation can be casted to an IntegerType
		 */
		bool isIntegerCastable() const;

		/**
		 * @return true if object's text representation can be casted to a DoubleType
		 */
		bool isDoubleCastable() const;

		/**
		 * Casts this object to an integer, if it can.
		 *
		 * @return A IntegerType object whose number is casted from this object's text
		 *
		 * @throws  std::runtime_error If object is not IntegerType-castable
		 */
		explicit operator IntegerType() const;

		/**
		 * Casts this object to a double, if it can.
		 *
		 * @return A DoubleType object whose number is casted from this object's text
		 *
		 * @throws  std::runtime_error If object is not DoubleType-castable
		 */
		explicit operator DoubleType() const;

		bool operator==(const Type & t) const override;

		static StringType getError();
	};
}