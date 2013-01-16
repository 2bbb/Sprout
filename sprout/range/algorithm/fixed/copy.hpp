#ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// copy
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy(Input const& input, Result const& result) {
				return sprout::fixed::copy(sprout::begin(input), sprout::end(input), result);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			copy(Input const& input) {
				return sprout::fixed::copy<Result>(sprout::begin(input), sprout::end(input));
			}
		}	// namespace fixed

		using sprout::range::fixed::copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_COPY_HPP
