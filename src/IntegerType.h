#ifndef INTEGERTYPE_H_RKOoJbSkOSMYNvLTyOsx
#define INTEGERTYPE_H_RKOoJbSkOSMYNvLTyOsx

#include "Type.h"

class IntegerType : public Type {
protected:
	long long number = 0;
	
public:
	IntegerType() = default;
	explicit IntegerType(long long number);
	
	long long getNumber() const;
	void setNumber(long long number);
	
	long getClassId() const override;
	void tryParse(const std::string & str) override;
	std::string toString() const override;
};

#endif