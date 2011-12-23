#ifndef TESTSPR_SPROUT_ALGORITHM_NTH_ELEMENT_HPP
#define TESTSPR_SPROUT_ALGORITHM_NTH_ELEMENT_HPP

#include <sprout/algorithm/nth_element.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_nth_element_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// �\�[�g
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					arr1,
					sprout::begin(arr1) + 4
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 10>{{2, 4, 1, 3, 5, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					arr1,
					sprout::begin(arr1) + 4
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 5>{{2, 4, 1, 3, 5}}
					));
			}
			// �\�[�g
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 6>{{2, 3, 5, 9, 8, 6}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 3>{{2, 3, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{10, 7, 8, 6, 9, 2, 5, 3, 4, 1}};

			// �\�[�g
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					arr1,
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 10>{{2, 4, 1, 3, 5, 10, 9, 8, 7, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					arr1,
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 5>{{2, 4, 1, 3, 5}}
					));
			}
			// �\�[�g
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 6>{{2, 3, 5, 9, 8, 6}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto nth = sprout::fit::nth_element(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 4,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					nth,
					array<int, 3>{{2, 3, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(nth),
					array<int, 10>{{10, 7, 2, 3, 5, 9, 8, 6, 4, 1}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_NTH_ELEMENT_HPP

