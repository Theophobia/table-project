#include "Type.h"

//std::ostream & Type::operator<<(std::ostream & os) const {
//	return os << toString();
//}

std::ostream & operator<<(std::ostream & os, const Type & type) {
	return os << type.toString();
}
