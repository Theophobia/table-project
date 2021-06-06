#pragma once

#include <memory>
#include "Type.h"

namespace TableProject {
/**
 * Type used in cells to represent a 64-bit integer.
 * <p>
 *
 */
	class IntegerType : public Type {

	protected:
		std::int64_t number = 0;

	public:
		IntegerType() = default;
		explicit IntegerType(std::int64_t number);

		~IntegerType() = default;

		IntegerType(const IntegerType & other);
		IntegerType & operator=(const IntegerType & other);

		IntegerType(IntegerType && other) noexcept;
		IntegerType & operator=(IntegerType && other) noexcept;

		operator std::shared_ptr<IntegerType>() const;

		std::int64_t getNumber() const;
		void setNumber(std::int64_t number);

		void tryParse(const std::string & str) override;
		std::string toString() const override;
		std::string toCSV() const override;
		const std::string & getClass() const override;

		bool operator==(const Type & t) const override;
	};
}