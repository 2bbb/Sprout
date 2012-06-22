#ifndef SPROUT_ARRAY_TYPE_TRAITS_HPP
#define SPROUT_ARRAY_TYPE_TRAITS_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>

namespace sprout {
	//
	// is_array
	//
	template<typename T>
	struct is_array
		: public std::false_type
	{};
	template<typename T>
	struct is_array<T const>
		: public sprout::is_array<T>
	{};
	template<typename T>
	struct is_array<T const volatile>
		: public sprout::is_array<T>
	{};
	template<typename T, std::size_t N>
	struct is_array<sprout::array<T, N> >
		: public std::true_type
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_TYPE_TRAITS_HPP
