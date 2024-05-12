#ifndef BASIC_ERROR_HPP
#define BASIC_ERROR_HPP

#include <stdexcept>
#include <string>

/* It's just an error class that inherits from std::exception, it supports strings as input
(idk how it is on other compilers but on MSVC it takes in only const char pointer basically) */ 

namespace dt0
{
	class basic_error : public std::exception
	{
	public:
		using base = std::exception;

		basic_error() noexcept : base() {}

		explicit basic_error(char const* const message) noexcept : base(message) {}

		basic_error(const std::string& message) noexcept : base(message.c_str()) {}

		basic_error(std::string&& message) noexcept : base(message.c_str()) {}

		~basic_error() noexcept = default;
	};
}

#endif /* BASIC_ERROR_HPP */
