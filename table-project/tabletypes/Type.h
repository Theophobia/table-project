#pragma once

#include <ostream>
#include <memory>

namespace TableProject {
	class Type {

	public:
		virtual ~Type() = default;
		virtual void tryParse(const std::string & str) = 0;
		virtual std::string toString() const = 0;
		virtual std::string toCSV() const = 0;
		virtual const std::string & getClass() const = 0;

		virtual bool operator==(const Type & t) const = 0;

		friend std::ostream & operator<<(std::ostream & os, const Type & type);

		static std::shared_ptr<Type> createCopy(const Type & t);

		/**
		 * TODO
		 * @param s
		 * @return
		 *
		 * @throws std::invalid_argument If string could not be parsed
		 */
		static std::shared_ptr<Type> fromString(const std::string & s);
	};
}