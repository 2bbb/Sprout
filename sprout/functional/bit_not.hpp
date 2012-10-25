#ifndef SPROUT_FUNCTIONAL_BIT_NOT_HPP
#define SPROUT_FUNCTIONAL_BIT_NOT_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	// 20.8.7 bitwise operations
	template<typename T = void>
	struct bit_not {
	public:
		typedef T argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x) const {
				return ~x;
		}
	};

	template<>
	struct bit_not<void> {
	public:
		template<typename T>
		SPROUT_CONSTEXPR decltype(~std::declval<T>())
		operator()(T&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(~std::declval<T>()))
		{
			return ~sprout::forward<T>(x);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIT_NOT_HPP
