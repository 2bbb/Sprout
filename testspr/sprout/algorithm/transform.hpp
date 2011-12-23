#ifndef TESTSPR_SPROUT_ALGORITHM_TRANSFORM_HPP
#define TESTSPR_SPROUT_ALGORITHM_TRANSFORM_HPP

#include <sprout/algorithm/transform.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_transform_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) �͈̔͂�ϊ�
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					testspr::x2<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 10>{{6, 8, 10, 12, 14, 16, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::fit::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2,
					testspr::x2<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 6>{{6, 8, 10, 12, 14, 16}}
					));
			}
			// [2 .. 8) �͈̔͂�ϊ�
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					testspr::x2<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 4>{{6, 8, 10, 12}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::fit::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3,
					testspr::x2<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 4>{{6, 8, 10, 12}}
					));
			}
			// [2 .. 8) �͈̔͂�ϊ�
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					testspr::x2<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 6>{{6, 8, 10, 12, 14, 16}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(transformed),
					array<int, 10>{{0, 0, 6, 8, 10, 12, 14, 16, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::fit::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8),
					testspr::x2<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 6>{{6, 8, 10, 12, 14, 16}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(transformed),
					array<int, 10>{{0, 0, 6, 8, 10, 12, 14, 16, 0, 0}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr1_2 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) �͈̔͂�ϊ�
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::begin(arr1_2) + 2,
					arr2,
					testspr::plus<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 10>{{6, 8, 10, 12, 14, 16, 0, 0, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::fit::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::begin(arr1_2) + 2,
					arr2,
					testspr::plus<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 6>{{6, 8, 10, 12, 14, 16}}
					));
			}
			// [2 .. 8) �͈̔͂�ϊ�
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::begin(arr1_2) + 2,
					arr3,
					testspr::plus<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 4>{{6, 8, 10, 12}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::fit::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::begin(arr1_2) + 2,
					arr3,
					testspr::plus<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 4>{{6, 8, 10, 12}}
					));
			}
			// [2 .. 8) �͈̔͂�ϊ�
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::begin(arr1_2) + 2,
					sprout::sub(arr2, 2, 8),
					testspr::plus<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 6>{{6, 8, 10, 12, 14, 16}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(transformed),
					array<int, 10>{{0, 0, 6, 8, 10, 12, 14, 16, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto transformed = sprout::fit::transform(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::begin(arr1_2) + 2,
					sprout::sub(arr2, 2, 8),
					testspr::plus<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					transformed,
					array<int, 6>{{6, 8, 10, 12, 14, 16}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(transformed),
					array<int, 10>{{0, 0, 6, 8, 10, 12, 14, 16, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_TRANSFORM_HPP

