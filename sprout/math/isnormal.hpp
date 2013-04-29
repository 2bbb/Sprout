#ifndef SPROUT_MATH_ISNORMAL_HPP
#define SPROUT_MATH_ISNORMAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/issubnormal.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			isnormal(FloatType x) {
				return !sprout::math::isnan(x)
					&& !sprout::math::isinf(x)
					&& !sprout::math::detail::issubnormal_or_zero(x)
					;
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::isnormal;
	}	// namespace math

	using sprout::math::isnormal;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISNORMAL_HPP
