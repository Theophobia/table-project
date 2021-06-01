#ifndef TABLE_STRINGTYPE_H
#define TABLE_STRINGTYPE_H

#include "base/Type.h"

class StringType : public Type {
private:

protected:
	std::string text;

public:
	StringType() = default;
	explicit StringType(const std::string & text);
	
	const std::string & getText() const;
	void setText(const std::string & text);
	
//	int getClassId() const override;
	void tryParse(const std::string & str) override;
	std::string toString() const override;
};

#endif