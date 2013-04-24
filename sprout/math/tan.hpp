#ifndef SPROUT_MATH_TAN_HPP
#define SPROUT_MATH_TAN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/copysign.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			tan_impl(T x) {
				return sprout::math::sin(x) / sprout::math::cos(x);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			tan(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity()
						? std::numeric_limits<FloatType>::quiet_NaN()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::sin(x)
#else
					: x == 0 ? sprout::math::copysign(FloatType(0), x)
					: static_cast<FloatType>(sprout::math::detail::tan_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			tan(IntType x) {
				return sprout::math::detail::tan(static_cast<double>(x));
			}
		}	// namespace detail
		//
		// tan
		//
		template<
			typename ArithmeticType,
			typename sprout::enabler_if<std::is_arithmetic<ArithmeticType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType>::type
		tan(ArithmeticType x) {
			return sprout::math::detail::tan(x);
		}
	}	// namespace math

	using sprout::math::tan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TAN_HPP
