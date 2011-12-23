#ifndef TESTSPR_SPROUT_ALGORITHM_REMOVE_IF_HPP
#define TESTSPR_SPROUT_ALGORITHM_REMOVE_IF_HPP

#include <sprout/algorithm/remove_if.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_remove_if_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 0, 3, 0, 5, 0, 7, 0, 9, 0}};

			// �폜 (is_odd)
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_if(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 10>{{0, 0, 0, 0, 0, 0, 7, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_if(
					arr1,
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 5>{{0, 0, 0, 0, 0}}
					));
			}
			// �폜 (is_odd)
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::remove_if(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 6>{{0, 0, 0, 0, 7, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(removed),
					array<int, 10>{{1, 0, 0, 0, 0, 0, 7, 0, 9, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto removed = sprout::fit::remove_if(
					sprout::sub(arr1, 2, 8),
					testspr::is_odd<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					removed,
					array<int, 3>{{0, 0, 0}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(removed),
					array<int, 10>{{1, 0, 0, 0, 0, 0, 7, 0, 9, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REMOVE_IF_HPP

