#ifndef SPROUT_CONTAINER_INTERNAL_END_HPP
#define SPROUT_CONTAINER_INTERNAL_END_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/sub_container_traits.hpp>
#include <sprout/container/internal.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/get_internal.hpp>

namespace sprout {
	//
	// internal_end
	//
	template<typename Container>
	typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::internal<Container&>::type
		>::type
	>::iterator
	internal_end(Container& cont) {
		return sprout::end(sprout::get_internal(cont));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::internal<Container const&>::type
		>::type
	>::const_iterator
	internal_end(Container const& cont) {
		return sprout::end(sprout::get_internal(cont));
	}

	//
	// internal_cend
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::internal<Container const&>::type
		>::type
	>::const_iterator
	internal_cend(Container const& cont) {
		return sprout::end(sprout::get_internal(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_END_HPP
