/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_COND_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_COND_HPP

#include <utility>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// cond_t
	// cond_
	//
	struct cond_t {
	public:
		template<typename T, typename U, typename V>
		SPROUT_CONSTEXPR decltype(std::declval<T>() ? std::declval<U>() : std::declval<V>())
		operator()(T&& x, U&& y, V&& z)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<T>() ? std::declval<U>() : std::declval<V>()))
		{
			return sprout::forward<T>(x) ? sprout::forward<U>(y) : sprout::forward<V>(z);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::cond_t cond_ = {};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_COND_HPP
