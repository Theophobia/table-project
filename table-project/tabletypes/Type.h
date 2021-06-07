#pragma once

#include <ostream>
#include <memory>

namespace TableProject {
	/**
	 * Superclass of all Table classes (IntegerType, DoubleType, StringType, FormulaType).
	 * Specifies an interface for them to follow.
	 */
	class Type {

	public:
		virtual ~Type() = default;

		/**
		 * Attempts to parse following string into a Type.
		 * If it does not succeed, an exception is thrown.
		 * Else it leaves this object in a state with
		 * correct values from the parsed string.
		 *
		 * @param s String to be parsed.
		 * @throws ParseError<TypeSubclass> If a parsing error occurred.
		 */
		virtual void tryParse(const std::string & s) = 0;

		/**
		 * Converts object to string, using the internal data.
		 * This method should be used by Type::operator<<(std::ostream &, const Type &)
		 *
		 * @return
		 */
		virtual std::string toString() const = 0;

		/**
		 * Convert object to a string, which later can
		 * easily be read to recover same object.
		 *
		 *
		 * @return
		 */
		virtual std::string toCSV() const = 0;

		/**
		 * Get class name of this object.
		 *
		 * @return Unique string, no other subclasses should return the same.
		 */
		virtual const std::string & getClass() const = 0;

		/**
		 * Check for equality between this object and another.
		 *
		 * @param t Other object
		 * @return true if objects are of same type and same content, false otherwise
		 */
		virtual bool operator==(const Type & t) const = 0;

		/**
		 * Print given object using Type.toString()
		 *
		 * @param os Output stream to print to.
		 * @param type Object of some Type subclass.
		 * @return The same output stream, but with the object added to it.
		 */
		friend std::ostream & operator<<(std::ostream & os, const Type & type);

		/**
		 * Return an exact copy of passed object.
		 *
		 * @param t Object of some Type subclass.
		 * @return Dynamically-allocated object of same type as given.
		 *
		 * @throws std::invalid_argument If "t" is not of known subclass of Type.
		 */
		static std::shared_ptr<Type> createCopy(const Type & t);

		/**
		 * Attempts to parse given string as all known subtypes of this class.
		 * If function is unable to do so, an exception is thrown.
		 *
		 * @param s String to be parsed.
		 * @return Dynamically-allocated object of some Type subclass, wrapped with a shared_ptr.
		 *
		 * @throws std::invalid_argument If string could not be parsed.
		 */
		static std::shared_ptr<Type> fromString(const std::string & s);
	};
}