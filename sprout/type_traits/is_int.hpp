#ifndef SPROUT_TYPE_TRAITS_IS_INT_HPP
#define SPROUT_TYPE_TRAITS_IS_INT_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// is_int
	//
	template<typename T>
	struct is_int
		: public std::integral_constant<
			bool,
			std::is_integral<T>::value && std::is_signed<T>::value
		>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using is_int_ = typename sprout::is_int<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_INT_HPP
