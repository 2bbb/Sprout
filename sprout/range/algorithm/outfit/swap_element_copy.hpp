#ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_RANGE_ALGORITHM_OUTFIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/outfit/swap_element_copy.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace outfit {
			//
			// swap_element_copy
			//
			template<typename Input, typename Result>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> swap_element_copy(
				Input const& input,
				Result const& result,
				typename sprout::fixed_container_traits<Input>::const_iterator pos1,
				typename sprout::fixed_container_traits<Input>::const_iterator pos2
				)
			{
				return sprout::outfit::swap_element_copy(sprout::begin(input), sprout::end(input), result, pos1, pos2);
			}
		}	// namespace outfit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_OUTFIT_SWAP_ELEMENT_COPY_HPP
