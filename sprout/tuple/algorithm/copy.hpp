#ifndef SPROUT_TUPLE_ALGORITHM_COPY_HPP
#define SPROUT_TUPLE_ALGORITHM_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/tuple/functions.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// copy
			//
			template<typename Tuple, typename InputTuple>
			struct copy {
			public:
				typedef typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename InputTuple, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
			SPROUT_CONSTEXPR inline Result copy_impl(
				Tuple const& t,
				InputTuple const& input,
				sprout::index_tuple<Indexes1...>,
				sprout::index_tuple<Indexes2...>
				)
			{
				return sprout::tuples::remake<Result>(
					t,
					sprout::tuples::get<Indexes2>(input)...,
					sprout::tuples::get<Indexes1>(t)...
					);
			}
			template<typename Tuple, typename InputTuple>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::tuples::tuple_size<Tuple>::value > sprout::tuples::tuple_size<InputTuple>::value),
				typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type
			>::type copy(
				Tuple const& t,
				InputTuple const& input
				)
			{
				return sprout::tuples::detail::copy_impl<typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type>(
					t,
					input,
					typename sprout::index_range<sprout::tuples::tuple_size<InputTuple>::value, sprout::tuples::tuple_size<Tuple>::value>::type(),
					typename sprout::index_range<0, sprout::tuples::tuple_size<InputTuple>::value>::type()
					);
			}
			template<typename Tuple, typename InputTuple>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				!(sprout::tuples::tuple_size<Tuple>::value > sprout::tuples::tuple_size<InputTuple>::value),
				typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type
			>::type copy(
				Tuple const& t,
				InputTuple const& input
				)
			{
				return sprout::tuples::detail::copy_impl<typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type>(
					t,
					input,
					sprout::index_tuple<>(),
					typename sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::type()
					);
			}
		}	// namespace detail
		//
		// copy
		//
		template<typename Tuple, typename InputTuple>
		SPROUT_CONSTEXPR inline typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type copy(
			Tuple const& t,
			InputTuple const& input
			)
		{
			return sprout::tuples::detail::copy(
				t,
				input
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_ALGORITHM_COPY_HPP
