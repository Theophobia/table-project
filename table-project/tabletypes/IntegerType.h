#pragma once

#include <memory>
#include <table-project/tabletypes/Type.h>

namespace TableProject {
	/**
	 * Type used in cells to represent a 64-bit integer.
	 */
	class IntegerType final : public Type {

	protected:
		std::int64_t number = 0;

	public:
		~IntegerType() = default;
		IntegerType() = default;
		explicit IntegerType(std::int64_t number);

		/**
		 * Dynamically allocate a copy of this object and return a shared_ptr to it.
		 *
		 * @return
		 */
		operator std::shared_ptr<IntegerType>() const;

		/**
		 * Getter for underlying number.
		 *
		 * @return 64-bit number of this object.
		 */
		std::int64_t getNumber() const;

		/**
		 * Setter for underlying number.
		 *
		 * @param number
		 */
		void setNumber(std::int64_t number);

		void tryParse(const std::string & str) override;
		std::string toString() const override;
		std::string toCSV() const override;
		const std::string & getClass() const override;

		bool operator==(const Type & t) const override;
	};
}