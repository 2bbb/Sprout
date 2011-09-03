#ifndef SPROUT_ALGORITHM_FIXED_FILL_N_HPP
#define SPROUT_ALGORITHM_FIXED_FILL_N_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/fill.hpp>

namespace sprout {
	namespace fixed {
		//
		// fill_n
		//
		template<typename Container, typename Size, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type fill_n(
			Container const& cont,
			Size n,
			T const& value
			)
		{
			return sprout::fixed::detail::fill_impl(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<Container>::fixed_size>::type(),
				value,
				sprout::fixed_begin_offset(cont),
				n
				);
		}
	}	// namespace fixed

	using sprout::fixed::fill_n;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_FILL_N_HPP
