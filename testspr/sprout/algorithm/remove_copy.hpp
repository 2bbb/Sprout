#ifndef TESTSPR_SPROUT_ALGORITHM_REMOVE_COPY_HPP
#define TESTSPR_SPROUT_ALGORITHM_REMOVE_COPY_HPP

#include <sprout/algorithm/remove_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_remove_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 2>{};

			// [2 .. 8) �͈̔͂��폜 (0)
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 10>{{3, 5, 7, 0, 0, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{3, 5, 7}}
					));
			}
			// [2 .. 8) �͈̔͂��폜 (0)
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 2>{{3, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 2>{{3, 5}}
					));
			}
			// [2 .. 8) �͈̔͂��폜 (0)
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 6>{{3, 5, 7, 0, 0, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					0
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(removed),
					array<int, 10>{{0, 0, 3, 5, 7, 0, 0, 0, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REMOVE_COPY_HPP

