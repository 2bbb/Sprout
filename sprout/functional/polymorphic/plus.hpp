#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PLUS_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_PLUS_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// plus_t
	// plus_
	//
	struct plus_t {
	public:
		template<typename T, typename U>
		SPROUT_CONSTEXPR decltype(std::declval<T>() + std::declval<U>())
		operator()(T&& x, U&& y)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<T>() + std::declval<U>()))
		{
			return sprout::forward<T>(x) + sprout::forward<U>(y);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::plus_t plus_{};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_PLUS_HPP
