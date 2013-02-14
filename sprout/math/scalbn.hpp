#ifndef SPROUT_MATH_SCALBN_HPP
#define SPROUT_MATH_SCALBN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			scalbn(FloatType x, int exp) {
				return x == 0 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
					: exp == 0 ? x
					: x * sprout::detail::pow_n(FloatType(std::numeric_limits<FloatType>::radix), exp)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			scalbn(IntType x, int exp) {
				return sprout::math::detail::scalbn(static_cast<double>(x), exp);
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::scalbn;
	}	// namespace math

	using sprout::math::scalbn;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SCALBN_HPP
