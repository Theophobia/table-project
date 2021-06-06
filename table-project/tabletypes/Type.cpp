#include <table-project/TableProject.h>

namespace TableProject {
	std::ostream & operator<<(std::ostream & os, const Type & type) {
		return os << type.toString();
	}

	std::shared_ptr<Type> Type::createCopy(const Type & t) {
		if (auto it = dynamic_cast<const IntegerType *>(&t)) {
			return std::make_shared<IntegerType>(*it);
		}

		if (auto dt = dynamic_cast<const DoubleType *>(&t)) {
			return std::make_shared<DoubleType>(*dt);
		}

		if (auto ft = dynamic_cast<const FormulaType *>(&t)) {
			return std::make_shared<FormulaType>(*ft);
		}

		if (auto st = dynamic_cast<const StringType *>(&t)) {
			return std::make_shared<StringType>(*st);
		}

		throw std::invalid_argument("Type is not registered within Type::createCopy()");
	}

	std::shared_ptr<Type> Type::fromString(const std::string & s) {
		try {
			long double convertDouble = std::stold(s);
			if (TableProject::DoubleUtil::isWhole(convertDouble, 0.000001)) {
				long long convertInteger = (long long) std::roundl(convertDouble);
				return createCopy(IntegerType(convertInteger));
			}
			return createCopy(DoubleType(convertDouble));
		}
		catch (std::exception &) {}

		try {
			long long convertInteger = std::stoll(s);
			return createCopy(IntegerType(convertInteger));
		}
		catch (std::exception &) {}


		try {
			// Unreachable?
			IntegerType it;
			it.tryParse(s);
			return createCopy(it);
		}
		catch (std::exception &) {}

		try {
			// Unreachable?
			DoubleType dt;
			dt.tryParse(s);
			return createCopy(dt);
		}
		catch (std::exception &) {}

		try {
			FormulaType ft;
			ft.tryParse(s);
			return createCopy(ft);
		}
		catch (std::exception &) {}

		try {
			StringType st;
			st.tryParse(s);
			return createCopy(st);
		}
		catch (std::exception &) {}

		throw std::invalid_argument("String could not be parsed as anything");
	}
}