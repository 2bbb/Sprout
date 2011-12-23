#ifndef TESTSPR_SPROUT_ALGORITHM_STABLE_SORT_HPP
#define TESTSPR_SPROUT_ALGORITHM_STABLE_SORT_HPP

#include <sprout/algorithm/stable_sort.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_stable_sort_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// �\�[�g
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::stable_sort(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::stable_sort(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}
					));
			}
			// �\�[�g
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::stable_sort(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 7, 8, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 7, 8, 9, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::stable_sort(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 3, 4, 7, 8, 9}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 3, 4, 7, 8, 9, 10, 6}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{5, 1, 9, 4, 8, 2, 7, 3, 10, 6}};

			// �\�[�g
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::stable_sort(
					arr1,
					testspr::mod_less<int, 5>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{5, 10, 1, 6, 2, 7, 8, 3, 9, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::stable_sort(
					arr1,
					testspr::mod_less<int, 5>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 10>{{5, 10, 1, 6, 2, 7, 8, 3, 9, 4}}
					));
			}
			// �\�[�g
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::stable_sort(
					sprout::sub(arr1, 2, 8),
					testspr::mod_less<int, 5>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 7, 8, 3, 9, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 7, 8, 3, 9, 4, 10, 6}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::stable_sort(
					sprout::sub(arr1, 2, 8),
					testspr::mod_less<int, 5>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sorted,
					array<int, 6>{{2, 7, 8, 3, 9, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(sorted),
					array<int, 10>{{5, 1, 2, 7, 8, 3, 9, 4, 10, 6}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_STABLE_SORT_HPP

