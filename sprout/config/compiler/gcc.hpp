#ifndef SPROUT_CONFIG_COMPILER_GCC_HPP
#define SPROUT_CONFIG_COMPILER_GCC_HPP

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_CONSTEXPR
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_DEFAULTED_FUNCTIONS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_DELETED_FUNCTIONS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_EXPLICIT_CONVERSION_OPERATORS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_NOEXCEPT
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_TEMPLATE_ALIASES
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_USER_DEFINED_LITERALS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_DELEGATING_CONSTRUCTORS
#endif

#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_NO_UNICODE_LITERALS
#endif

#if ((__GNUC__ >= 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_HAS_CONSTEXPR_CMATH_FUNCTION
#endif

#if ((__GNUC__ >= 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) && defined(__GXX_EXPERIMENTAL_CXX0X__))
#	define SPROUT_HAS_CONSTEXPR_BIT_OPERATION
#endif

#endif	// #ifndef SPROUT_CONFIG_COMPILER_GCC_HPP
