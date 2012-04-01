#ifndef SPROUT_FUNCTIONAL_MODULUS_HPP
#define SPROUT_FUNCTIONAL_X_HPP

#include <sprout/config.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 20.8.4 Arithmetic operations
	template<typename T>
	struct modulus {
	public:
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef T result_type;
	public:
		SPROUT_CONSTEXPR T operator()(T const& x, T const& y) const {
			 return x % y;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_MODULUS_HPP
