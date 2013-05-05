#ifndef SPROUT_MATH_FRACTIONAL_PART_HPP
#define SPROUT_MATH_FRACTIONAL_PART_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/integer_part.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fractional_part_impl(T x, T ipart) {
				return x == ipart ? T(0) * x
					: sprout::math::copysign(x - ipart, x)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			fractional_part(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity() ? sprout::math::copysign(FloatType(0), x)
					: x == 0 ? x
					: sprout::math::detail::fractional_part_impl(x, sprout::integer_part(x))
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			fractional_part(IntType x) {
				return sprout::math::detail::fractional_part(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::fractional_part;
	}	// namespace math

	using sprout::math::fractional_part;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FRACTIONAL_PART_HPP
