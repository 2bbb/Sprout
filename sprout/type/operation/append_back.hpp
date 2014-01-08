/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_APPEND_BACK_HPP
#define SPROUT_TYPE_OPERATION_APPEND_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/tuple/indexes.hpp>

namespace sprout {
	namespace types {
		//
		// append_back
		//
		template<typename Tuple, typename InputTuple>
		struct append_back {
		private:
			template<typename IndexTuple1, typename IndexTuple2>
			struct apply_impl;
			template<sprout::index_t... Indexes1, sprout::index_t... Indexes2>
			struct apply_impl<sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...> >
				: public sprout::types::rebind_types<
					Tuple
				>::template apply<
					typename sprout::types::tuple_element<Indexes1, Tuple>::type...,
					typename sprout::types::tuple_element<Indexes2, InputTuple>::type...
				>
			{};
		public:
			typedef typename apply_impl<
				typename sprout::tuple_indexes<Tuple>::type,
				typename sprout::tuple_indexes<InputTuple>::type
			>::type type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_APPEND_BACK_HPP
