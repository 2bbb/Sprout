#ifndef SPROUT_RANGE_ALGORITHM_INFIT_REMOVE_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_INFIT_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/remove_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// remove_copy
			//
			template<typename Input, typename Result, typename T>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> remove_copy(
				Input const& input,
				Result const& result,
				T const& value
				)
			{
				return sprout::infit::remove_copy(sprout::begin(input), sprout::end(input), result, value);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFIT_REMOVE_COPY_HPP
