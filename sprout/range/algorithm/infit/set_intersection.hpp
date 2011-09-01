#ifndef SPROUT_RANGE_ALGORITHM_INFOT_SET_INTERSECTION_HPP
#define SPROUT_RANGE_ALGORITHM_INFOT_SET_INTERSECTION_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/set_intersection.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// set_intersection
			//
			template<typename Input1, typename Input2, typename Result, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type set_intersection(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result,
				Compare comp
				)
			{
				return sprout::infit::set_intersection(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result, comp);
			}

			//
			// set_intersection
			//
			template<typename Input1, typename Input2, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type set_intersection(
				Input1 const& input1,
				Input2 const& input2,
				Result const& result
				)
			{
				return sprout::infit::set_intersection(sprout::begin(input1), sprout::end(input1), sprout::begin(input2), sprout::end(input2), result);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFOT_SET_INTERSECTION_HPP
