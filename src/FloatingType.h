#ifndef FLOATINGTYPE_H_zoGwuZzeGRVnyCWuYvDq
#define FLOATINGTYPE_H_zoGwuZzeGRVnyCWuYvDq

#include "Type.h"

class FloatingType : public Type {
protected:
	long double number = 0;

public:
	FloatingType() = default;
	explicit FloatingType(long double number);
	
	long double getNumber() const;
	void setNumber(long double number);
	
	long getClassId() const override;
	void tryParse(const std::string & str) override;
	std::string toString() const override;
};

#endif