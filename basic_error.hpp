#ifndef BASIC_ERROR_HPP
#define BASIC_ERROR_HPP

#include <stdexcept>
#include <string>

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
