/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_FLOAT_PROMOTE_HPP
#define SPROUT_TYPE_TRAITS_FLOAT_PROMOTE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/std_type_traits.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		struct float_promote1
			: public sprout::conditional<
				sprout::is_floating_point<T>::value,
				T,
				double
			>
		{
			static_assert(
				sprout::is_arithmetic<T>::value,
				"float_promote requires arithmetic type."
				);
		};

		template<typename T, typename U>
		struct float_promote2
			: public sprout::conditional<
				(sprout::is_same<T, long double>::value || sprout::is_same<U, long double>::value),
				long double,
				typename sprout::conditional<
					(sprout::is_same<T, float>::value && sprout::is_same<U, float>::value),
					float,
					double
				>::type
			>
		{
			static_assert(
				sprout::is_arithmetic<T>::value && sprout::is_arithmetic<U>::value,
				"float_promote requires arithmetic type."
				);
		};

		template<typename... Types>
		struct float_promote_impl;
		template<typename T, typename U, typename... Tail>
		struct float_promote_impl<T, U, Tail...>
			: public sprout::detail::float_promote_impl<
				typename sprout::detail::float_promote2<T, U>::type,
				Tail...
			>
		{};
		template<typename T>
		struct float_promote_impl<T>
			: public sprout::detail::float_promote1<T>
		{};
	}	// namespace detail

	//
	// float_promote
	//
	template<typename... Types>
	struct float_promote
		: public sprout::detail::float_promote_impl<
			typename sprout::remove_cv<Types>::type...
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Types>
	using float_promote_t = typename sprout::float_promote<Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_FLOAT_PROMOTE_HPP
