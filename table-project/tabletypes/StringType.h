#pragma once

#include "Type.h"

class StringType : public Type {

protected:
	std::string text;

public:
	StringType() = default;
	explicit StringType(const std::string & text);
	
	const std::string & getText() const;
	void setText(const std::string & text);
	
	void tryParse(const std::string & str) override;
	std::string toString() const override;
	std::string toCSV() const override;
	const std::string & getClass() const override;
	
	bool operator==(const Type & t) const override;
};