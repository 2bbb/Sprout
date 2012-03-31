#ifndef SPROUT_ALGORITHM_FIXED_GENERATE_HPP
#define SPROUT_ALGORITHM_FIXED_GENERATE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				InitSize == 0,
				typename sprout::container_traits<Container>::value_type
			>::type call_gen(
				Generator gen,
				Args const&... args
				)
			{
				return gen();
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				InitSize != 0 && InitSize == sizeof...(Args) + 1,
				typename sprout::container_traits<Container>::value_type
			>::type call_gen(
				Generator gen,
				Head const& head,
				Args const&... args
				)
			{
				return gen(head, args...);
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename Head, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				InitSize != 0 && InitSize != sizeof...(Args) + 1,
				typename sprout::container_traits<Container>::value_type
			>::type call_gen(
				Generator gen,
				Head const& head,
				Args const&... args
				)
			{
				return call_gen<InitSize, Container>(gen, args...);
			}
			template<typename Container, typename Generator>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type generate_impl_drop(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size
				)
			{
				return sprout::detail::container_complate(cont);
			}
			template<typename Container, typename Generator, typename Head, typename... Inits>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::container_traits<Container>::static_size >= sizeof...(Inits) + 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_drop(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size,
				Head const& head,
				Inits const&... inits
				)
			{
				return size < sizeof...(Inits) + 1
					? sprout::fixed::detail::generate_impl_drop(cont, gen, size, inits...)
					: sprout::detail::container_complate(cont, head, inits...)
					;
			}
			template<typename Container, typename Generator, typename Head, typename... Inits>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::container_traits<Container>::static_size < sizeof...(Inits) + 1),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_drop(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size,
				Head const& head,
				Inits const&... inits
				)
			{
				return sprout::fixed::detail::generate_impl_drop(cont, gen, size, inits...);
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Container>::static_size == sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_1(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size,
				Args const&... args
				)
			{
				return sprout::remake<Container>(cont, sprout::size(cont), args...);
			}
			template<std::size_t InitSize, typename Container, typename Generator, typename... Args>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::container_traits<Container>::static_size != sizeof...(Args),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl_1(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size,
				Args const&... args
				)
			{
				return sizeof...(Args) < size
					? sprout::fixed::detail::generate_impl_1<InitSize>(cont, gen, size, args..., sprout::fixed::detail::call_gen<InitSize, Container>(gen, args...))
					: sprout::detail::container_complate(cont, args...)
					;
			}
			template<typename Container, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::container_traits<Container>::static_size > sizeof...(Inits)),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size,
				Inits const&... inits
				)
			{
				return sizeof...(Inits) < size
					? sprout::fixed::detail::generate_impl_1<sizeof...(Inits)>(cont, gen, size, inits...)
					: sprout::fixed::detail::generate_impl_drop(cont, gen, size, inits...)
					;
			}
			template<typename Container, typename Generator, typename... Inits>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				(sprout::container_traits<Container>::static_size <= sizeof...(Inits)),
				typename sprout::fixed::result_of::algorithm<Container>::type
			>::type generate_impl(
				Container const& cont,
				Generator gen,
				typename sprout::container_traits<Container>::size_type size,
				Inits const&... inits
				)
			{
				return sprout::fixed::detail::generate_impl_drop(cont, gen, size, inits...);
			}
		}	// namespace detail
		//
		// generate
		//
		template<typename Container, typename Generator, typename... Inits>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Container>::type generate(
			Container const& cont,
			Generator gen,
			Inits const&... inits
			)
		{
			return sprout::fixed::detail::generate_impl(cont, gen, sprout::size(cont), inits...);
		}
	}	// namespace fixed

	using sprout::fixed::generate;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_FIXED_GENERATE_HPP
