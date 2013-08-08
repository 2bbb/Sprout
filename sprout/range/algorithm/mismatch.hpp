/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_MISMATCH_HPP
#define SPROUT_RANGE_ALGORITHM_MISMATCH_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/range/type_traits/lvalue_iterator.hpp>
#include <sprout/algorithm/mismatch.hpp>

namespace sprout {
	namespace range {

		// 25.2.10 Mismatch
		template<typename InputRange1, typename InputRange2>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<InputRange1>::type,
			typename sprout::range::lvalue_iterator<InputRange2>::type
		>
		mismatch(InputRange1&& range1, InputRange2&& range2) {
			return sprout::mismatch(
				sprout::begin(sprout::forward<InputRange1>(range1)),
				sprout::end(sprout::forward<InputRange1>(range1)),
				sprout::begin(sprout::forward<InputRange2>(range2))
				);
		}

		template<typename InputRange1, typename InputRange2, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::range::lvalue_iterator<InputRange1>::type,
			typename sprout::range::lvalue_iterator<InputRange2>::type
		>
		mismatch(InputRange1&& range1, InputRange2&& range2, BinaryPredicate pred) {
			return sprout::mismatch(
				sprout::begin(sprout::forward<InputRange1>(range1)),
				sprout::end(sprout::forward<InputRange1>(range1)),
				sprout::begin(sprout::forward<InputRange2>(range2)),
				pred
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_MISMATCH_HPP
