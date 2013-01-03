#ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/remove_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/operation.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result, typename T>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			remove_copy_impl(
				InputIterator first, InputIterator last, Result const& result, T const& value,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::remove_copy(first, last, result, value)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(
						sprout::distance(first, last) - NS_SSCRISK_CEL_OR_SPROUT::count(first, last, value),
						sprout::size(result)
						)
					);
			}
		}	// namespace detail
		//
		// remove_copy
		//
		template<typename InputIterator, typename Result, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		remove_copy(InputIterator first, InputIterator last, Result const& result, T const& value) {
			return sprout::fit::detail::remove_copy_impl(first, last, result, value, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_REMOVE_COPY_HPP
