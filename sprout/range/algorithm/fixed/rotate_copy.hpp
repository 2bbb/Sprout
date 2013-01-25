#ifndef SPROUT_RANGE_ALGORITHM_FIXED_ROTATE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_ROTATE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/rotate_copy.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// rotate_copy
			//
			template<typename Input, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			rotate_copy(
				Input const& input, typename sprout::container_traits<Input>::const_iterator middle,
				Result const& result
				)
			{
				return sprout::fixed::rotate_copy(sprout::begin(input), middle, sprout::end(input), result);
			}

			template<typename Result, typename Input>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			rotate_copy(
				Input const& input, typename sprout::container_traits<Input>::const_iterator middle
				)
			{
				return sprout::fixed::rotate_copy<Result>(sprout::begin(input), middle, sprout::end(input));
			}
		}	// namespace fixed

		using sprout::range::fixed::rotate_copy;
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_ROTATE_COPY_HPP
