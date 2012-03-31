#ifndef TESTSPR_SPROUT_ALGORITHM_REBERSE_HPP
#define TESTSPR_SPROUT_ALGORITHM_REBERSE_HPP

#include <sprout/algorithm/reverse.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_reverse_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// ���]
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					reversed,
					array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse(
					arr1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					reversed,
					array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}}
					));
			}
			// ���]
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::reverse(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(reversed),
					array<int, 10>{{1, 2, 8, 7, 6, 5, 4, 3, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto reversed = sprout::fit::reverse(
					sprout::sub(arr1, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					reversed,
					array<int, 6>{{8, 7, 6, 5, 4, 3}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(reversed),
					array<int, 10>{{1, 2, 8, 7, 6, 5, 4, 3, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_REBERSE_HPP

