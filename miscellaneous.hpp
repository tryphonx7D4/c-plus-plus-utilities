#ifndef MISCELLANEOUS_HPP
#define MISCELLANEOUS_HPP

#include <type_traits>
#include "core_macros.hpp"

namespace dt0
{
	template <typename drain_type>
	___nodiscard___ ___constexpr___ drain_type&& move(const drain_type& _val)
	{
		return static_cast<drain_type&&>(const_cast<drain_type&>(_val));
	}
}

#endif /* MISCELLANEOUS_HPP */
