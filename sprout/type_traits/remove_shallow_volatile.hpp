#ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_VOLATILE_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_VOLATILE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// remove_shallow_volatile
	//
	template<typename T>
	struct remove_shallow_volatile
		: public sprout::identity<T>
	{};
	template<typename T>
	struct remove_shallow_volatile<T volatile>
		: public std::conditional<std::is_array<T>::value, T volatile, T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_shallow_volatile_ = typename sprout::remove_shallow_volatile<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_VOLATILE_HPP
