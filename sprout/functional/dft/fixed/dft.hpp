#ifndef SPROUT_FUNCTIONAL_DFT_FIXED_DFT_HPP
#define SPROUT_FUNCTIONAL_DFT_FIXED_DFT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/functional/dft/dft_element.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type dft_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? sprout::detail::dft_element_impl(first, last, Indexes - offset, input_size)
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type dft(
				InputIterator first,
				InputIterator last,
				Result const& result
				)
			{
				return sprout::fixed::detail::dft_impl(
					first,
					last,
					result,
					typename sprout::index_range<0, sprout::container_traits<Result>::static_size>::type(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT::distance(first, last)
					);
			}
		}	// namespace detail
		//
		// dft
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type dft(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::dft(first, last, result);
		}
	}	// namespace fixed

	using sprout::fixed::dft;
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_DFT_FIXED_DFT_HPP
