#ifndef SPROUT_ALGORITHM_FIT_REMOVE_IF_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/remove_if.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename Container, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
			remove_if_impl(
				Container const& cont, Predicate pred,
				typename sprout::container_traits<Container>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove_if(cont, pred)),
					offset,
					offset + sprout::size(cont) - NS_SSCRISK_CEL_OR_SPROUT::count_if(sprout::begin(cont), sprout::end(cont), pred)
					);
			}
		}	// namespace detail
		//
		// remove_if
		//
		template<typename Container, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Container>::type
		remove_if(Container const& cont, Predicate pred) {
			return sprout::fit::detail::remove_if_impl(cont, pred, sprout::internal_begin_offset(cont));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_IF_HPP
