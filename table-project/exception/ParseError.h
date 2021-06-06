#pragma once

class Type;

template<class T>
class ParseError final : public std::exception {

private:
	/**
	 * Check if class passed is subclass of Type
	 *
	 * Read from:
	 * https://www.stroustrup.com/bs_faq2.html#constraints
	 *
	 * @param a Object of class T
	 */
	static void constraints(T a) {
		Type * c = &a;
	}
	
	void checkIfCompile() {
		void (* p)(T) = constraints;
	}

	std::string msg;

public:
	ParseError<T>() {
		checkIfCompile();
	}
	
	explicit ParseError<T>(const char * msg) {
		checkIfCompile();
		this->msg = msg;
	}
	
	explicit ParseError<T>(const std::string & msg) {
		checkIfCompile();
		this->msg = msg;
	}
	
	~ParseError() = default;
	
	ParseError<T>(const ParseError<T> & other) {
		*this = other;
	}
	
	ParseError<T> & operator=(const ParseError<T> & other) {
		this->msg = other.msg;
		return *this;
	}
	
	ParseError<T>(ParseError<T> && other) noexcept {
		*this = std::move(other);
	}
	
	ParseError<T> & operator=(ParseError<T> && other) noexcept {
		this->msg = std::move(other.msg);
		return *this;
	}
	
	const char * what() const noexcept override {
		return msg.c_str();
	}
};
