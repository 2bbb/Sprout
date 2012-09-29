#ifndef SPROUT_ALGORITHM_FIXED_ROTATE_COPY_HPP
#define SPROUT_ALGORITHM_FIXED_ROTATE_COPY_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			rotate_copy_impl_ra(
				RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last,
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
						? (Indexes < offset + NS_SSCRISK_CEL_OR_SPROUT::distance(middle, last)
							? middle[Indexes - offset]
							: first[(Indexes - offset) - NS_SSCRISK_CEL_OR_SPROUT::distance(first, middle)]
							)
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			rotate_copy(
				RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last,
				Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::rotate_copy_impl_ra(
					first,
					middle,
					last,
					result,
					sprout::index_range<0, sprout::container_traits<Result>::static_size>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT::distance(first, last)
					);
			}
			template<typename ForwardIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			rotate_copy_impl_1(
				ForwardIterator first, ForwardIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename ForwardIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			rotate_copy_impl_1(
				ForwardIterator first, ForwardIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::rotate_copy_impl_1(sprout::next(first), last, result, size, args..., *first)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename ForwardIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			rotate_copy_impl(
				ForwardIterator first, ForwardIterator middle,
				ForwardIterator middle_first, ForwardIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename ForwardIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			rotate_copy_impl(
				ForwardIterator first, ForwardIterator middle,
				ForwardIterator middle_first, ForwardIterator last,
				Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return middle_first != last && sizeof...(Args) < size
					? sprout::fixed::detail::rotate_copy_impl(first, middle, sprout::next(middle_first), last, result, size, args..., *middle_first)
					: sprout::fixed::detail::rotate_copy_impl_1(first, middle, result, size, args...)
					;
			}
			template<typename ForwardIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			rotate_copy(
				ForwardIterator first, ForwardIterator middle, ForwardIterator last, Result const& result,
				void*
				)
			{
				return sprout::fixed::detail::rotate_copy_impl(first, middle, last, result, sprout::size(result));
			}
		}	// namespace detail
		//
		// rotate_copy
		//
		template<typename ForwardIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Result const& result) {
			typedef typename std::iterator_traits<ForwardIterator>::iterator_category* category;
			return sprout::fixed::detail::rotate_copy(first, middle, last, result, category());
		}
	}	// namespace fixed

	using sprout::fixed::rotate_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_ROTATE_COPY_HPP
