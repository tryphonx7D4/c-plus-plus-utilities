#ifndef CORE_MACROS_HPP
#define CORE_MACROS_HPP

#ifndef ___constexpr___
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > 199711L
			#define ___constexpr___ constexpr
		#else
			#define ___constexpr___
		#endif
	#else
		#if __cplusplus > 199711L
			#define ___constexpr___ constexpr
		#else
			#define ___constexpr___
		#endif
	#endif
#endif

#ifndef ___constexpr14___
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > 201103L
			#define ___constexpr14___ constexpr
		#else
			#define ___constexpr14___
		#endif
	#else
		#if __cplusplus > 201103L
			#define ___constexpr14___ constexpr
		#else
			#define ___constexpr14___
		#endif
	#endif
#endif

#ifndef ___constexpr17___
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > 201402L
			#define ___constexpr17___ constexpr
		#else
			#define ___constexpr17___
		#endif
	#else
		#if __cplusplus > 201402L
			#define ___constexpr17___ constexpr
		#else
			#define ___constexpr17___
		#endif
	#endif
#endif

#ifndef ___constexpr20___
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > 201703L
			#define ___constexpr20___ constexpr
		#else
			#define ___constexpr20___
		#endif
	#else
		#if __cplusplus > 201703L
			#define ___constexpr20___ constexpr
		#else
			#define ___constexpr20___
		#endif
	#endif
#endif

#ifndef ___nodiscard___
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > 201402L
			#define ___nodiscard___ [[nodiscard]]
		#else
			#define ___nodiscard___
		#endif
	#else
		#if __cplusplus > 201402L
			#define ___nodiscard___ [[nodiscard]]
		#else
			#define ___nodiscard___
		#endif
	#endif
#endif

#ifndef noexcept17
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > 201402L
			#define noexcept17 noexcept
		#else
			#define noexcept17
		#endif
	#else
		#if __cplusplus > 201402L
			#define noexcept17 noexcept
		#else
			#define noexcept17
		#endif
	#endif
#endif

#endif /* CORE_MACROS_HPP */
