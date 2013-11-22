/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_CONSTANT_DISTANCE_ITERATOR_HPP
#define SPROUT_ITERATOR_TYPE_TRAITS_IS_CONSTANT_DISTANCE_ITERATOR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_constant_distance_iterator
	//
	template<typename MaybeIterator>
	struct is_constant_distance_iterator
		: public sprout::integral_constant<
			bool,
#ifdef SPROUT_NO_CXX14_CONSTEXPR
			sprout::is_random_access_iterator<MaybeIterator>::value && !std::is_pointer<MaybeIterator>::value
#else	// #ifdef SPROUT_NO_CXX14_CONSTEXPR
			sprout::is_random_access_iterator<MaybeIterator>::value
#endif	// #ifdef SPROUT_NO_CXX14_CONSTEXPR
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TYPE_TRAITS_IS_CONSTANT_DISTANCE_ITERATOR_HPP
