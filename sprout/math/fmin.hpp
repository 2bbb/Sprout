#ifndef SPROUT_MATH_FMIN_HPP
#define SPROUT_MATH_FMIN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			fmin(FloatType x, FloatType y) {
				return sprout::math::isnan(y) ? x
					: sprout::math::isnan(x) ? y
					: x == -std::numeric_limits<FloatType>::infinity() ? x
					: y == std::numeric_limits<FloatType>::infinity() ? x
					: y == -std::numeric_limits<FloatType>::infinity() ? y
					: x == std::numeric_limits<FloatType>::infinity() ? y
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: x == 0 && y == 0 ? x
					: std::fmin(x, y)
#else
					: y < x ? y : x
#endif
					;
			}
			template<
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
			fmin(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::fmin(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using sprout::math::detail::fmin;
	}	// namespace math

	using sprout::math::fmin;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMIN_HPP
