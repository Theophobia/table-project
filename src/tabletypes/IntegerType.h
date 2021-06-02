#ifndef TABLE_INTEGERTYPE_H
#define TABLE_INTEGERTYPE_H

#include "base/Type.h"

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
	
	std::int64_t getNumber() const;
	void setNumber(std::int64_t number);
	
	void tryParse(const std::string & str) override;
	std::string toString() const override;
	
	bool operator==(const Type & t) const override;
};

#endif