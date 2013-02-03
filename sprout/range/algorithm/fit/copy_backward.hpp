#ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_BACKWARD_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_COPY_BACKWARD_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/copy_backward.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// copy_backward
			//
			template<typename BidirectionalRange, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			copy_backward(BidirectionalRange const& rng, Result const& result) {
				return sprout::fit::copy_backward(sprout::begin(rng), sprout::end(rng), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_COPY_BACKWARD_HPP
