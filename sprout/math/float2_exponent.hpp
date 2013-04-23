#ifndef SPROUT_MATH_FLOAT2_EXPONENT_HPP
#define SPROUT_MATH_FLOAT2_EXPONENT_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/ilogb2.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			float2_exponent(FloatType x) {
				return x == 0 ? 0
					: sprout::ilogb2(x) + 1
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			float2_exponent(IntType x) {
				return sprout::math::detail::float2_exponent(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::float2_exponent;
	}	// namespace math

	using sprout::math::float2_exponent;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT2_EXPONENT_HPP
