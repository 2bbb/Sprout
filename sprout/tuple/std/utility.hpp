#ifndef SPROUT_TUPLE_STD_UTILITY_HPP
#define SPROUT_TUPLE_STD_UTILITY_HPP

#include <cstddef>
#include <type_traits>
#include <array>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, std::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T1& operator()(std::pair<T1, T2>& t) const {
					return t.first;
				}
				SPROUT_CONSTEXPR T1 const& operator()(std::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, std::pair<T1, T2> > {
			public:
			public:
				SPROUT_CONSTEXPR T2& operator()(std::pair<T1, T2>& t) const {
					return t.second;
				}
				SPROUT_CONSTEXPR T2 const& operator()(std::pair<T1, T2> const& t) const {
					return t.second;
				}
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace sprout_adl {
	//
	// tuple_get
	//
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, std::pair<T1, T2> >::type&
	tuple_get(std::pair<T1, T2>& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, std::pair<T1, T2> >()(t);
	}
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, std::pair<T1, T2> >::type const&
	tuple_get(std::pair<T1, T2> const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, std::pair<T1, T2> >()(t);
	}
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, std::pair<T1, T2> >::type&&
	tuple_get(std::pair<T1, T2>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout_adl

#endif	// #ifndef SPROUT_TUPLE_STD_UTILITY_HPP
