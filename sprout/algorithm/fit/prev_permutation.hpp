#ifndef SPROUT_ALGORITHM_FIT_PREV_PERMUTATION_HPP
#define SPROUT_ALGORITHM_FIT_PREV_PERMUTATION_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/prev_permutation.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/utility/pair.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Permutation>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::result_of::algorithm<Container>::type, bool>
			prev_permutation_impl_1(
				Container const& cont,
				Permutation const& perm,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::pair<typename sprout::fit::result_of::algorithm<Container>::type, bool>(
					sprout::sub_copy(
						sprout::get_internal(perm.first),
						offset,
						offset + sprout::size(cont)
						),
					perm.second
					);
			}

			template<typename Container, typename Compare>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::result_of::algorithm<Container>::type, bool>
			prev_permutation_impl(
				Container const& cont,
				Compare comp,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return prev_permutation_impl_1(cont, sprout::fixed::prev_permutation(cont, comp), offset);
			}
		}	// namespace detail
		//
		// prev_permutation
		//
		template<typename Container, typename Compare>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::result_of::algorithm<Container>::type, bool>
		prev_permutation(
			Container const& cont,
			Compare comp
			)
		{
			return sprout::fit::detail::prev_permutation_impl(cont, comp, sprout::internal_begin_offset(cont));
		}

		namespace detail {
			template<typename Container>
			inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::result_of::algorithm<Container>::type, bool>
			prev_permutation_impl(
				Container const& cont,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return prev_permutation_impl_1(cont, sprout::fixed::prev_permutation(cont), offset);
			}
		}	// namespace detail
		//
		// prev_permutation
		//
		template<typename Container>
		inline SPROUT_CONSTEXPR sprout::pair<typename sprout::fit::result_of::algorithm<Container>::type, bool>
		prev_permutation(
			Container const& cont
			)
		{
			return sprout::fit::detail::prev_permutation_impl(cont, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_PREV_PERMUTATION_HPP
