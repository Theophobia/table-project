#include <sstream>

#include <table-project/tabletypes/DoubleType.h>
#include <table-project/exception/ParseError.h>
#include <table-project/TableProject.h>

namespace TableProject {
	DoubleType::DoubleType(long double number) {
		this->number = number;
	}

	DoubleType::operator std::unique_ptr<DoubleType>() const {
		return std::make_unique<DoubleType>(*this);
	}

	long double DoubleType::getNumber() const {
		return number;
	}

	void DoubleType::setNumber(long double number) {
		this->number = number;
	}

	void DoubleType::tryParse(const std::string & str) {
		try {
			long double ld = TableProject::StringUtil::toLongDouble(str, true);
			this->number = ld;
		}
		catch (std::exception & e) {
			throw ParseError<DoubleType>("Could not parse string as double");
		}
	}

	std::string DoubleType::toString() const {

		// Source: https://stackoverflow.com/questions/15165502/double-to-string-without-scientific-notation-or-trailing-zeros-efficiently
		size_t len = std::snprintf(nullptr, 0, "%.10Lf", number);
		std::string s(len + 1, 0);

		std::snprintf(&s[0], len + 1, "%.10Lf", number);

		// remove null terminator
		s.pop_back();

		// remove trailing zeros
		s.erase(s.find_last_not_of('0') + 1, std::string::npos);

		// remove trailing point
		if (s.back() == '.') {
			s.pop_back();
		}

		return s;
	}

	std::string DoubleType::toCSV() const {
		return this->toString();
	}

	const std::string & DoubleType::getClass() const {
		static const std::string className = "DoubleType";
		return className;
	}

	bool DoubleType::operator==(const Type & t) const {
		const DoubleType * casted = dynamic_cast<const DoubleType *>(&t);

		if (casted == nullptr) {
			return false;
		}

		if (casted == this) {
			return true;
		}

		// Compare string representations,
		// because two visibly equal doubles can be !=
		return std::to_string(this->getNumber()) == std::to_string(casted->getNumber());
	}
}