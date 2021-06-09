#include <memory>
#include <cmath>
#include <table-project/math/Operators.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>
#include <table-project/TableProject.h>

namespace TableProject {
	TypeData getTypeData(const std::unique_ptr<Type> & aPtr) {
		TypeData td;

		Type * a = aPtr.get();

		auto * integerType = dynamic_cast<IntegerType *>(a);
		auto * doubleType = dynamic_cast<DoubleType *>(a);
		auto * stringType = dynamic_cast<StringType *>(a);
		auto * formulaType = dynamic_cast<FormulaType *>(a);

		// Check "a" for integer or double contents
		if (integerType) {
			td.integerPart = integerType->getNumber();
		}

		if (doubleType) {
			td.hasDouble = true;
			td.doublePart = doubleType->getNumber();
		}
		else if (stringType) {
			try {
				IntegerType it;
				it.tryParse(stringType->toString());

				td.integerPart = it.getNumber();
			}
			catch (std::exception &) {}

			try {
				DoubleType dt;
				dt.tryParse(stringType->toString());

				td.doublePart = dt.getNumber();
				td.hasDouble = true;
			}
			catch (std::exception &) {}
		}
		else if (formulaType) {
			throw std::runtime_error("Formula type arithmetic not supported");
		}

		return td;
	}

	std::unique_ptr<Type> operator+(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr) {
		if (!aPtr || !bPtr) {
			throw std::runtime_error("aPtr or bPtr is nullptr");
		}

		TypeData atd = getTypeData(aPtr);
		TypeData btd = getTypeData(bPtr);

		if (atd.hasDouble && btd.hasDouble) {
			return std::make_unique<DoubleType>(atd.doublePart + btd.doublePart);
		}

		if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
			return std::make_unique<DoubleType>(atd.doublePart + btd.integerPart);
		}

		if (!atd.hasDouble && btd.hasDouble) {
			return std::make_unique<DoubleType>(atd.integerPart + btd.doublePart);
		}

		if (!atd.hasDouble && !btd.hasDouble) {
			return std::make_unique<IntegerType>(atd.integerPart + btd.integerPart);
		}

		throw std::runtime_error("Unexpected error");
	}

	std::unique_ptr<Type> operator-(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr) {
		if (!aPtr || !bPtr) {
			throw std::runtime_error("aPtr or bPtr is nullptr");
		}

		TypeData atd = getTypeData(aPtr);
		TypeData btd = getTypeData(bPtr);

		if (atd.hasDouble && btd.hasDouble) {
			return std::make_unique<DoubleType>(atd.doublePart - btd.doublePart);
		}

		if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
			return std::make_unique<DoubleType>(atd.doublePart - btd.integerPart);
		}

		if (!atd.hasDouble && btd.hasDouble) {
			return std::make_unique<DoubleType>(atd.integerPart - btd.doublePart);
		}

		if (!atd.hasDouble && !btd.hasDouble) {
			return std::make_unique<IntegerType>(atd.integerPart - btd.integerPart);
		}

		throw std::runtime_error("Unexpected error");
	}

	std::unique_ptr<Type> operator*(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr) {
		if (!aPtr || !bPtr) {
			throw std::runtime_error("aPtr or bPtr is nullptr");
		}

		TypeData atd = getTypeData(aPtr);
		TypeData btd = getTypeData(bPtr);

		if (atd.hasDouble && btd.hasDouble) {
			return std::make_unique<DoubleType>(atd.doublePart * btd.doublePart);
		}

		if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
			return std::make_unique<DoubleType>(atd.doublePart * btd.integerPart);
		}

		if (!atd.hasDouble && btd.hasDouble) {
			return std::make_unique<DoubleType>(atd.integerPart * btd.doublePart);
		}

		if (!atd.hasDouble && !btd.hasDouble) {
			return std::make_unique<IntegerType>(atd.integerPart * btd.integerPart);
		}

		throw std::runtime_error("Unexpected error");
	}

	std::unique_ptr<Type> operator/(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr) {
		if (!aPtr || !bPtr) {
			throw std::runtime_error("aPtr or bPtr is nullptr");
		}

		TypeData atd = getTypeData(aPtr);
		TypeData btd = getTypeData(bPtr);

		if (atd.hasDouble && btd.hasDouble) {
			long double num = atd.doublePart / btd.doublePart;
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		if (atd.hasDouble && !btd.hasDouble) {
			long double num = atd.doublePart / btd.integerPart;
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		if (!atd.hasDouble && btd.hasDouble) {
			long double num = ((long double) atd.integerPart) / btd.doublePart;
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}

			// Result may be actually an integer
			if (TableProject::DoubleUtil::isWhole(num, 0.00001)) {
				std::int64_t actuallyInt64 = (std::int64_t) num;

				auto res = Type::fromString(std::to_string(actuallyInt64));

				return res;
			}

			auto res = Type::fromString(std::to_string(num));

			return res;
		}

		if (!atd.hasDouble && !btd.hasDouble) {
			if (atd.integerPart % btd.integerPart == 0) {
				return Type::fromString(std::to_string(atd.integerPart / btd.integerPart));
			}

			long double num = ((long double) atd.integerPart) / btd.integerPart;
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		throw std::runtime_error("Unexpected error");
	}

	std::unique_ptr<Type> operator^(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr) {
		if (!aPtr || !bPtr) {
			throw std::runtime_error("aPtr or bPtr is nullptr");
		}

		TypeData atd = getTypeData(aPtr);
		TypeData btd = getTypeData(bPtr);

		if (atd.hasDouble && btd.hasDouble) {
			long double num = std::pow(atd.doublePart, btd.doublePart);
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
			long double num = std::pow(atd.doublePart, btd.integerPart);
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		if (!atd.hasDouble && btd.hasDouble) {
			long double num = std::pow(atd.integerPart, btd.doublePart);
			if (std::isnan(num) || std::isinf(num)) {
				return std::make_unique<StringType>(StringType::getError());
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		if (!atd.hasDouble && !btd.hasDouble) {
			long double num = std::pow(atd.integerPart, btd.integerPart);

			if (TableProject::DoubleUtil::isWhole(num, 0.0001)) {
				auto res = Type::fromString(std::to_string((std::int64_t) num));
				return res;
			}
			auto res = Type::fromString(std::to_string(num));
			return res;
		}

		throw std::runtime_error("Unexpected error");
	}


//	std::unique_ptr<Type> operator+(const std::unique_ptr<Type> & aPtr, long long b) {
//		return operator+(aPtr, std::make_unique<IntegerType>(b));
//	}
//
//	std::unique_ptr<Type> operator+(long long a, const std::unique_ptr<Type> & bPtr) {
//		return operator+(bPtr, a);
//	}
//
//	std::unique_ptr<Type> operator+(const std::unique_ptr<Type> & aPtr, long double b) {
//		return operator+(aPtr, std::make_unique<DoubleType>(b));
//	}
//
//	std::unique_ptr<Type> operator+(long double a, const std::unique_ptr<Type> & bPtr) {
//		return operator+(bPtr, a);
//	}
}