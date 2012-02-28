#ifndef SPROUT_TUPLE_OPERATION_APPEND_BACK_HPP
#define SPROUT_TUPLE_OPERATION_APPEND_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/operation/append_back.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// append_back
			//
			template<typename Tuple, typename InputTuple>
			struct append_back
				: public sprout::types::append_back<Tuple, InputTuple>
			{};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename InputTuple, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
			SPROUT_CONSTEXPR inline Result append_back_impl(
				Tuple const& t,
				InputTuple const& input,
				sprout::index_tuple<Indexes1...>,
				sprout::index_tuple<Indexes2...>
				)
			{
				return sprout::tuples::remake_clone<Result>(
					t,
					sprout::tuples::get<Indexes1>(t)...,
					sprout::tuples::get<Indexes2>(input)...
					);
			}
		}	// namespace detail
		//
		// append_back
		//
		template<typename Tuple, typename InputTuple>
		SPROUT_CONSTEXPR inline typename sprout::tuples::result_of::append_back<Tuple, InputTuple>::type append_back(
			Tuple const& t,
			InputTuple const& input
			)
		{
			return sprout::tuples::detail::append_back_impl<typename sprout::tuples::result_of::append_back<Tuple, InputTuple>::type>(
				t,
				input,
				typename sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::type(),
				typename sprout::index_range<0, sprout::tuples::tuple_size<InputTuple>::value>::type()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_APPEND_BACK_HPP
