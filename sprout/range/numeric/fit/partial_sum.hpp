#ifndef SPROUT_RANGE_NUMERIC_FIT_PARTIAL_SUM_HPP
#define SPROUT_RANGE_NUMERIC_FIT_PARTIAL_SUM_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/numeric/fit/partial_sum.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// partial_sum
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partial_sum(Input const& input, Result const& result) {
				return sprout::fit::partial_sum(sprout::begin(input), sprout::end(input), result);
			}
			template<typename Input, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partial_sum(Input const& input, Result const& result, BinaryOperation binary_op) {
				return sprout::fit::partial_sum(sprout::begin(input), sprout::end(input), result, binary_op);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partial_sum(Input const& input) {
				return sprout::fit::partial_sum<Result>(sprout::begin(input), sprout::end(input));
			}
			template<typename Result, typename Input, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partial_sum(Input const& input, BinaryOperation binary_op) {
				return sprout::fit::partial_sum<Result>(sprout::begin(input), sprout::end(input), binary_op);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FIT_PARTIAL_SUM_HPP
