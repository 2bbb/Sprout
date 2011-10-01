#ifndef SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP
#define SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Iterator, typename Result, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result, Result>(
					result,
					sprout::size(result),
					(Indexes < offset && Indexes + size >= offset && Indexes + input_size >= offset
						? *sprout::next(last, Indexes - offset)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
		}	// namespace detail
		//
		// copy_backward
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type copy_backward(
			Iterator first,
			Iterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::copy_backward_impl(
				first,
				last,
				result,
				typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				sprout::fixed_end_offset(result),
				sprout::size(result),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
				);
		}
	}	// namespace fixed

	using sprout::fixed::copy_backward;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_COPY_BACKWARD_HPP
