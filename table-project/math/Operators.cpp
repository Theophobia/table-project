#include <memory>
#include <cmath>

#include <table-project/math/Operators.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>

TypeData getTypeData(const std::shared_ptr<Type> & aPtr) {
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

std::shared_ptr<Type> operator+(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr) {
	if (!aPtr || !bPtr) {
		throw std::runtime_error("aPtr or bPtr is nullptr");
	}
	
	TypeData atd = getTypeData(aPtr);
	TypeData btd = getTypeData(bPtr);
	
	if (atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.doublePart + btd.doublePart);
	}
	
	if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
		return std::make_shared<DoubleType>(atd.doublePart + btd.integerPart);
	}
	
	if (!atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.integerPart + btd.doublePart);
	}
	
	if (!atd.hasDouble && !btd.hasDouble) {
		return std::make_shared<IntegerType>(atd.integerPart + btd.integerPart);
	}
	
	throw std::runtime_error("Unexpected error");
}

std::shared_ptr<Type> operator-(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr) {
	if (!aPtr || !bPtr) {
		throw std::runtime_error("aPtr or bPtr is nullptr");
	}
	
	TypeData atd = getTypeData(aPtr);
	TypeData btd = getTypeData(bPtr);
	
	if (atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.doublePart - btd.doublePart);
	}
	
	if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
		return std::make_shared<DoubleType>(atd.doublePart - btd.integerPart);
	}
	
	if (!atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.integerPart - btd.doublePart);
	}
	
	if (!atd.hasDouble && !btd.hasDouble) {
		return std::make_shared<IntegerType>(atd.integerPart - btd.integerPart);
	}
	
	throw std::runtime_error("Unexpected error");
}

std::shared_ptr<Type> operator*(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr) {
	if (!aPtr || !bPtr) {
		throw std::runtime_error("aPtr or bPtr is nullptr");
	}
	
	TypeData atd = getTypeData(aPtr);
	TypeData btd = getTypeData(bPtr);
	
	if (atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.doublePart * btd.doublePart);
	}
	
	if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
		return std::make_shared<DoubleType>(atd.doublePart * btd.integerPart);
	}
	
	if (!atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.integerPart * btd.doublePart);
	}
	
	if (!atd.hasDouble && !btd.hasDouble) {
		return std::make_shared<IntegerType>(atd.integerPart * btd.integerPart);
	}
	
	throw std::runtime_error("Unexpected error");
}

std::shared_ptr<Type> operator/(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr) {
	if (!aPtr || !bPtr) {
		throw std::runtime_error("aPtr or bPtr is nullptr");
	}
	
	TypeData atd = getTypeData(aPtr);
	TypeData btd = getTypeData(bPtr);
	
	if (atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.doublePart / btd.doublePart);
	}
	
	if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
		return std::make_shared<DoubleType>(atd.doublePart / btd.integerPart);
	}
	
	if (!atd.hasDouble && btd.hasDouble) {
		return std::make_shared<DoubleType>(atd.integerPart / btd.doublePart);
	}
	
	if (!atd.hasDouble && !btd.hasDouble) {
		if (atd.integerPart % btd.integerPart == 0) {
			return std::make_shared<IntegerType>(atd.integerPart / btd.integerPart);
		}
		return std::make_shared<DoubleType>(((long double) atd.integerPart) / btd.integerPart);
	}
	
	throw std::runtime_error("Unexpected error");
}

std::shared_ptr<Type> operator^(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr) {
	if (!aPtr || !bPtr) {
		throw std::runtime_error("aPtr or bPtr is nullptr");
	}
	
	TypeData atd = getTypeData(aPtr);
	TypeData btd = getTypeData(bPtr);
	
	if (atd.hasDouble && btd.hasDouble) {
		return std::make_shared<StringType>("#ERROR");
	}
	
	if (atd.hasDouble && !btd.hasDouble) { // Redundancy for readability
		if (atd.doublePart < 0) {
			return std::make_shared<StringType>("#ERROR");
		}
		return std::make_shared<DoubleType>(std::pow(atd.doublePart, btd.integerPart));
	}
	
	if (!atd.hasDouble && btd.hasDouble) {
		if (atd.integerPart < 0) {
			return std::make_shared<StringType>("#ERROR");
		}
		return std::make_shared<DoubleType>(std::pow(atd.integerPart, btd.doublePart));
	}
	
	if (!atd.hasDouble && !btd.hasDouble) {
		return std::make_shared<IntegerType>(std::pow(atd.integerPart, btd.integerPart));
	}
	
	throw std::runtime_error("Unexpected error");
}


std::shared_ptr<Type> operator+(const std::shared_ptr<Type> & aPtr, long long b) {
	return operator+(aPtr, std::make_shared<IntegerType>(b));
}

std::shared_ptr<Type> operator+(long long a, const std::shared_ptr<Type> & bPtr) {
	return operator+(bPtr, a);
}

std::shared_ptr<Type> operator+(const std::shared_ptr<Type> & aPtr, long double b) {
	return operator+(aPtr, std::make_shared<DoubleType>(b));
}

std::shared_ptr<Type> operator+(long double a, const std::shared_ptr<Type> & bPtr) {
	return operator+(bPtr, a);
}