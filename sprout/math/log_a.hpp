#ifndef SPROUT_MATH_LOG_A_HPP
#define SPROUT_MATH_LOG_A_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
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
			log_a(FloatType x, FloatType y) {
				return x == 2 ? sprout::log(y) / sprout::math::ln_two<FloatType>()
					: x == 10 ? sprout::log(y) / sprout::math::ln_ten<FloatType>()
					: sprout::log(y) / sprout::log(x)
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
			log_a(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::log_a(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using sprout::math::detail::log_a;
	}	// namespace math

	using sprout::math::log_a;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG_A_HPP
