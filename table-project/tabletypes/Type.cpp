#include <table-project/TableProject.h>

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
	
	throw std::invalid_argument("Type is not registered within Type::createCopy()");
}

std::shared_ptr<Type> Type::fromString(const std::string & s) {
	try {
		IntegerType it;
		it.tryParse(s);
		return createCopy(it);
	}
	catch (std::exception &) {}
	
	try {
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
