#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_UNTIL_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_UNTIL_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy_until.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy_until
			//
			template<typename Input, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_until(Input const& input, Result const& result, Predicate pred) {
				return sprout::fixed::copy_until(sprout::begin(input), sprout::end(input), result);
			}

			template<typename Result, typename Input, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy_until(Input const& input, Predicate pred) {
				return sprout::fixed::copy_until<Result>(sprout::begin(input), sprout::end(input));
			}
		}	// namespace fixed

		using sprout::range::fixed::copy_until;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_UNTIL_HPP
