#ifndef SPROUT_ITERATOR_DISTANCE_HPP
#define SPROUT_ITERATOR_DISTANCE_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl iterator_distance(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!std::is_pointer<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		iterator_distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag*) {
			return last - first;
		}

		// Copyright (C) 2011 RiSK (sscrisk)
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		iterator_distance_impl(InputIterator first, InputIterator last) {
			return first == last ? 0
				: 1 + sprout::iterator_detail::iterator_distance_impl(sprout::next(first), last)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		iterator_distance(InputIterator first, InputIterator last, void*) {
			return sprout::iterator_detail::iterator_distance_impl(first, last);
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		iterator_distance(InputIterator first, InputIterator last) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::iterator_detail::iterator_distance(first, last, category());
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		using sprout::iterator_detail::iterator_distance;
		using sprout_adl::iterator_distance;
		return iterator_distance(first, last);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// distance
	//
	//	effect:
	//		ADL callable iterator_distance(first, last) -> iterator_distance(first, last)
	//		[first, last) is RandomAccessIterator && not Pointer -> last - first
	//		otherwise -> linearly count: first to last
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return sprout_iterator_detail::distance(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DISTANCE_HPP
