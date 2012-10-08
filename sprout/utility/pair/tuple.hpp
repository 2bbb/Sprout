#ifndef SPROUT_UTILITY_PAIR_TUPLE_HPP
#define SPROUT_UTILITY_PAIR_TUPLE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<typename T1, typename T2>
			struct tuple_element_impl<0, sprout::pair<T1, T2> > {
			public:
				typedef T1 type;
			};
			template<typename T1, typename T2>
			struct tuple_element_impl<1, sprout::pair<T1, T2> > {
			public:
				typedef T2 type;
			};

			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, sprout::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T1& operator()(sprout::pair<T1, T2>& t) const {
					return t.first;
				}
				SPROUT_CONSTEXPR T1 const& operator()(sprout::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, sprout::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T2& operator()(sprout::pair<T1, T2>& t) const {
					return t.second;
				}
				SPROUT_CONSTEXPR T2 const& operator()(sprout::pair<T1, T2> const& t) const {
					return t.second;
				}
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T1, typename T2>
	struct tuple_size<sprout::pair<T1, T2> >
		: public std::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T1, typename T2>
	struct tuple_element<I, sprout::pair<T1, T2> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::pair<T1, T2> >
	{};
}	// namespace std

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type&
	tuple_get(sprout::pair<T1, T2>& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::pair<T1, T2> >()(t);
	}
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type const&
	tuple_get(sprout::pair<T1, T2> const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::pair<T1, T2> >()(t);
	}
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type&&
	tuple_get(sprout::pair<T1, T2>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_TUPLE_HPP
