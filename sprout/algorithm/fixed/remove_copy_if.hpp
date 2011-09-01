#ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP
#define SPROUT_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type remove_copy_if_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Result, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type remove_copy_if_impl_3(
				Result const& result,
				Args const&... args
				)
			{
				return remove_copy_if_impl_3(result, args..., *(sprout::fixed_begin(result) + sizeof...(Args)));
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type remove_copy_if_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type remove_copy_if_impl_2(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < offset
					? pred(*first)
						? remove_copy_if_impl_2(first + 1, last, result, pred, offset, args...)
						: remove_copy_if_impl_2(first + 1, last, result, pred, offset, args..., *first)
					: remove_copy_if_impl_3(result, args...)
					;
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type remove_copy_if_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return typename sprout::fixed_container_traits<Result>::fixed_container_type{args...};
			}
			template<typename Iterator, typename Result, typename Predicate, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
				typename sprout::fixed_container_traits<Result>::fixed_container_type
			>::type remove_copy_if_impl_1(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				Args const&... args
				)
			{
				return sizeof...(Args) < offset
					? remove_copy_if_impl_1(first, last, result, pred, offset, args..., *(sprout::fixed_begin(result) + sizeof...(Args)))
					: remove_copy_if_impl_2(first, last, result, pred, offset + sprout::size(result), args...)
					;
			}
			template<typename Iterator, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type remove_copy_if_impl(
				Iterator first,
				Iterator last,
				Result const& result,
				Predicate pred
				)
			{
				return remove_copy_if_impl_1(first, last, result, pred, sprout::fixed_begin_offset(result));
			}
		}	// namespace detail
		//
		// remove_copy_if
		//
		template<typename Iterator, typename Result, typename Predicate>
		SPROUT_CONSTEXPR inline typename sprout::fixed_container_traits<Result>::fixed_container_type remove_copy_if(
			Iterator first,
			Iterator last,
			Result const& result,
			Predicate pred
			)
		{
			return sprout::fixed::detail::remove_copy_if_impl(first, last, result, pred);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_REMOVE_COPY_IF_HPP
