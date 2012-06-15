#ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_BACKWARD_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_COPY_BACKWARD_CPP

#include <sprout/algorithm/copy_backward.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_copy_backward_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
			SPROUT_STATIC_CONSTEXPR auto arr2 = array<int, 10>{};
			SPROUT_STATIC_CONSTEXPR auto arr3 = array<int, 4>{};

			// [2 .. 8) �͈̔͂��R�s�[
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 10>{{0, 0, 0, 0, 3, 4, 5, 6, 7, 8}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr2
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
			}
			// [2 .. 8) �͈̔͂��R�s�[
			// �o�͔͈͂��I�[�o�[����ꍇ
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{5, 6, 7, 8}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					arr3
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 4>{{5, 6, 7, 8}}
					));
			}
			// [2 .. 8) �͈̔͂��R�s�[
			// �o�͔͈͂̐؂�o��
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 3, 4, 5, 6, 7, 8, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_BOTH_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
				TESTSPR_BOTH_ASSERT(testspr::equal(
					sprout::get_internal(copied),
					array<int, 10>{{0, 0, 3, 4, 5, 6, 7, 8, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_copy_backward_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_COPY_BACKWARD_CPP
