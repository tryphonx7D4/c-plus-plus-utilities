#ifndef CORE_MACROS_HPP
#define CORE_MACROS_HPP

#ifndef ___constexpr20___
	#ifdef _WIN64
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
	#ifdef _WIN64
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

#endif /* CORE_MACROS_HPP */
