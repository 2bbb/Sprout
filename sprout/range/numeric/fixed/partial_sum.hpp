/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_FIXED_PARTIAL_SUM_HPP
#define SPROUT_RANGE_NUMERIC_FIXED_PARTIAL_SUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/fixed/partial_sum.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// partial_sum
			//
			template<typename InputRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(InputRange const& rng, Result const& result) {
				return sprout::fixed::partial_sum(sprout::begin(rng), sprout::end(rng), result);
			}
			template<typename InputRange, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(InputRange const& rng, Result const& result, BinaryOperation binary_op) {
				return sprout::fixed::partial_sum(sprout::begin(rng), sprout::end(rng), result, binary_op);
			}

			template<typename Result, typename InputRange>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(InputRange const& rng) {
				return sprout::fixed::partial_sum<Result>(sprout::begin(rng), sprout::end(rng));
			}
			template<typename Result, typename InputRange, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			partial_sum(InputRange const& rng, BinaryOperation binary_op) {
				return sprout::fixed::partial_sum<Result>(sprout::begin(rng), sprout::end(rng), binary_op);
			}
		}	// namespace fixed

		using sprout::range::fixed::partial_sum;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIXED_PARTIAL_SUM_HPP
