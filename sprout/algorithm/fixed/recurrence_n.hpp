#ifndef SPROUT_ALGORITHM_FIXED_RECURRENCE_N_HPP
#define SPROUT_ALGORITHM_FIXED_RECURRENCE_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/recurrence.hpp>

namespace sprout {
	namespace fixed {
		//
		// recurrence_n
		//
		template<typename Container, typename Size, typename Generator, typename... Inits>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Container>::type recurrence_n(
			Container const& cont,
			Size n,
			Generator const& gen,
			Inits const&... inits
			)
		{
			return sprout::fixed::detail::recurrence_impl(cont, gen, n, inits...);
		}
	}	// namespace fixed

	using sprout::fixed::recurrence_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_RECURRENCE_N_HPP
