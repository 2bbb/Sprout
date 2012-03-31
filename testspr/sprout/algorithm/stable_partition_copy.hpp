#ifndef TESTSPR_SPROUT_ALGORITHM_STABLE_PARTITION_COPY_HPP
#define TESTSPR_SPROUT_ALGORITHM_STABLE_PARTITION_COPY_HPP

#include <sprout/algorithm/stable_partition_copy.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_stable_partition_copy_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) �͈̔͂��p�[�e�B�V���� (is_odd)
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::stable_partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 10>{{3, 5, 7, 4, 6, 8, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::stable_partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{3, 5, 7}}
					));
			}
			// [2 .. 8) �͈̔͂��p�[�e�B�V���� (is_odd)
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::stable_partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 4>{{3, 5, 7, 4}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::stable_partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{3, 5, 7}}
					));
			}
			// [2 .. 8) �͈̔͂��p�[�e�B�V���� (is_odd)
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::stable_partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 6>{{3, 5, 7, 4, 6, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(partitioned),
					array<int, 10>{{0, 0, 3, 5, 7, 4, 6, 8, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto partitioned = sprout::fit::stable_partition_copy(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					partitioned,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(partitioned),
					array<int, 10>{{0, 0, 3, 5, 7, 4, 6, 8, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_STABLE_PARTITION_COPY_HPP

