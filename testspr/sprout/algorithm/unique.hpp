#ifndef TESTSPR_SPROUT_ALGORITHM_UNIQUE_HPP
#define TESTSPR_SPROUT_ALGORITHM_UNIQUE_HPP

#include <sprout/algorithm/unique.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_unique_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 1, 3, 3, 5, 5, 7, 7, 9, 9}};

			// �u�c�c���j�[�N�v
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 10>{{1, 3, 5, 7, 9, 5, 7, 7, 9, 9}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 5>{{1, 3, 5, 7, 9}}
					));
			}
			// �u�c�c���j�[�N�v
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 6>{{3, 5, 7, 5, 7, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(uniqued),
					array<int, 10>{{1, 1, 3, 5, 7, 5, 7, 7, 9, 9}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(uniqued),
					array<int, 10>{{1, 1, 3, 5, 7, 5, 7, 7, 9, 9}}
					));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 1, 3, 3, 5, 5, 7, 7, 9, 9}};

			// �u�c�c���j�[�N�v
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique(
					arr1,
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 10>{{1, 3, 5, 7, 9, 5, 7, 7, 9, 9}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique(
					arr1,
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 5>{{1, 3, 5, 7, 9}}
					));
			}
			// �u�c�c���j�[�N�v
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::unique(
					sprout::sub(arr1, 2, 8),
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 6>{{3, 5, 7, 5, 7, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(uniqued),
					array<int, 10>{{1, 1, 3, 5, 7, 5, 7, 7, 9, 9}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto uniqued = sprout::fit::unique(
					sprout::sub(arr1, 2, 8),
					testspr::equal_to<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					uniqued,
					array<int, 3>{{3, 5, 7}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(uniqued),
					array<int, 10>{{1, 1, 3, 5, 7, 5, 7, 7, 9, 9}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_UNIQUE_HPP

