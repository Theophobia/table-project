#pragma once

#include <memory>

#include <table-project/tabletypes/Type.h>

struct TypeData {
	bool hasDouble = false;
	long double doublePart = 0;
	std::int64_t integerPart = 0;
};

TypeData getTypeData(const std::shared_ptr<Type> & aPtr);

std::shared_ptr<Type> operator+(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr);
std::shared_ptr<Type> operator-(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr);
std::shared_ptr<Type> operator*(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr);
std::shared_ptr<Type> operator/(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr);
std::shared_ptr<Type> operator^(const std::shared_ptr<Type> & aPtr, const std::shared_ptr<Type> & bPtr);

std::shared_ptr<Type> operator+(const std::shared_ptr<Type> & aPtr, long long b);
std::shared_ptr<Type> operator+(long long a, const std::shared_ptr<Type> & bPtr);
std::shared_ptr<Type> operator+(const std::shared_ptr<Type> & aPtr, long double b);
std::shared_ptr<Type> operator+(long double a, const std::shared_ptr<Type> & bPtr);