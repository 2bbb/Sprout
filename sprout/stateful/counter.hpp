/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_COUNTER_HPP
#define SPROUT_STATEFUL_COUNTER_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	namespace counter_detail {
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wnon-template-friend"
#endif
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wundefined-inline"
#endif
		template<int N>
		struct tag {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::counter_detail::tag<N>);
		};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#if defined(__GNUC__) && !defined(__clang__)
#	pragma GCC diagnostic pop
#endif

		template<int N>
		struct state {
			friend SPROUT_CONSTEXPR int adl_counter(sprout::counter_detail::tag<N>) {
				return N;
			}
			SPROUT_STATIC_CONSTEXPR int value = N;
		};
		template<int N>
		SPROUT_CONSTEXPR_OR_CONST int sprout::counter_detail::state<N>::value;

		template<int N, int = adl_counter(sprout::counter_detail::tag<N>())>
		SPROUT_CONSTEXPR bool check_impl(int, sprout::counter_detail::tag<N>) {
			return true;
		}
		template<int N>
		SPROUT_CONSTEXPR bool check_impl(long, sprout::counter_detail::tag<N>) {
			return false;
		}
		template<int N>
		SPROUT_CONSTEXPR bool check(bool R = sprout::counter_detail::check_impl(0, sprout::counter_detail::tag<N>())) {
			return R;
		}

		template<int N>
		SPROUT_CONSTEXPR int counter_impl(sprout::false_type, sprout::counter_detail::tag<N>) {
			return 0;
		}
		template<int N>
		SPROUT_CONSTEXPR int counter_impl(
			sprout::true_type, sprout::counter_detail::tag<N>,
			int R = !sprout::counter_detail::check<N>() ? N
				: counter_impl(sprout::bool_constant<sprout::counter_detail::check<N>()>(), sprout::counter_detail::tag<N + 1>())
			)
		{
			return R;
		}
		template<int N = 0>
		SPROUT_CONSTEXPR int counter(int R = sprout::counter_detail::counter_impl(sprout::true_type(), sprout::counter_detail::tag<N>())) {
			return R;
		}
	}	// namespace counter_detail
	//
	// counter
	//
	template<
		int N = 1,
		int R = sprout::counter_detail::state<
			sprout::counter_detail::counter() + N - 1
			>::value
	>
	SPROUT_CONSTEXPR int counter() {
		return R;
	}

#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_STATEFUL_COUNTER_HPP
