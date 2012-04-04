#ifndef SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP
#define SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/algorithm/fixed/unique_copy.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array.hpp>
#include <sprout/detail/overlap_count.hpp>
#include HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type unique_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unique_copy(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - sprout::detail::overlap_count(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type unique_copy(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fit::detail::unique_copy_impl(first, last, result, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryPredicate>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type unique_copy_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				BinaryPredicate pred,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::unique_copy(first, last, result, pred)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - sprout::detail::overlap_count(first, last, pred), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// unique_copy
		//
		template<typename InputIterator, typename Result, typename BinaryPredicate>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type unique_copy(
			InputIterator first,
			InputIterator last,
			Result const& result,
			BinaryPredicate pred
			)
		{
			return sprout::fit::detail::unique_copy_impl(first, last, result, pred, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIT_UNIQUE_COPY_HPP
