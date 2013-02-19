#ifndef SPROUT_NUMERIC_FIT_PARTIAL_SUM_HPP
#define SPROUT_NUMERIC_FIT_PARTIAL_SUM_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/fixed/partial_sum.hpp>
#include <sprout/algorithm/fit/result_of.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT
#include <sprout/iterator/type_traits/is_iterator.hpp>

namespace sprout {
	namespace fit {
		namespace detail {
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partial_sum_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::partial_sum(first, last, result)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// partial_sum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		partial_sum(InputIterator first, InputIterator last, Result const& result) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::partial_sum_impl(first, last, result, sprout::internal_begin_offset(result));
		}

		namespace detail {
			template<typename InputIterator, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
			partial_sum_impl(
				InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op,
				typename sprout::container_traits<Result>::difference_type offset
				)
			{
				return sprout::sub_copy(
					sprout::get_internal(sprout::fixed::partial_sum(first, last, result, binary_op)),
					offset,
					offset + NS_SSCRISK_CEL_OR_SPROUT::min(sprout::distance(first, last), sprout::size(result))
					);
			}
		}	// namespace detail
		//
		// partial_sum
		//
		template<typename InputIterator, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::algorithm<Result>::type
		partial_sum(InputIterator first, InputIterator last, Result const& result, BinaryOperation binary_op) {
			static_assert(sprout::is_forward_iterator<InputIterator>::value, "Sorry, not implemented.");
			return sprout::fit::detail::partial_sum_impl(first, last, result, binary_op, sprout::internal_begin_offset(result));
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FIT_PARTIAL_SUM_HPP
