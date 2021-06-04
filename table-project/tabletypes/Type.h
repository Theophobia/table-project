#pragma once

#include <ostream>

class Type {

public:
	virtual ~Type();
	virtual void tryParse(const std::string & str) = 0;
	virtual std::string toString() const = 0;
	
	virtual bool operator==(const Type & t) const = 0;
	
//	std::ostream & operator<<(std::ostream & os) const;
	friend std::ostream & operator<<(std::ostream & os, const Type & type);
	
	static Type * createCopy(const Type & t);
};