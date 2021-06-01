#ifndef TABLE_INTEGERTYPE_H
#define TABLE_INTEGERTYPE_H

#include "base/Type.h"

/**
 * Type used in cells to represent a 64-bit integer.
 * <p>
 *
 */
class IntegerType : public Type {
private:

protected:
	std::int64_t number = 0;
	
public:
	IntegerType() = default;
	explicit IntegerType(std::int64_t number);
	
	std::int64_t getNumber() const;
	void setNumber(std::int64_t number);
	
//	int getClassId() const override;
	void tryParse(const std::string & str) override;
	std::string toString() const override;
};

#endif