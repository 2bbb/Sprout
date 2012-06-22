#ifndef SPROUT_SUB_ARRAY_TUPLE_HPP
#define SPROUT_SUB_ARRAY_TUPLE_HPP

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/container.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type&
		get(sprout::sub_array<Container>& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*sprout::next(sprout::internal_begin(t), I)))
		{
			static_assert(I < sprout::container_traits<sprout::sub_array<Container> >::static_size, "get: index out of range");
			return *sprout::next(sprout::internal_begin(t), I);
		}
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type const&
		get(sprout::sub_array<Container> const& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*sprout::next(sprout::internal_begin(t), I)))
		{
			static_assert(I < sprout::container_traits<sprout::sub_array<Container> >::static_size, "get: index out of range");
			return *sprout::next(sprout::internal_begin(t), I);
		}
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type&&
		get(sprout::sub_array<Container>&& t)
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
	struct tuple_size<sprout::sub_array<Container> >
		: public std::tuple_size<typename std::remove_reference<Container>::type>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::sub_array<Container> >
		: public std::tuple_element<I, typename std::remove_reference<Container>::type>
	{};
}	// namespace std

#endif	// #ifndef SPROUT_SUB_ARRAY_TUPLE_HPP
