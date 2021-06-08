#include <table-project/tabletypes/IntegerType.h>

#include <memory>
#include <table-project/TableProject.h>

namespace TableProject {
	IntegerType::IntegerType(std::int64_t number) {
		this->number = number;
	}

	IntegerType::operator std::shared_ptr<IntegerType>() const {
		return std::make_shared<IntegerType>(*this);
	}

	std::int64_t IntegerType::getNumber() const {
		return number;
	}

	void IntegerType::setNumber(std::int64_t number) {
		this->number = number;
	}

	void IntegerType::tryParse(const std::string & str) {
		try {
			std::int64_t i = TableProject::StringUtil::toInt64(str, true);

			// If we passed, then we have a regular integer
			// Assign it and return, as we have other code below
			this->number = i;
			return;
		}
		catch (std::exception & e) {}

		// Check for zero-fractional double, as that is an integer
		if (TableProject::StringUtil::isZeroFractionalDouble(str)) {
			// Safe to cast to int
			std::int64_t i = std::stoll(str);
			this->number = i;
			return;
		}

		throw ParseError<IntegerType>("Could not parse string as integer");
	}

	std::string IntegerType::toString() const {
		return std::to_string(number);
	}

	std::string IntegerType::toCSV() const {
		return this->toString();
	}

	const std::string & IntegerType::getClass() const {
		static const std::string className = "IntegerType";
		return className;
	}

	bool IntegerType::operator==(const Type & t) const {
		const IntegerType * casted = dynamic_cast<const IntegerType *>(&t);

		if (casted == nullptr) {
			return false;
		}

		if (casted == this) {
			return true;
		}

		return this->getNumber() == casted->getNumber();
	}
}