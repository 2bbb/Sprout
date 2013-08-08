/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPERATION_FIXED_APPEND_BACK_HPP
#define SPROUT_OPERATION_FIXED_APPEND_BACK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/operation/fixed/append.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// append_back
			//
			template<typename Container, typename Input>
			struct append_back
				: public sprout::fixed::result_of::append<Container, Input>
			{};
		}	// namespace result_of

		//
		// append_back
		//
		template<typename Container, typename Input>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::append_back<Container, Input>::type
		append_back(Container const& cont, Input const& input) {
			return sprout::fixed::detail::append_impl<typename sprout::fixed::result_of::append_back<Container, Input>::type>(
				cont,
				sprout::container_indexes<typename sprout::fixed::result_of::append_back<Container, Input>::type>::make(),
				sprout::internal_end_offset(cont),
				sprout::size(input),
				input
				);
		}
	}	// namespace fixed

	namespace result_of {
		using sprout::fixed::result_of::append_back;
	}	// namespace result_of

	using sprout::fixed::append_back;
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_APPEND_BACK_HPP
