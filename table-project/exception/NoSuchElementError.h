#pragma once

#include <exception>
#include <string>

namespace TableProject {
	/**
	 * Error object used by Table for specifying that no such element exists in table.
	 */
	class NoSuchElementError final : public std::exception {
		std::string msg;

	public:
		NoSuchElementError() = default;

		explicit NoSuchElementError(const char * msg) {
			this->msg = msg;
		}

		explicit NoSuchElementError(const std::string & msg) {
			this->msg = msg;
		}

		~NoSuchElementError() = default;

		NoSuchElementError(const NoSuchElementError & other) {
			*this = other;
		}

		NoSuchElementError & operator=(const NoSuchElementError & other) {
			this->msg = other.msg;
			return *this;
		}

		NoSuchElementError(NoSuchElementError && other) noexcept {
			*this = std::move(other);
		}

		NoSuchElementError & operator=(NoSuchElementError && other) noexcept {
			this->msg = std::move(other.msg);
			return *this;
		}

		const char * what() const noexcept override {
			return msg.c_str();
		}
	};
}