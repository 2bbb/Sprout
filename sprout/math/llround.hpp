#ifndef SPROUT_MATH_LLROUND_HPP
#define SPROUT_MATH_LLROUND_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iround.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long long
			llround(FloatType x) {
				return sprout::math::isnan(x) || sprout::math::isinf(x) ? std::numeric_limits<long long>::min()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::llround(x)
#else
					: sprout::math::iround<long long>(x);
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long long
			llround(IntType x) {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				return std::llround(x);
#else
				return sprout::math::iround<long long>(x);
#endif
			}
		}	// namespace detail

		using sprout::math::detail::llround;
	}	// namespace math

	using sprout::math::llround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LLROUND_HPP
