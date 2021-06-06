#pragma once

#include <ostream>
#include <bits/shared_ptr.h>

class Type {

public:
	virtual ~Type();
	virtual void tryParse(const std::string & str) = 0;
	virtual std::string toString() const = 0;
	virtual std::string toCSV() const = 0;
	virtual const std::string & getClass() const = 0;
	
	virtual bool operator==(const Type & t) const = 0;
	
//	std::ostream & operator<<(std::ostream & os) const;
	friend std::ostream & operator<<(std::ostream & os, const Type & type);
	
	static std::shared_ptr<Type> createCopy(const Type & t);
	static std::shared_ptr<Type> fromString(const char * str);
};