#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/replace_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// replace_copy
			//
			template<typename InputRange, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			replace_copy(InputRange const& rng, Result const& result, T const& old_value, T const& new_value) {
				return sprout::fixed::replace_copy(sprout::begin(rng), sprout::end(rng), result, old_value, new_value);
			}

			template<typename Result, typename InputRange, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			replace_copy(InputRange const& rng, T const& old_value, T const& new_value) {
				return sprout::fixed::replace_copy<Result>(sprout::begin(rng), sprout::end(rng), old_value, new_value);
			}
		}	// namespace fixed

		using sprout::range::fixed::replace_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_HPP
