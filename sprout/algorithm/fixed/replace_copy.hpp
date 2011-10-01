#ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REPLACE_COPY_HPP

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
			template<typename Iterator, typename Result, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				T const& old_value,
				T const& new_value,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result, Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? *sprout::next(first, Indexes - offset) == old_value ? new_value : *sprout::next(first, Indexes - offset)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
		}	// namespace detail
		//
		// replace_copy
		//
		template<typename Iterator, typename Result, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type replace_copy(
			Iterator first,
			Iterator last,
			Result const& result,
			T const& old_value,
			T const& new_value
			)
		{
			return sprout::fixed::detail::replace_copy_impl(
				first,
				last,
				result,
				typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				old_value,
				new_value,
				sprout::fixed_begin_offset(result),
				sprout::size(result),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
				);
		}
	}	// namespace fixed

	using sprout::fixed::replace_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REPLACE_COPY_HPP
