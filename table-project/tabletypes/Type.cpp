#include <table-project/tabletypes/Type.h>
#include <table-project/tabletypes/IntegerType.h>
#include <table-project/tabletypes/DoubleType.h>
#include <table-project/tabletypes/StringType.h>
#include <table-project/tabletypes/FormulaType.h>

Type::~Type() {

}

std::ostream & operator<<(std::ostream & os, const Type & type) {
	return os << type.toString();
}

Type * Type::createCopy(const Type & t) {
	if (auto it = dynamic_cast<const IntegerType *>(&t)) {
		return new IntegerType(*it);
	}
	if (auto it = dynamic_cast<const DoubleType *>(&t)) {
		return new DoubleType(*it);
	}
	if (auto it = dynamic_cast<const StringType *>(&t)) {
		return new StringType(*it);
	}
	if (auto it = dynamic_cast<const FormulaType *>(&t)) {
		return new FormulaType(*it);
	}
	throw std::invalid_argument("Type is not registeded within Type::createCopy()");
}
