#ifndef SPROUT_ALGORITHM_FIT_GENERATE_HPP
#define SPROUT_ALGORITHM_FIT_GENERATE_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/fixed/generate.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type generate_impl(
				Container const& cont,
				Generator gen,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				Inits const&... inits
				)
			{
				return sprout::sub_copy(
					sprout::get_fixed(sprout::fixed::generate(cont, gen, inits...)),
					offset,
					offset + sprout::size(cont)
					);
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::algorithm<Container>::type generate(
			Container const& cont,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::fit::detail::generate_impl(cont, gen, sprout::fixed_begin_offset(cont), inits...);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_GENERATE_HPP
