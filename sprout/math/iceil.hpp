#ifndef SPROUT_MATH_ICEIL_HPP
#define SPROUT_MATH_ICEIL_HPP

#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <sprout/math/ceil.hpp>
#else
#	include <sprout/math/equal_to.hpp>
#endif

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iceil_impl(FloatType x) {
				return std::numeric_limits<To>::max() < x || std::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::domain_error("iceil: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iceil(FloatType x) {
				return sprout::math::detail::iceil_impl<To>(sprout::math::ceil(x));
			}
#else
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iceil_impl(FloatType x, To x0) {
				return sprout::math::equal_to(x, x0) ? x0
					: x0 + 1
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iceil(FloatType x) {
				return x == 0 ? To(0)
					: std::numeric_limits<To>::max() < x || std::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::domain_error("iceil: large float rounding."), static_cast<To>(x))
					: sprout::math::detail::iceil_impl(x, static_cast<To>(x))
					;
			}
#endif
			template<
				typename To = int,
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iceil(IntType x) {
				return sprout::math::detail::iceil<To>(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::iceil;
	}	// namespace math

	using sprout::math::iceil;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ICEIL_HPP
