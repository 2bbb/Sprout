#ifndef SPROUT_ARRAY_TUPLE_HPP
#define SPROUT_ARRAY_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR T&
	tuple_get(sprout::array<T, N>& t) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR T const&
	tuple_get(sprout::array<T, N> const& t) SPROUT_NOEXCEPT {
		static_assert(I < N, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I, typename T, std::size_t N>
	inline SPROUT_CONSTEXPR T&&
	tuple_get(sprout::array<T, N>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T, std::size_t N>
	struct tuple_size<sprout::array<T, N> >
		: public std::integral_constant<std::size_t, N>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N>
	struct tuple_element<I, sprout::array<T, N> > {
	public:
		static_assert(I < N, "tuple_element<>: index out of range");
		typedef T type;
	};
}	// namespace std

#endif	// #ifndef SPROUT_ARRAY_TUPLE_HPP
