/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ALGORITHM_IS_HEAP_UNTIL_HPP
#define SPROUT_RANGE_ALGORITHM_IS_HEAP_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/range/range_return.hpp>
#include <sprout/algorithm/is_heap_until.hpp>

namespace sprout {
	namespace range {

		// 25.4.6.5 is_heap
		template<typename RandomAccessRange>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<RandomAccessRange>::type
		is_heap_until(RandomAccessRange&& range) {
			return sprout::range::range_return<RandomAccessRange>::pack(
				sprout::is_heap_until(
					sprout::begin(sprout::forward<RandomAccessRange>(range)),
					sprout::end(sprout::forward<RandomAccessRange>(range))
					),
				sprout::forward<RandomAccessRange>(range)
				);
		}

		template<typename RandomAccessRange, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<RandomAccessRange>::type
		is_heap_until(RandomAccessRange&& range, Compare comp) {
			return sprout::range::range_return<RandomAccessRange>::pack(
				sprout::is_heap_until(
					sprout::begin(sprout::forward<RandomAccessRange>(range)),
					sprout::end(sprout::forward<RandomAccessRange>(range)),
					comp
					),
				sprout::forward<RandomAccessRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename RandomAccessRange>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<RandomAccessRange, RetV>::type
		is_heap_until(RandomAccessRange&& range) {
			return sprout::range::range_return<RandomAccessRange, RetV>::pack(
				sprout::is_heap_until(
					sprout::begin(sprout::forward<RandomAccessRange>(range)),
					sprout::end(sprout::forward<RandomAccessRange>(range))
					),
				sprout::forward<RandomAccessRange>(range)
				);
		}

		template<sprout::range::range_return_value RetV, typename RandomAccessRange, typename Compare>
		inline SPROUT_CONSTEXPR typename sprout::range::range_return<RandomAccessRange, RetV>::type
		is_heap_until(RandomAccessRange&& range, Compare comp) {
			return sprout::range::range_return<RandomAccessRange, RetV>::pack(
				sprout::is_heap_until(
					sprout::begin(sprout::forward<RandomAccessRange>(range)),
					sprout::end(sprout::forward<RandomAccessRange>(range)),
					comp
					),
				sprout::forward<RandomAccessRange>(range)
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_IS_HEAP_UNTIL_HPP
