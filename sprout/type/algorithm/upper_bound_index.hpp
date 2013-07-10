#ifndef SPROUT_TYPE_ALGORITHM_UPPER_BOUND_INDEX_HPP
#define SPROUT_TYPE_ALGORITHM_UPPER_BOUND_INDEX_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/functional/less.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last,
				std::size_t Distance = (Last - First)
			>
			struct upper_bound_index_impl;
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last
			>
			struct upper_bound_index_impl<
				Tuple, T, Compare, First, Last,
				0
			>
				: public std::integral_constant<std::size_t, Last>
			{};
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last
			>
			struct upper_bound_index_impl<
				Tuple, T, Compare, First, Last,
				1
			>
				: public std::integral_constant<
					std::size_t,
					!Compare::template apply<T, typename sprout::types::tuple_element<First, Tuple>::type>::type::value ? Last : First
				>
			{};
			template<
				typename Tuple, typename T, typename Compare, std::size_t First, std::size_t Last,
				std::size_t Distance
			>
			struct upper_bound_index_impl
				: public std::conditional<
					!Compare::template apply<T, typename sprout::types::tuple_element<First + Distance / 2, Tuple>::type>::type::value,
					sprout::types::detail::upper_bound_index_impl<Tuple, T, Compare, First + Distance / 2, Last>,
					sprout::types::detail::upper_bound_index_impl<Tuple, T, Compare, First, First + Distance / 2>
				>::type
			{};
		}	// namespace detail
		//
		// upper_bound_index
		//
		template<typename Tuple, typename T, typename Compare = sprout::types::less_>
		struct upper_bound_index
			: public sprout::types::detail::upper_bound_index_impl<Tuple, T, Compare, 0, sprout::types::tuple_size<Tuple>::value>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_UPPER_BOUND_INDEX_HPP
