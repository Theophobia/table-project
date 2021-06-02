#ifndef TABLE_DOUBLETYPE_H
#define TABLE_DOUBLETYPE_H

#include "base/Type.h"

class DoubleType : public Type {

protected:
	long double number = 0;

public:
	DoubleType() = default;
	explicit DoubleType(long double number);
	
	long double getNumber() const;
	void setNumber(long double number);
	
	void tryParse(const std::string & str) override;
	std::string toString() const override;
	
	bool operator==(const Type & t) const override;
};

#endif