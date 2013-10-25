/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_PARTITION_COPY_HPP
#define SPROUT_ALGORITHM_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/utility/pair.hpp>

namespace sprout {
	//
	// 25.3.13 Partitions
	//
	template<typename InputIterator, typename OutputIterator1, typename OutputIterator2, typename Predicate>
	inline SPROUT_CXX14_CONSTEXPR sprout::pair<OutputIterator1, OutputIterator2>
	partition_copy(InputIterator first, InputIterator last, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred); // !!!
}	// namespace sprout

#include <sprout/algorithm/fixed/partition_copy.hpp>
#include <sprout/algorithm/fit/partition_copy.hpp>

#endif	// #ifndef SPROUT_ALGORITHM_PARTITION_COPY_HPP
