#ifndef TESTSPR_SPROUT_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP
#define TESTSPR_SPROUT_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP

#include <sprout/algorithm/set_symmetric_difference.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_set_symmetric_difference_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 10, 15, 20, 25}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 5>{{10, 20, 30, 40, 50}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// �r���I�_���a
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{5, 15, 25, 30, 40, 50, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 15, 25, 30, 40, 50}}
					));
			}
			// �r���I�_���a
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 15, 25, 30}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 15, 25, 30}}
					));
			}
			// �r���I�_���a
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 15, 25, 30, 40, 50}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{0, 0, 5, 15, 25, 30, 40, 50, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 15, 25, 30, 40, 50}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{0, 0, 5, 15, 25, 30, 40, 50, 0, 0}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 10, 15, 20, 25}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 5>{{10, 20, 30, 40, 50}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// �r���I�_���a
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 10>{{5, 15, 25, 30, 40, 50, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr2,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 15, 25, 30, 40, 50}}
					));
			}
			// �r���I�_���a
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 15, 25, 30}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					arr3,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 4>{{5, 15, 25, 30}}
					));
			}
			// �r���I�_���a
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 15, 25, 30, 40, 50}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{0, 0, 5, 15, 25, 30, 40, 50, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto merged = sprout::fit::set_symmetric_difference(
					sprout::begin(arr1),
					sprout::end(arr1),
					sprout::begin(arr1_2),
					sprout::end(arr1_2),
					sprout::sub(arr2, 2, 8),
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					merged,
					array<int, 6>{{5, 15, 25, 30, 40, 50}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(merged),
					array<int, 10>{{0, 0, 5, 15, 25, 30, 40, 50, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP

