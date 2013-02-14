#ifndef SPROUT_MATH_IROUND_HPP
#define SPROUT_MATH_IROUND_HPP

#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <sprout/math/round.hpp>
#else
#	include <sprout/math/equal_to.hpp>
#endif

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iround_impl(FloatType x) {
				return std::numeric_limits<To>::max() < x || std::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::domain_error("iround: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iround(FloatType x) {
				return sprout::math::detail::iround_impl<To>(sprout::math::round(x));
			}
#else
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iround_impl_positive(FloatType x, To x0) {
				return x - x0 < FloatType(0.5) ? x0
					: x0 + 1
					;
			}
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iround_impl_nagative(FloatType x, To x0) {
				return x0 - x < FloatType(0.5) ? x0
					: x0 - 1
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iround(FloatType x) {
				return x == 0 ? To(0)
					: std::numeric_limits<To>::max() < x || std::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::domain_error("iround: large float irounding."), x)
					: x < 0 ? sprout::math::detail::iround_impl_nagative(x, static_cast<To>(x))
					: sprout::math::detail::iround_impl_positive(x, static_cast<To>(x))
					;
			}
#endif
			template<
				typename To = int,
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iround(IntType x) {
				return sprout::math::detail::iround(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::iround;
	}	// namespace math

	using sprout::math::iround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_IROUND_HPP
