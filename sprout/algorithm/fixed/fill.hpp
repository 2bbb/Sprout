#ifndef SPROUT_ALGORITHM_FIXED_FILL_HPP
#define SPROUT_ALGORITHM_FIXED_FILL_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type fill_impl(
				Container const& cont,
				T const& value,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Container>::difference_type offset,
				typename sprout::fixed_container_traits<Container>::size_type size
				)
			{
				return sprout::remake_clone<Container>(
					cont,
					sprout::size(cont),
					(Indexes >= offset && Indexes < offset + size
						? value
						: *sprout::next(sprout::fixed_begin(cont), Indexes)
						)...
					);
			}
		}	// namespace detail
		//
		// fill
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type fill(
			Container const& cont,
			T const& value
			)
		{
			return sprout::fixed::detail::fill_impl(
				cont,
				value,
				typename sprout::index_range<0, sprout::fixed_container_traits<Container>::fixed_size>::type(),
				sprout::fixed_begin_offset(cont),
				sprout::size(cont)
				);
		}
	}	// namespace fixed

	using sprout::fixed::fill;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_FILL_HPP
