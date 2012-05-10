#ifndef SPROUT_MATH_LOG2HPP
#define SPROUT_MATH_LOG2HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/utility/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <cmath>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log2(FloatType x) {
				return sprout::math::log(x) / sprout::math::ln_two<FloatType>();
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log2(IntType x) {
				return sprout::math::detail::log2(static_cast<double>(x));
			}
		}	// namespace detail

#	if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		using std::log2;
#	else
		using sprout::math::detail::log2;
#	endif
	}	// namespace math

	using sprout::math::log2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG2HPP
