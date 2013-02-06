#ifndef SPROUT_MATH_EXP_HPP
#define SPROUT_MATH_EXP_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			exp_impl_1(T x, std::size_t n, std::size_t last) {
				return last - n == 1
					? sprout::detail::pow_n(x, n) / sprout::math::factorial<T>(n)
					: sprout::math::detail::exp_impl_1(x, n, n + (last - n) / 2)
						+ sprout::math::detail::exp_impl_1(x, n + (last - n) / 2, last)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			exp_impl(T x) {
				return 1 + sprout::math::detail::exp_impl_1(x, 1, sprout::math::factorial_limit<T>() + 1);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			exp(FloatType x) {
				typedef double type;
				return !(x > -1) ? 1 / sprout::math::detail::exp_impl(-static_cast<type>(x))
					: sprout::math::detail::exp_impl(static_cast<type>(x))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			exp(IntType x) {
				return sprout::math::detail::exp(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::exp;
	}	// namespace math

	using sprout::math::exp;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP_HPP
