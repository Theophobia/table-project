#include <table-project/tabletypes/StringType.h>
#include <table-project/exception/ParseError.h>

namespace TableProject {
	StringType::StringType(const std::string & text) {
		this->text = text;
	}

	const std::string & StringType::getText() const {
		return text;
	}

	void StringType::setText(const std::string & text) {
		this->text = text;
	}

	void StringType::tryParse(const std::string & str) {
		if (str.size() < 2) {
			throw ParseError<StringType>("Minimum length not met");
		}

		if (str.front() != '"' || str.back() != '"') {
			throw ParseError<StringType>("String is not surrounded by quotes (\")");
		}

		const std::size_t start = 1;
		const std::size_t end = str.size() - 1;

		// Check for unescaped "
		for (std::size_t i = start; i < end; i++) {
			if (str[i] == '"' && str[i - 1] != '\\') {
				std::string msg = "Quotes (\") at string index "
								  + std::to_string(i)
								  + " are not escaped by back slash (\\)";
				throw ParseError<StringType>(msg);
			}
		}

		// str without the 2 quotes, hence size()-2
		text = str.substr(1, str.size() - 2);
	}

	std::string StringType::toString() const {
		return text;
	}

	std::string StringType::toCSV() const {
		return '"' + this->toString() + '"';
	}

	const std::string & StringType::getClass() const {
		static const std::string className = "StringType";
		return className;
	}

	bool StringType::isIntegerCastable() const {
		if (text.empty()) {
			return false;
		}

		try {
			IntegerType it;
			it.tryParse(text);
			return true;
		}
		catch (std::exception & e) {
			return false;
		}
	}

	bool StringType::isDoubleCastable() const {
		if (text.empty()) {
			return false;
		}

		try {
			DoubleType dt;
			dt.tryParse(text);
			return true;
		}
		catch (std::exception & e) {
			return false;
		}
	}

	StringType::operator IntegerType() const {
		if (!isIntegerCastable()) {
			throw std::runtime_error("String object is not castable to an integer");
		}
		try {
			IntegerType it;
			it.tryParse(text);
			return it;
		}
		catch (std::exception & e) {
			throw std::runtime_error("String object is not castable to an integer");
		}
	}

	StringType::operator DoubleType() const {
		if (!isDoubleCastable()) {
			throw std::runtime_error("String object is not castable to a double");
		}
		try {
			DoubleType dt;
			dt.tryParse(text);
			return dt;
		}
		catch (std::exception & e) {
			throw std::runtime_error("String object is not castable to a double");
		}
	}


	bool StringType::operator==(const Type & t) const {
		const StringType * casted = dynamic_cast<const StringType *>(&t);

		if (casted == nullptr) {
			return false;
		}

		if (casted == this) {
			return true;
		}

		return this->getText() == casted->getText();
	}

	StringType StringType::getError() {
		return StringType("#ERROR");
	}
}