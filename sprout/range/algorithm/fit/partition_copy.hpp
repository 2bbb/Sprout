#ifndef SPROUT_RANGE_ALGORITHM_FIT_PARTITION_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_PARTITION_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/partition_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// partition_copy
			//
			template<typename InputRange, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partition_copy(InputRange const& rng, Result const& result, Predicate pred) {
				return sprout::fit::partition_copy(sprout::begin(rng), sprout::end(rng), result, pred);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_PARTITION_COPY_HPP
