#ifndef MISCELLANEOUS_HPP
#define MISCELLANEOUS_HPP

#include <type_traits>
#include "core_macros.hpp"

namespace dt0
{
	template <typename M>
	___nodiscard___ ___constexpr___ M&& const_move(const M& val) noexcept
	{
		return static_cast<M&&>(const_cast<M&>(val));
	}
}

#endif /* MISCELLANEOUS_HPP */
