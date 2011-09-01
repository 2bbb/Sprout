#ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/replace_copy_if.hpp>

namespace sprout {
	namespace range {
		namespace fixed {
			//
			// replace_copy_if
			//
			template<typename Input, typename Result, typename T, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type replace_copy_if(
				Input const& input,
				Result const& result,
				Predicate pred,
				T const& new_value
				)
			{
				return sprout::fixed::replace_copy_if(sprout::begin(input), sprout::end(input), result, pred, new_value);
			}
		}	// namespace fixed
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_FIXED_REPLACE_COPY_IF_HPP
