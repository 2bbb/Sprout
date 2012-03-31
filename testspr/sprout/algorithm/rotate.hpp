#ifndef TESTSPR_SPROUT_ALGORITHM_ROTATE_HPP
#define TESTSPR_SPROUT_ALGORITHM_ROTATE_HPP

#include <sprout/algorithm/rotate.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_rotate_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// ��]
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::rotate(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 10>{{6, 7, 8, 9, 10, 1, 2, 3, 4, 5}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::fit::rotate(
					arr1,
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 10>{{6, 7, 8, 9, 10, 1, 2, 3, 4, 5}}
					));
			}
			// ��]
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::rotate(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 6>{{6, 7, 8, 3, 4, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(rotated),
					array<int, 10>{{1, 2, 6, 7, 8, 3, 4, 5, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto rotated = sprout::fit::rotate(
					sprout::sub(arr1, 2, 8),
					sprout::begin(arr1) + 5
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					rotated,
					array<int, 6>{{6, 7, 8, 3, 4, 5}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(rotated),
					array<int, 10>{{1, 2, 6, 7, 8, 3, 4, 5, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_ROTATE_HPP

