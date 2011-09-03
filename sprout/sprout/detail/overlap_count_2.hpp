#ifndef SPROUT_DETAIL_OVERLAP_COUNT_2_HPP
#define SPROUT_DETAIL_OVERLAP_COUNT_2_HPP

#include <iterator>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		//
		// overlap_count_2
		//
		template<typename Iterator1, typename Iterator2, typename Compare>
		SPROUT_CONSTEXPR inline typename std::iterator_traits<Iterator1>::difference_type overlap_count_2(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2,
			Compare comp
			)
		{
			return first1 != last1 && first2 != last2
				? comp(*first1, *first2)
					? sprout::detail::overlap_count_2(first1 + 1, last1, first2, last2, comp)
					: comp(*first2, *first1)
						? sprout::detail::overlap_count_2(first1, last1, first2 + 1, last2, comp)
						: 1 + sprout::detail::overlap_count_2(first1 + 1, last1, first2 + 1, last2, comp)
				: 0
				;
		}
		//
		// overlap_count_2
		//
		template<typename Iterator1, typename Iterator2>
		SPROUT_CONSTEXPR inline typename std::iterator_traits<Iterator1>::difference_type overlap_count_2(
			Iterator1 first1,
			Iterator1 last1,
			Iterator2 first2,
			Iterator2 last2
			)
		{
			return first1 != last1 && first2 != last2
				? *first1 < *first2
					? sprout::detail::overlap_count_2(first1 + 1, last1, first2, last2)
					: *first2 < *first1
						? sprout::detail::overlap_count_2(first1, last1, first2 + 1, last2)
						: 1 + sprout::detail::overlap_count_2(first1 + 1, last1, first2 + 1, last2)
				: 0
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_OVERLAP_COUNT_2_HPP
