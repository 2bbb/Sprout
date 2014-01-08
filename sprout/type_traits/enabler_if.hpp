/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ENABLER_IF_HPP
#define SPROUT_TYPE_TRAITS_ENABLER_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// enabler_t
	// enabler
	//
	typedef void* enabler_t;
	extern enabler_t enabler;
	//
	// enabler_if
	//
	template<bool C>
	class enabler_if
		: public std::enable_if<C, sprout::enabler_t&>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<bool C>
	using enabler_if_t = typename sprout::enabler_if<C>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ENABLER_IF_HPP
