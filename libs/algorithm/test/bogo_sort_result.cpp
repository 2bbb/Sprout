#ifndef SPROUT_LIBS_ALGORITHM_TEST_BOGO_SORT_RESULT_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_BOGO_SORT_RESULT_CPP

#include <sprout/algorithm/bogo_sort_result.hpp>
#include <sprout/random.hpp>
#include <sprout/random/unique_seed.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_bogo_sort_result_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};
			SPROUT_STATIC_CONSTEXPR auto g = sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED);

			// �\�[�g
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort_result(
					arr1,
					g
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort_result(
					arr1,
					g
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			// �\�[�g
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort_result(
					sprout::sub(arr1, 1, 4),
					g
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort_result(
					sprout::sub(arr1, 1, 4),
					g
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
		}
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 5>{{5, 1, 4, 2, 3}};
			SPROUT_STATIC_CONSTEXPR auto g = sprout::random::hellekalek1995(SPROUT_UNIQUE_SEED);

			// �\�[�g
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort_result(
					arr1,
					g,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort_result(
					arr1,
					g,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 5>{{1, 2, 3, 4, 5}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			// �\�[�g
			// �͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::bogo_sort_result(
					sprout::sub(arr1, 1, 4),
					g,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto sorted = sprout::fit::bogo_sort_result(
					sprout::sub(arr1, 1, 4),
					g,
					testspr::less<int>()
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get<0>(sorted),
					array<int, 3>{{1, 2, 4}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_internal(sprout::get<0>(sorted)),
					array<int, 5>{{5, 1, 2, 4, 3}}
					));
				SPROUT_STATIC_CONSTEXPR auto sorted2 = sprout::bogo_sort_result(
					sprout::get<0>(sorted),
					sprout::get<1>(sorted)
					);
				TESTSPR_DOUBLE_ASSERT(sprout::get<1>(sorted) == sprout::get<1>(sorted2));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_bogo_sort_result_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_BOGO_SORT_RESULT_CPP

