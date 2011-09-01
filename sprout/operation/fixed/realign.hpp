#ifndef SPROUT_OPERATION_FIXED_REALIGN_HPP
#define SPROUT_OPERATION_FIXED_REALIGN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>

namespace sprout {
	namespace fixed {
		namespace result_of {
			//
			// realign
			//
			template<typename Container>
			struct realign {
			public:
				typedef typename sprout::fixed_container_traits<Container>::fixed_container_type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Container, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result realign_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type size,
				T const& v
				)
			{
				return Result{
					(Indexes < size
						? *(sprout::begin(cont) + Indexes)
						: v
						)...
					};
			}
		}	// namespace detail
		//
		// realign
		//
		template<typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::realign<Container>::type realign(
			Container const& cont,
			T const& v
			)
		{
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::result_of::realign<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::realign<Container>::type>::fixed_size>::type(),
				sprout::size(cont),
				v
				);
		}

		namespace detail {
			template<typename Result, typename Container, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result realign_impl(
				Container const& cont,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type size
				)
			{
				return Result{
					(Indexes < size
						? *(sprout::begin(cont) + Indexes)
						: typename sprout::fixed_container_traits<Result>::value_type{}
						)...
					};
			}
		}	// namespace detail
		//
		// realign
		//
		template<typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::realign<Container>::type realign(
			Container const& cont
			)
		{
			return sprout::fixed::detail::realign_impl<typename sprout::fixed::result_of::realign<Container>::type>(
				cont,
				typename sprout::index_range<0, sprout::fixed_container_traits<typename sprout::fixed::result_of::realign<Container>::type>::fixed_size>::type(),
				sprout::size(cont)
				);
		}
	}	// namespace fixed
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIXED_REALIGN_HPP
