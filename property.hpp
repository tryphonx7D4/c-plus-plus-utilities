#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <ostream>
#include <istream>
#include <type_traits>
#include <typeinfo>
#include "core_macros.hpp"
#include "basic_error.hpp"
#include "miscellaneous.hpp"

namespace dt0
{
	template <typename A, typename R = const A&, typename P = const A&, typename F = R(P)>
	struct get
	{
		using value_type = A;
		using return_type = R;
		using parameter_type = P;
		using function_type = F;

		function_type* getter{ nullptr };
	};

	template <typename A, typename R = const A&, typename P = const A&, typename F = R(P)>
	class get_accessor
	{
	public:
		using value_type = A;
		using return_type = R;
		using parameter_type = P;
		using function_type = F;

		___constexpr20___ get_accessor() noexcept : _core(nullptr) {}

		___constexpr20___ get_accessor(const get_accessor<value_type, return_type, parameter_type, function_type>&) = delete;
		
		___constexpr20___ get_accessor(get_accessor<value_type, return_type, parameter_type, function_type>&&) noexcept = delete;

		const get_accessor<value_type, return_type, parameter_type, function_type>& operator= (const get_accessor<value_type, return_type, parameter_type, function_type>&) = delete;

		const get_accessor<value_type, return_type, parameter_type, function_type>& operator= (get_accessor<value_type, return_type, parameter_type, function_type>&) noexcept = delete;

		___constexpr20___ get_accessor(std::nullptr_t) noexcept : _core(nullptr) {}

		~get_accessor() noexcept = default;

		const get_accessor<value_type, return_type, parameter_type, function_type>& operator= (const get<value_type, return_type, parameter_type>& other)
		{
			_core = other.getter;

			if (_core == nullptr)
			{
				_core = [](parameter_type _value) -> return_type { return _value; };
			}

			return *this;
		}

		const get_accessor<value_type, return_type, parameter_type, function_type>& operator= (get<value_type, return_type, parameter_type>&& other) noexcept(false)
		{
			_core = std::move(other.getter);

			if (_core == nullptr)
			{
				_core = [](parameter_type _value) -> return_type { return _value; };
			}

			return *this;
		}

		___nodiscard___ return_type operator() (parameter_type _value)
		{
			return _core(_value);
		}

	private:
		function_type* _core;
	};

	template <typename A>
	struct set
	{
		using value_type = A;

		void(*copy_setter)(value_type&, const value_type&) { nullptr };
		void(*move_setter)(value_type&, value_type&&) noexcept17 { nullptr };
	};

	template <typename A>
	class set_accessor
	{
	public:
		using value_type = A;

		___constexpr20___ set_accessor() noexcept : _copy_core(nullptr), _move_core(nullptr) {}

		___constexpr20___ set_accessor(std::nullptr_t) noexcept : _copy_core(nullptr), _move_core(nullptr) {}

		~set_accessor() noexcept = default;

		const set_accessor& operator= (const set<value_type>& other)
		{
			_copy_core = other.copy_setter;
			_move_core = other.move_setter;

			if ((_copy_core == nullptr) && (_move_core == nullptr))
			{
				_copy_core = [](value_type& _left, const value_type& _right) { _left = _right; };
				_move_core = [](value_type& _left, value_type&& _right) noexcept17{ _left = std::move(_right); };
			}

			return *this;
		}

		const set_accessor& operator= (set<value_type>&& other) noexcept
		{
			_copy_core = std::move(other.copy_setter);
			_move_core = std::move(other.move_setter);

			if ((_copy_core == nullptr) && (_move_core == nullptr))
			{
				_copy_core = [](value_type& _left, const value_type& _right) { _left = _right; };
				_move_core = [](value_type& _left, value_type&& _right) noexcept17{ _left = std::move(_right); };
			}

			return *this;
		}

		const set_accessor& operator() (value_type& left_value, const value_type& right_value) const
		{
			_copy_core(left_value, right_value);

			return *this;
		}

		const set_accessor& operator() (value_type& left_value, value_type&& right_value) const noexcept
		{
			_move_core(left_value, std::move(right_value));

			return *this;
		}

	private:
		void(*_copy_core)(value_type&, const value_type&);
		void(*_move_core)(value_type&, value_type&&) noexcept17;
	};

	template <typename A, typename R = const A&, typename P = const A&, typename G = R(P)>
	class property
	{
	public:
		using value_type = A;
		using return_type = R;
		using parameter_type = P;
		using getter_type = G;

		___constexpr20___ property(get<value_type, return_type, parameter_type>&& getter_init, set<value_type>&& setter_init) noexcept
		{
			_getter_core = std::move(getter_init);
			_setter_core = std::move(setter_init);
		}

		___constexpr20___ property(set<value_type>&& setter_init, get<value_type, return_type, parameter_type>&& getter_init) noexcept
		{
			_setter_core = std::move(setter_init);
			_getter_core = std::move(getter_init);
		}

		___constexpr20___ property(const value_type& other, get<value_type, return_type, parameter_type>&& getter_init, set<value_type>&& setter_init) noexcept
		{
			_core = other;

			_getter_core = std::move(getter_init);
			_setter_core = std::move(setter_init);
		}

		___constexpr20___ property(const value_type& other, set<value_type>&& setter_init, get<value_type, return_type, parameter_type>&& getter_init) noexcept
		{
			_core = other;

			_setter_core = std::move(setter_init);
			_getter_core = std::move(getter_init);
		}

		___constexpr20___ property(value_type&& other, get<value_type, return_type, parameter_type>&& getter_init, set<value_type>&& setter_init) noexcept
		{
			_core = std::move(other);

			_getter_core = std::move(getter_init);
			_setter_core = std::move(setter_init);
		}

		___constexpr20___ property(value_type&& other, set<value_type>&& setter_init, get<value_type, return_type, parameter_type>&& getter_init) noexcept
		{
			_core = std::move(other);

			_setter_core = std::move(setter_init);
			_getter_core = std::move(getter_init);
		}

		___constexpr20___ property(const property& other, get<value_type, return_type, parameter_type>&& getter_init, set<value_type>&& setter_init) noexcept
		{
			_core = other.value();

			_getter_core = std::move(getter_init);
			_setter_core = std::move(setter_init);
		}

		___constexpr20___ property(const property& other, set<value_type>&& setter_init, get<value_type, return_type, parameter_type>&& getter_init) noexcept
		{
			_core = other.value();

			_setter_core = std::move(setter_init);
			_getter_core = std::move(getter_init);
		}

		___constexpr20___ property(property&& other, get<value_type, return_type, parameter_type>&& getter_init, set<value_type>&& setter_init) noexcept
		{
			_core = const_move(other.value());

			_getter_core = std::move(getter_init);
			_setter_core = std::move(setter_init);
		}

		___constexpr20___ property(property&& other, set<value_type>&& setter_init, get<value_type, return_type, parameter_type>&& getter_init) noexcept
		{
			_core = const_move(other.value());

			_setter_core = std::move(setter_init);
			_getter_core = std::move(getter_init);
		}

		___constexpr20___ property(const value_type& other) noexcept
		{
			_core = other;

			_getter_core = std::move(get<value_type, return_type, parameter_type>{});
			_setter_core = std::move(set<value_type>{});
		}

		___constexpr20___ property(value_type&& other) noexcept
		{
			_core = std::move(other);

			_getter_core = std::move(get<value_type, return_type, parameter_type>{});
			_setter_core = std::move(set<value_type>{});
		}

		___constexpr20___ property(const property& other) noexcept
		{
			_core = other.value();

			_getter_core = std::move(get<value_type, return_type, parameter_type>{});
			_setter_core = std::move(set<value_type>{});
		}

		___constexpr20___ property(property&& other) noexcept
		{
			_core = const_move(other.value());

			_getter_core = std::move(get<value_type, return_type, parameter_type>{});
			_setter_core = std::move(set<value_type>{});
		}

		~property() noexcept = default;

		___nodiscard___ return_type value()
		{
			return _getter_core(_core);
		}

		const value_type& operator-> () const
		{
			return _core;
		}

		const property& operator= (const value_type& other)
		{
			_setter_core(_core, other);

			return *this;
		}

		const property& operator= (value_type&& other) noexcept
		{
			_setter_core(_core, std::move(other));

			return *this;
		}

		const property& operator= (const property& other)
		{
			_setter_core(_core, other.value());

			return *this;
		}

		const property& operator= (property&& other) noexcept
		{
			_setter_core(_core, const_move(other.value()));

			return *this;
		}

		___nodiscard___ bool operator== (const value_type& other) const
		{
			if (_core == other)
				return true;

			return false;
		}

		___nodiscard___ bool operator== (const property& other) const
		{
			if (_core == other.value())
				return true;

			return false;
		}

		___nodiscard___ bool operator!= (const value_type& other) const
		{
			if (_core != other)
				return true;

			return false;
		}

		___nodiscard___ bool operator!= (const property& other) const
		{
			if (_core != other.value())
				return true;

			return false;
		}

		___nodiscard___ bool operator> (const value_type& other) const
		{
			if (_core > other)
				return true;

			return false;
		}

		___nodiscard___ bool operator> (const property& other) const
		{
			if (_core > other.value())
				return true;

			return false;
		}

		___nodiscard___ bool operator< (const value_type& other) const
		{
			if (_core < other)
				return true;

			return false;
		}

		___nodiscard___ bool operator< (const property& other) const
		{
			if (_core < other.value())
				return true;

			return false;
		}

#ifdef _WIN64
	#if _MSVC_LANG > 201703L
		___nodiscard___ bool operator<=> (const value_type& other) const
		{
			if (_core <=> other)
				return true;

			return false;
		}

		___nodiscard___ bool operator<=> (const property& other) const
		{
			if (_core <=> other.value())
				return true;

			return false;
		}
	#endif
#else
	#if __cplusplus > 201703L
		___nodiscard___ bool operator<=> (const value_type& other) const
		{
			if (*_core <=> other)
				return true;

			return false;
		}

		___nodiscard___ bool operator<=> (const property& other) const
		{
			if (*_core <=> other.value())
				return true;

			return false;
		}
	#endif
#endif

		friend std::ostream& operator<< (std::ostream& output_stream, property& other)
		{
			output_stream << other._getter_core(other._core);

			return output_stream;
		}

		friend std::istream& operator>> (std::istream& input_stream, property& other)
		{
			input_stream >> other._core;

			return input_stream;
		}

	private:
		value_type _core;
		get_accessor<value_type, return_type, parameter_type, getter_type> _getter_core;
		set_accessor<value_type> _setter_core;
	};

	template <typename A, typename R = const A&>
	class const_property
	{
	public:
		using value_type = A;
		using return_type = R;
		using parameter_type = const A&;

		___constexpr20___ const_property(get<value_type, return_type, parameter_type>&& getter_init) noexcept
		{
			_core = value_type();
			_getter_core = std::move(getter_init);
		}

		~const_property() noexcept = default;

		___nodiscard___ return_type value()
		{
			return _getter_core(_core);
		}

		const value_type& operator-> () const
		{
			return _core;
		}

		const const_property& operator= (const value_type& other)
		{
			if (_initialized == false)
			{
				_core = other;
				_initialized = true;
			}

			else throw basic_error("Can not change const property!");

			return *this;
		}

		const const_property& operator= (value_type&& other) noexcept(false)
		{
			if (_initialized == false)
			{
				_core = std::move(other);
				_initialized = true;
			}

			else throw basic_error("Can not change const property!");

			return *this;
		}

		const const_property& operator= (const const_property& other)
		{
			if (_initialized == false)
			{
				_core = other.value();
				_initialized = true;
			}

			else throw basic_error("Can not change const property!");

			return *this;
		}

		___nodiscard___ bool operator== (const value_type& other) const
		{
			if (_core == other)
				return true;

			return false;
		}

		___nodiscard___ bool operator== (const const_property& other) const
		{
			if (_core == other.value())
				return true;

			return false;
		}

		___nodiscard___ bool operator!= (const value_type& other) const
		{
			if (_core != other)
				return true;

			return false;
		}

		___nodiscard___ bool operator!= (const const_property& other) const
		{
			if (_core != other.value())
				return true;

			return false;
		}

		___nodiscard___ bool operator> (const value_type& other) const
		{
			if (_core > other)
				return true;

			return false;
		}

		___nodiscard___ bool operator> (const const_property& other) const
		{
			if (_core > other.value())
				return true;

			return false;
		}

		___nodiscard___ bool operator< (const value_type& other) const
		{
			if (_core < other)
				return true;

			return false;
		}

		___nodiscard___ bool operator< (const const_property& other) const
		{
			if (_core < other.value())
				return true;

			return false;
		}

#ifdef _WIN64
	#if _MSVC_LANG > 201703L
		___nodiscard___ bool operator<=> (const value_type& other) const
		{
			if (_core <=> other)
				return true;

			return false;
		}

		___nodiscard___ bool operator<=> (const const_property& other) const
		{
			if (_core <=> other.value())
				return true;

			return false;
		}

	#endif
#else
	#if __cplusplus > 201703L
		___nodiscard___ bool operator<=> (const value_type& other) const
		{
			if (*_core <=> other)
				return true;

			return false;
		}

		___nodiscard___ bool operator<=> (const const_property& other) const
		{
			if (_core <=> other.value())
				return true;

			return false;
		}
	#endif
#endif

		friend std::ostream& operator<< (std::ostream& output_stream, const_property& other)
		{
			output_stream << other._getter_core(other._core);

			return output_stream;
		}

	private:
		value_type _core;
		get_accessor<value_type, return_type, parameter_type> _getter_core;
		bool _initialized = false;
	};
}

#endif /* PROPERTY_HPP */
