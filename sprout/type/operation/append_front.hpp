#ifndef SPROUT_TYPE_OPERATION_APPEND_FRONT_HPP
#define SPROUT_TYPE_OPERATION_APPEND_FRONT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		//
		// append_front
		//
		template<typename Tuple, typename InputTuple>
		struct append_front {
		private:
			template<typename IndexTuple1, typename IndexTuple2>
			struct apply_impl;
			template<std::ptrdiff_t... Indexes1, std::ptrdiff_t... Indexes2>
			struct apply_impl<sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...> >
				: public sprout::types::rebind_types<
					Tuple
				>::template apply<
					typename sprout::types::tuple_element<Indexes2, InputTuple>::type...,
					typename sprout::types::tuple_element<Indexes1, Tuple>::type...
				>
			{};
		public:
			typedef typename apply_impl<
				typename sprout::index_range<0, sprout::types::tuple_size<Tuple>::value>::type,
				typename sprout::index_range<0, sprout::types::tuple_size<InputTuple>::value>::type
			>::type type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_APPEND_FRONT_HPP
