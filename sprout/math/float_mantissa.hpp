#ifndef SPROUT_MATH_FLOAT_MANTISSA_HPP
#define SPROUT_MATH_FLOAT_MANTISSA_HPP

#include <cfloat>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/float_exponent.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			float_mantissa(FloatType x) {
				return x / sprout::detail::pow_n(FloatType(FLT_RADIX), sprout::math::float_exponent(x));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			float_mantissa(IntType x) {
				return sprout::math::detail::float_mantissa(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::float_mantissa;
	}	// namespace math

	using sprout::math::float_mantissa;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_MANTISSA_HPP
