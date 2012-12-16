#ifndef SPROUT_LIBS_ALGORITHM_TEST_ONE_OF_EQUAL_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_ONE_OF_EQUAL_CPP

#include <sprout/algorithm/one_of_equal.hpp>
#include <sprout/array.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void algorithm_one_of_equal_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR auto arr1 = array<int, 10>{{1, 2, 3, 4, 5, 5, 5, 5, 5, 10}};

			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::one_of_equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					5
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::one_of_equal(
					sprout::begin(arr1),
					sprout::end(arr1),
					10
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::one_of_equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					5
					);
				TESTSPR_BOTH_ASSERT(result);
			}
			{
				SPROUT_STATIC_CONSTEXPR auto result = sprout::one_of_equal(
					sprout::begin(arr1),
					sprout::begin(arr1) + 5,
					10
					);
				TESTSPR_BOTH_ASSERT(!result);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_one_of_equal_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_ONE_OF_EQUAL_CPP
