#ifndef SPROUT_PIT_TUPLE_HPP
#define SPROUT_PIT_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/pit/pit.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::pit<Container> >::value_type&
		get(sprout::pit<Container>& t) SPROUT_NOEXCEPT {
			static_assert(I < sprout::container_traits<sprout::pit<Container> >::static_size, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::pit<Container> >::value_type const&
		get(sprout::pit<Container> const& t) SPROUT_NOEXCEPT {
			static_assert(I < sprout::container_traits<sprout::pit<Container> >::static_size, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::pit<Container> >::value_type&&
		get(sprout::pit<Container>&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::move(sprout::tuples::get<I>(t))))
		{
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename Container>
	struct tuple_size<sprout::pit<Container> >
		: public std::tuple_size<Container>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::pit<Container> >
		: public std::tuple_element<I, Container>
	{};
}	// namespace std

#endif	// #ifndef SPROUT_PIT_TUPLE_HPP
