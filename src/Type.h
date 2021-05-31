#ifndef TYPE_H_GADbBeWXLQTbXSMdTfnL
#define TYPE_H_GADbBeWXLQTbXSMdTfnL

#include <ostream>

class Type {

public:
	virtual long getClassId() const = 0;
	virtual void tryParse(const std::string & str) = 0;
	virtual std::string toString() const = 0;
	
//	std::ostream & operator<<(std::ostream & os) const;
	friend std::ostream & operator<<(std::ostream & os, const Type & type);
};

#endif