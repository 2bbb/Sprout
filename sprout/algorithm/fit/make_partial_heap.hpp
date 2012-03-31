#ifndef SPROUT_ALGORITHM_FIT_MAKE_PARTIAL_HEAP_HPP
#define SPROUT_ALGORITHM_FIT_MAKE_PARTIAL_HEAP_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/make_partial_heap.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type make_partial_heap_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::const_iterator middle,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::make_partial_heap(cont, middle, comp)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), middle)
					);
			}
		}	// namespace detail
		//
		// make_partial_heap
		//
		template<typename Container, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type make_partial_heap(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator middle,
			Compare comp
			)
		{
			return sprout::fit::detail::make_partial_heap_impl(cont, middle, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type make_partial_heap_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::const_iterator middle,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::make_partial_heap(cont, middle)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(sprout::begin(cont), middle)
					);
			}
		}	// namespace detail
		//
		// make_partial_heap
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type make_partial_heap(
			Container const& cont,
			typename sprout::container_traits<Container>::const_iterator middle
			)
		{
			return sprout::fit::detail::make_partial_heap_impl(cont, middle, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_MAKE_PARTIAL_HEAP_HPP
