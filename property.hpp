#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <new>
#include <iostream>
#include "core_macros.hpp"
#include "basic_error.hpp"

namespace dt0
{
	template <typename, typename>
	class property;

	struct complete {};

	struct readonly {};

	template <typename P, typename I = complete>
	class property
	{
	public:
		using value_type = P;

		___constexpr20___ property() noexcept(false)
		{
			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
				::new(_core) value_type();
		}

		___constexpr20___ property(std::nullptr_t) noexcept : _core(nullptr) {}

		___constexpr20___ property(const value_type& other) 
		{
			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_copy_constructible<value_type>::value)
					::new(_core) value_type(other);

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor copy constructible!"));
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
					*_core = other;

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not copy assignable!"));
				}
			}
		}

		___constexpr20___ property(value_type&& other) noexcept(false)
		{
			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_move_constructible<value_type>::value)
					::new(_core) value_type(std::move(other));

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor move constructible!"));
				}
			}

			else
			{
				if (std::is_move_assignable<value_type>::value)
					*_core = std::move(other);

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not move assignable!"));
				}
			}
		}

		___constexpr20___ property(const property<value_type>& other)
		{
			if (this == __builtin_addressof(other))
			{
				throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
					std::string(">: Self-assignment not allowed!"));
			}

			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_copy_constructible<value_type>::value)
					::new(_core) value_type(other.get());

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor copy constructible!"));
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
					*_core = other.get();

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not copy assignable!"));
				}
			}
		}

		___constexpr20___ property(property<value_type>&& other) noexcept(false)
		{
			if (this == __builtin_addressof(other))
			{
				throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) + 
					std::string(">: Self-assignment not allowed!"));
			}

			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_move_constructible<value_type>::value)
					::new(_core) value_type(std::move(other.get()));

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor move constructible!"));
				}
			}

			else
			{
				if (std::is_move_assignable<value_type>::value)
					*_core = std::move(other.get());

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not move assignable!"));
				}
			}
		}

		~property() noexcept(false)
		{
			if (std::is_destructible<value_type>::value)
				_core->~value_type();

			try
			{
				::operator delete(_core, sizeof(value_type));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}
		}

		___nodiscard___ const value_type& get() const
		{
			return *_core;
		}

		const property<value_type> operator= (const value_type& other)
		{	
			if (_core == nullptr)
			{
				try
				{
					_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
				}

				catch (std::bad_alloc _error)
				{
					throw;
				}

				if (std::is_constructible<value_type>::value)
				{
					if(std::is_copy_constructible<value_type>::value)
						::new(_core) value_type(other);

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is neither\nconstructible nor copy constructible!"));
					}
				}

				else
				{
					if(std::is_copy_assignable<value_type>::value)
						*_core = other;

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is not copy assignable!"));
					}
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
				{
					*_core = other;
				}

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not copy assignable!"));
				}
			}

			return *this;
		}

		const property<value_type> operator= (value_type&& other) noexcept(false)
		{
			if (_core == nullptr)
			{
				try
				{
					_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
				}

				catch (std::bad_alloc _error)
				{
					throw;
				}

				if (std::is_constructible<value_type>::value)
				{
					if (std::is_move_constructible<value_type>::value)
						::new(_core) value_type(std::move(other));

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is neither\nconstructible nor move constructible!"));
					}
				}

				else
				{
					if (std::is_move_assignable<value_type>::value)
						*_core = std::move(other);

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is not move assignable!"));
					}
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
				{
					*_core = std::move(other);
				}

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not move assignable!"));
				}
			}

			return *this;
		}

		const property<value_type>& operator= (const property<value_type>& other)
		{
			if (this == __builtin_addressof(other))
			{
				throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
					std::string(">: Self-assignment not allowed!"));
			}

			if (_core == nullptr)
			{
				try
				{
					_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
				}

				catch (std::bad_alloc _error)
				{
					throw;
				}

				if (std::is_constructible<value_type>::value)
				{
					if (std::is_copy_constructible<value_type>::value)
						::new(_core) value_type(other.get());

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is neither\nconstructible nor copy constructible!"));
					}
				}

				else
				{
					if (std::is_copy_assignable<value_type>::value)
						*_core = other.get();

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is not copy assignable!"));
					}
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
					*_core = other.get();

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not copy assignable!"));
				}
			}

			return *this;
		}

		const property<value_type>& operator= (property<value_type>&& other) noexcept(false)
		{
			if (this == __builtin_addressof(other))
			{
				throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
					std::string(">: Self-assignment not allowed!"));
			}

			if (_core == nullptr)
			{
				try
				{
					_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
				}

				catch (std::bad_alloc _error)
				{
					throw;
				}

				if (std::is_constructible<value_type>::value)
				{
					if (std::is_move_constructible<value_type>::value)
						::new(_core) value_type(std::move(other.get()));

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is neither\nconstructible nor move constructible!"));
					}
				}

				else
				{
					if (std::is_move_assignable<value_type>::value)
						*_core = std::move(other.get());

					else
					{
						throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
							std::string(">: Can not assign value because type is not move assignable!"));
					}
				}
			}

			else
			{
				if (std::is_move_assignable<value_type>::value)
					*_core = std::move(other.get());

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not move assignable!"));
				}
			}

			return *this;
		}

		value_type const* const operator-> () const
		{
			return _core;
		}

		friend std::ostream& operator<< (std::ostream& out, const property<value_type>& prop)
		{
			out << *prop._core;

			return out;
		}

		friend std::istream& operator>> (std::istream& in, property<value_type>& prop)
		{
			in >> *prop._core;

			return in;
		}

	private:
		value_type* _core;
	};

	template <typename P>
	class property<P, readonly>
	{
	public:
		using value_type = P;

		___constexpr20___ property() noexcept(false)
		{
			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
				::new(_core) value_type();
		}

		___constexpr20___ property(std::nullptr_t) noexcept : _core(nullptr) {}

		___constexpr20___ property(const value_type& other)
		{
			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_copy_constructible<value_type>::value)
					::new(_core) value_type(other);

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor copy constructible!"));
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
					*_core = other;

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not copy assignable!"));
				}
			}
		}

		___constexpr20___ property(value_type&& other) noexcept(false)
		{
			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_move_constructible<value_type>::value)
					::new(_core) value_type(std::move(other));

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor move constructible!"));
				}
			}

			else
			{
				if (std::is_move_assignable<value_type>::value)
					*_core = std::move(other);

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not move assignable!"));
				}
			}
		}

		___constexpr20___ property(const property<value_type>& other)
		{
			if (this == __builtin_addressof(other))
			{
				throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
					std::string(">: Self-assignment not allowed!"));
			}

			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_copy_constructible<value_type>::value)
					::new(_core) value_type(other.get());

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor copy constructible!"));
				}
			}

			else
			{
				if (std::is_copy_assignable<value_type>::value)
					*_core = other.get();

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not copy assignable!"));
				}
			}
		}

		___constexpr20___ property(property<value_type>&& other) noexcept(false)
		{
			if (this == __builtin_addressof(other))
			{
				throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
					std::string(">: Self-assignment not allowed!"));
			}

			try
			{
				_core = reinterpret_cast<value_type*>(::operator new(sizeof(value_type)));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}

			if (std::is_constructible<value_type>::value)
			{
				if (std::is_move_constructible<value_type>::value)
					::new(_core) value_type(std::move(other));

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is neither\nconstructible nor move constructible!"));
				}
			}

			else
			{
				if (std::is_move_assignable<value_type>::value)
					*_core = std::move(other);

				else
				{
					throw basic_error(std::string("property<") + std::string(typeid(value_type).name()) +
						std::string(">: Can not assign value because type is not move assignable!"));
				}
			}
		}

		~property() noexcept(false)
		{
			if (std::is_destructible<value_type>::value)
				_core->~value_type();

			try
			{
				::operator delete(_core, sizeof(value_type));
			}

			catch (std::bad_alloc _error)
			{
				throw;
			}
		}

		___nodiscard___ const value_type& get() const
		{
			return *_core;
		}

		value_type const* const operator-> () const
		{
			return _core;
		}

		friend std::ostream& operator<< (std::ostream& out, const property<value_type>& prop)
		{
			out << *prop._core;

			return out;
		}

	private:
		value_type* _core;
	};
}

#endif /* PROPERTY_HPP */
