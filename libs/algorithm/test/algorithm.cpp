#ifndef SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
#define SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
#	define TESTSPR_CPP_INCLUDE
#endif

#include "./modifying.cpp"

#ifdef TESTSPR_CPP_INCLUDE_DISABLE_SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
#	undef TESTSPR_CPP_INCLUDE
#endif

namespace testspr {
	static void algorithm_test() {
		testspr::algorithm_modifying_test();
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::algorithm_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_ALGORITHM_TEST_ALGORITHM_CPP
