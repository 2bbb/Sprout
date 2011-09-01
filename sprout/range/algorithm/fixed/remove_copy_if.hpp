#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// remove_copy_if
			//
			template<typename Input, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type remove_copy_if(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::fixed::remove_copy_if(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP
