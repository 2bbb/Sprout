#ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
#define SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/swap_element_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type swap_element_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				InputIterator pos1,
				InputIterator pos2,
				typename sprout::fixed_container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::swap_element_copy(first, last, result, pos1, pos2)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::min(NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// swap_element_copy
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Result>::type swap_element_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			InputIterator pos1,
			InputIterator pos2
			)
		{
			return sprout::fit::detail::swap_element_copy_impl(first, last, result, pos1, pos2, sprout::fixed_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_SWAP_ELEMENT_COPY_HPP
