/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_LOWER_BOUND_INDEX_HPP
#define SPROUT_TYPE_ALGORITHM_LOWER_BOUND_INDEX_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/functional/less.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last,
				std::size_t Distance = (Last - First)
			>
			struct lower_bound_index_impl;
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last
			>
			struct lower_bound_index_impl<
				Tuple, T, Compare, First, Last,
				0
			>
				: public sprout::integral_constant<std::size_t, Last>
			{};
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last
			>
			struct lower_bound_index_impl<
				Tuple, T, Compare, First, Last,
				1
			>
				: public sprout::integral_constant<
					std::size_t,
					Compare::template apply<typename sprout::types::tuple_element<First, Tuple>::type, T>::type::value ? Last : First
				>
			{};
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last,
				std::size_t Distance
			>
			struct lower_bound_index_impl
				: public std::conditional<
					Compare::template apply<typename sprout::types::tuple_element<First + Distance / 2, Tuple>::type, T>::type::value,
					sprout::types::detail::lower_bound_index_impl<Tuple, T, Compare, First + Distance / 2, Last>,
					sprout::types::detail::lower_bound_index_impl<Tuple, T, Compare, First, First + Distance / 2>
				>::type
			{};
		}	// namespace detail
		//
		// lower_bound_index
		//
		template<typename Tuple, typename T, typename Compare = sprout::types::less_>
		struct lower_bound_index
			: public sprout::types::detail::lower_bound_index_impl<Tuple, T, Compare, 0, sprout::types::tuple_size<Tuple>::value>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_LOWER_BOUND_INDEX_HPP
