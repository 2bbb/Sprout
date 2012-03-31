#ifndef SPROUT_RANGE_ALGORITHM_FIT_REVERSE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIT_REVERSE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/algorithm/fit/reverse_copy.hpp>

namespace sprout {
	namespace range {
		namespace fit {
			//
			// reverse_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type reverse_copy(
				Input const& input,
				Result const& result
				)
			{
				return sprout::fit::reverse_copy(sprout::begin(input), sprout::end(input), result);
			}
		}	// namespace fit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIT_REVERSE_COPY_HPP
