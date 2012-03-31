#ifndef SPROUT_ALGORITHM_FIXED_BOGO_SORT_HPP
#define SPROUT_ALGORITHM_FIXED_BOGO_SORT_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/shuffle.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Container, typename Shuffled, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type bogo_sort_impl_1(
				Shuffled const& shuffled,
				Compare comp
				)
			{
				return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::is_sorted(
					sprout::begin(sprout::tuples::get<0>(shuffled)),
					sprout::end(sprout::tuples::get<0>(shuffled)),
					comp
					)
					? sprout::tuples::get<0>(shuffled)
					: sprout::fixed::detail::bogo_sort_impl_1<Container>(
						sprout::fixed::shuffle_result(
							sprout::tuples::get<0>(shuffled),
							sprout::tuples::get<1>(shuffled)
							),
						comp
						)
					;
			}
			template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type bogo_sort_impl(
				Container const& cont,
				UniformRandomNumberGenerator&& g,
				Compare comp
				)
			{
				return NS_SSCRISK_CEL_OR_SPROUT_DETAIL::is_sorted(
					sprout::begin(cont),
					sprout::end(cont),
					comp
					)
					? sprout::deep_copy(cont)
					: sprout::fixed::detail::bogo_sort_impl_1<Container>(
						sprout::fixed::shuffle_result(
							cont,
							sprout::forward<UniformRandomNumberGenerator>(g)
							),
						comp
						)
					;
			}
		}	// namespace detail
		//
		// bogo_sort
		//
		template<typename Container, typename UniformRandomNumberGenerator, typename Compare>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type bogo_sort(
			Container const& cont,
			UniformRandomNumberGenerator&& g,
			Compare comp
			)
		{
			return sprout::fixed::detail::bogo_sort_impl(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				comp
				);
		}
		//
		// bogo_sort
		//
		template<typename Container, typename UniformRandomNumberGenerator>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type bogo_sort(
			Container const& cont,
			UniformRandomNumberGenerator&& g
			)
		{
			return sprout::fixed::detail::bogo_sort_impl(
				cont,
				sprout::forward<UniformRandomNumberGenerator>(g),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::less<typename sprout::container_traits<Container>::value_type>()
				);
		}
	}	// namespace fixed

	using sprout::fixed::bogo_sort;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_BOGO_SORT_HPP
