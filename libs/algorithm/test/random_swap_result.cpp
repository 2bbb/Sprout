#ifndef SPROUT_LIBS_ALGORITHM_TEST_RANDOM_SWAP_RESULT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_RANDOM_SWAP_RESULT_CPP

#include <sprout/algorithm/random_swap_result.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_random_swap_result_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto g = sprout::random::default_random_engine(SPROUT_UNIQUE_SEED);

			// �����_���X���b�v
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::random_swap_result(
					arr1,
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(random_swapped),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto random_swapped2 = sprout::random_swap_result(
					sprout::get<0>(random_swapped),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(random_swapped) == sprout::get<1>(random_swapped2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::fit::random_swap_result(
					arr1,
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(random_swapped),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto random_swapped2 = sprout::random_swap_result(
					sprout::get<0>(random_swapped),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(random_swapped) == sprout::get<1>(random_swapped2));
			}
			// �����_���X���b�v
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::random_swap_result(
					sprout::sub(arr1, 2, 8),
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(random_swapped),
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get_internal(sprout::get<0>(random_swapped)),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto random_swapped2 = sprout::random_swap_result(
					sprout::get<0>(random_swapped),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(random_swapped) == sprout::get<1>(random_swapped2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto random_swapped = sprout::fit::random_swap_result(
					sprout::sub(arr1, 2, 8),
					g
					);
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get<0>(random_swapped),
					sprout::sub(arr1, 2, 8)
					));
				TESTSPR_BOTH_ASSERT(testspr::is_permutation(
					sprout::get_internal(sprout::get<0>(random_swapped)),
					arr1
					));
				SPROUT_STATIC_CONSTEXPR auto random_swapped2 = sprout::random_swap_result(
					sprout::get<0>(random_swapped),
					g
					);
				TESTSPR_BOTH_ASSERT(sprout::get<1>(random_swapped) == sprout::get<1>(random_swapped2));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_random_swap_result_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_RANDOM_SWAP_RESULT_CPP
