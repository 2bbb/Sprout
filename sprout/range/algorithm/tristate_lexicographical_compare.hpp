#ifndef SPROUT_RANGE_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP
#define SPROUT_RANGE_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/tristate_lexicographical_compare.hpp>

namespace sprout {
	namespace range {
		//
		// tristate_lexicographical_compare
		//
		template<typename Range1, typename Range2>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(Range1 const& range1, Range2 const& range2) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2)
				);
		}

		template<typename Range1, typename Range2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(Range1 const& range1, Range2 const& range2, Compare comp) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), sprout::begin(range2), sprout::end(range2), comp
				);
		}

		template<typename Range1, typename T1, typename Range2, typename T2>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(Range1 const& range1, T1 const& delim1, Range2 const& range2, T2 const& delim2) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), delim1, sprout::begin(range2), sprout::end(range2), delim2
				);
		}

		template<typename Range1, typename T1, typename Range2, typename T2, typename Compare>
		inline SPROUT_CONSTEXPR int
		tristate_lexicographical_compare(Range1 const& range1, T1 const& delim1, Range2 const& range2, T2 const& delim2, Compare comp) {
			return sprout::tristate_lexicographical_compare(
				sprout::begin(range1), sprout::end(range1), delim1, sprout::begin(range2), sprout::end(range2), delim2, comp
				);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_TRISTATE_LEXICOGRAPHICAL_COMPARE_HPP
