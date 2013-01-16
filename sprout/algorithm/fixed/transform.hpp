#ifndef SPROUT_ALGORITHM_FIXED_TRANSFORM_HPP
#define SPROUT_ALGORITHM_FIXED_TRANSFORM_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/pit.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, typename UnaryOperation, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform_impl_ra(
				RandomAccessIterator first, RandomAccessIterator last,
				Result const& result, UnaryOperation op,
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
						? op(first[Indexes - offset])
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform(
				RandomAccessIterator first, RandomAccessIterator last,
				Result const& result, UnaryOperation op,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::transform_impl_ra(
					first, last,
					result, op,
					sprout::index_range<0, sprout::container_traits<Result>::static_size>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}

			template<typename InputIterator, typename Result, typename UnaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform_impl(
				InputIterator first, InputIterator last,
				Result const& result, UnaryOperation op,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename UnaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform_impl(
				InputIterator first, InputIterator last,
				Result const& result, UnaryOperation op,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::transform_impl(sprout::next(first), last, result, op, size, args..., op(*first))
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform(
				InputIterator first, InputIterator last,
				Result const& result, UnaryOperation op,
				void*
				)
			{
				return sprout::fixed::detail::transform_impl(first, last, result, op, sprout::size(result));
			}

			template<typename InputIterator, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform(InputIterator first, InputIterator last, Result const& result, UnaryOperation op) {
				typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
				return sprout::fixed::detail::transform(first, last, result, op, category());
			}

			template<typename InputIterator, typename Result, typename UnaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform(InputIterator first, InputIterator last, Result const& result, UnaryOperation op) {
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					sprout::make_transform_iterator(first, op), sprout::make_transform_iterator(last, op)
					);
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename InputIterator, typename Result, typename UnaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		transform(InputIterator first, InputIterator last, Result const& result, UnaryOperation op) {
			return sprout::fixed::detail::transform(first, last, result, op);
		}

		template<typename Result, typename InputIterator, typename UnaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		transform(InputIterator first, InputIterator last, UnaryOperation op) {
			return sprout::fixed::transform(first, last, sprout::pit<Result>(), op);
		}

		namespace detail {
			template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Result, typename BinaryOperation, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform_impl_ra(
				RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2,
				Result const& result, BinaryOperation op,
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
						? op(first1[Indexes - offset], first2[Indexes - offset])
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform(
				RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2,
				Result const& result, BinaryOperation op,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::transform_impl_ra(
					first1, last1, first2,
					result, op,
					sprout::index_range<0, sprout::container_traits<Result>::static_size>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first1, last1)
				);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform_impl(
				InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				Result const& result, BinaryOperation op,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform_impl(
				InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				Result const& result, BinaryOperation op,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first1 != last1 && sizeof...(Args) < size
					? sprout::fixed::detail::transform_impl(sprout::next(first1), last1, sprout::next(first2), result, op, size, args..., op(*first1, *first2))
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			transform(
				InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
				Result const& result, BinaryOperation op,
				void*
				)
			{
				return sprout::fixed::detail::transform_impl(first1, last1, first2, result, op, sprout::size(result));
			}

			template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Result const& result, BinaryOperation op) {
				typedef typename sprout::common_iterator_category<InputIterator1, InputIterator2>::type* category;
				return sprout::fixed::detail::transform(first1, last1, first2, result, op, category());
			}

			template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::result_of::algorithm<Result>::type
			>::type
			transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Result const& result, BinaryOperation op) {
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					sprout::make_transform_iterator(first1, first2, op),
					sprout::make_transform_iterator(last1, first2, op)
					);
			}
		}	// namespace detail
		//
		// transform
		//
		template<typename InputIterator1, typename InputIterator2, typename Result, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, Result const& result, BinaryOperation op) {
			return sprout::fixed::detail::transform(first1, last1, first2, result, op);
		}

		template<typename Result, typename InputIterator1, typename InputIterator2, typename BinaryOperation>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryOperation op) {
			return sprout::fixed::transform(first1, last1, first2, sprout::pit<Result>(), op);
		}
	}	// namespace fixed

	using sprout::fixed::transform;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_TRANSFORM_HPP
