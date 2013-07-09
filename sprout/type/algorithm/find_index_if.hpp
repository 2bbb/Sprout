#ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP
#define SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple, typename Predicate, std::size_t I, typename = void>
			struct find_index_if_impl;
			template<typename Tuple, typename Predicate, std::size_t I>
			struct find_index_if_impl<
				Tuple, Predicate, I,
				typename std::enable_if<
					I == sprout::types::tuple_size<Tuple>::value
					|| Predicate::template apply<typename sprout::types::tuple_element<I, Tuple>::type>::type::value
				>::type
			>
				: public std::integral_constant<std::size_t, I>
			{};
			template<typename Tuple, typename Predicate, std::size_t I>
			struct find_index_if_impl<
				Tuple, Predicate, I,
				typename std::enable_if<
					I != sprout::types::tuple_size<Tuple>::value
					&& !Predicate::template apply<typename sprout::types::tuple_element<I, Tuple>::type>::type::value
				>::type
			>
				: public sprout::types::detail::find_index_if_impl<Tuple, Predicate, I + 1>
			{};
		}	// namespace detail
		//
		// find_index_if
		//
		template<typename Tuple, typename Predicate>
		struct find_index_if
			: public sprout::types::detail::find_index_if_impl<Tuple, Predicate, 0>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP
