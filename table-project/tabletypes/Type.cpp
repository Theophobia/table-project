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
	
	throw std::invalid_argument("Type is not registeded within Type::createCopy()");
}

std::shared_ptr<Type> Type::fromString(const char * str) {
	try {
		IntegerType it;
		it.tryParse(str);
		return createCopy(it);
	}
	catch (std::exception &) {}
	
	try {
		DoubleType dt;
		dt.tryParse(str);
		return createCopy(dt);
	}
	catch (std::exception &) {}
	
	try {
		FormulaType ft;
		ft.tryParse(str);
		return createCopy(ft);
	}
	catch (std::exception &) {}
	
	try {
		StringType st;
		st.tryParse(str);
		return createCopy(st);
	}
	catch (std::exception &) {}
	
	throw std::invalid_argument("String could not be parsed as anything, unexpected error");
}
