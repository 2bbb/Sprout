#ifndef SPROUT_ALGORITHM_FIXED_REVERSE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_REVERSE_COPY_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Iterator, typename Result, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type reverse_copy_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? *(last - 1 - Indexes + offset)
						: *(sprout::fixed_begin(result) + Indexes)
						)...
					};
			}
		}	// namespace detail
		//
		// reverse_copy
		//
		template<typename Iterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type reverse_copy(
			Iterator first,
			Iterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::reverse_copy_impl(
				first,
				last,
				result, typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
				sprout::fixed_begin_offset(result),
				sprout::size(result),
				NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REVERSE_COPY_HPP
