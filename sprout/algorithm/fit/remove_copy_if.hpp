#ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy_if.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename Predicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			remove_copy_if_impl(
				InputIterator first, InputIterator last, Result const& result, Predicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove_copy_if(first, last, result, pred)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(
						sprout::distance(first, last) - NS_SSCRISK_CEL_OR_SPROUT::count_if(first, last, pred),
						sprout::size(result)
						)
					);
			}
		}	// namespace detail
		//
		// remove_copy_if
		//
		template<typename InputIterator, typename Result, typename Predicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		remove_copy_if(InputIterator first, InputIterator last, Result const& result, Predicate pred) {
			return sprout::fit::detail::remove_copy_if_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_IF_HPP
