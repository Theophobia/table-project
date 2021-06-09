#pragma once

#include <memory>
#include <table-project/tabletypes/Type.h>

namespace TableProject {
	/**
	 * Used for operators between Type
	 */
	struct TypeData {
		bool hasDouble = false;
		long double doublePart = 0;
		std::int64_t integerPart = 0;
	};

	TypeData getTypeData(const std::unique_ptr<Type> & aPtr);

	std::unique_ptr<Type> operator+(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr);
	std::unique_ptr<Type> operator-(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr);
	std::unique_ptr<Type> operator*(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr);
	std::unique_ptr<Type> operator/(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr);
	std::unique_ptr<Type> operator^(const std::unique_ptr<Type> & aPtr, const std::unique_ptr<Type> & bPtr);

//	std::unique_ptr<Type> operator+(const std::unique_ptr<Type> & aPtr, long long b);
//	std::unique_ptr<Type> operator+(long long a, const std::unique_ptr<Type> & bPtr);
//	std::unique_ptr<Type> operator+(const std::unique_ptr<Type> & aPtr, long double b);
//	std::unique_ptr<Type> operator+(long double a, const std::unique_ptr<Type> & bPtr);
}