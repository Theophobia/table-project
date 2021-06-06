#pragma once

#include <table-project/tabletypes/Type.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/StringType.h>

namespace TableProject {
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
		std::string toCSV() const override;
		const std::string & getClass() const override;

		bool operator==(const Type & t) const override;

	};
}