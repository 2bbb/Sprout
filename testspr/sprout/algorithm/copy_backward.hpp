#ifndef TESTSPR_SPROUT_ALGORITHM_COPY_BACKWARD_HPP
#define TESTSPR_SPROUT_ALGORITHM_COPY_BACKWARD_HPP

#include <sprout/algorithm/copy_backward.hpp>
#include <sprout/array.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/fixed_container.hpp>
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
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
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
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
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
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
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
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
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
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(copied),
					array<int, 10>{{0, 0, 3, 4, 5, 6, 7, 8, 0, 0}}
					));
			}
			{
				SPROUT_STATIC_CONSTEXPR auto copied = sprout::fit::copy_backward(
					sprout::begin(arr1) + 2,
					sprout::begin(arr1) + 8,
					sprout::sub(arr2, 2, 8)
					);
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					copied,
					array<int, 6>{{3, 4, 5, 6, 7, 8}}
					));
				TESTSPR_DOUBLE_ASSERT(testspr::equal(
					sprout::get_fixed(copied),
					array<int, 10>{{0, 0, 3, 4, 5, 6, 7, 8, 0, 0}}
					));
			}
		}
	}
}	// namespace testspr

#endif	// #ifndef TESTSPR_SPROUT_ALGORITHM_COPY_BACKWARD_HPP

