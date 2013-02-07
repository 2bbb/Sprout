#ifndef SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP
#define SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/generate.hpp>
#include <sprout/pit/pit.hpp>

namespace sprout {
	namespace fixed {
		//
		// generate_n
		//
		template<typename Container, typename Size, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		generate_n(Container const& cont, Size n, Generator const& gen) {
			return sprout::fixed::detail::generate_impl(cont, gen, n);
		}

		template<typename Container, typename Size, typename Generator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type
		generate_n(Size n, Generator const& gen) {
			return sprout::fixed::generate_n(sprout::pit<Container>(), n, gen);
		}
	}	// namespace fixed

	using sprout::fixed::generate_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_GENERATE_N_HPP
