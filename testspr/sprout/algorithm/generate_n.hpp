#ifndef TESTSPR_SPROUT_ALGORITHM_GENERATE_N_HPP
#define TESTSPR_SPROUT_ALGORITHM_GENERATE_N_HPP

#include <sprout/algorithm/generate_n.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_generate_n_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

			// ����
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate_n(
					arr1,
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 10>{{1, 2, 4, 8, 5, 6, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate_n(
					arr1,
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 4>{{1, 2, 4, 8}}
					));
			}
			// ����
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::generate_n(
					sprout::sub(arr1, 2, 8),
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 6>{{1, 2, 4, 8, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(generated),
					array<int, 10>{{1, 2, 1, 2, 4, 8, 7, 8, 9, 10}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto generated = sprout::fit::generate_n(
					sprout::sub(arr1, 2, 8),
					4,
					testspr::x2<int>(),
					1
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					generated,
					array<int, 4>{{1, 2, 4, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(generated),
					array<int, 10>{{1, 2, 1, 2, 4, 8, 7, 8, 9, 10}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_GENERATE_N_HPP

