#ifndef SPROUT_FIXED_CONTAINER_GET_DEEP_INTERNAL_HPP
#define SPROUT_FIXED_CONTAINER_GET_DEEP_INTERNAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/get_internal.hpp>
#include <sprout/container/deep_internal.hpp>
#include <sprout/container/is_sub_container.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
		template<
			typename Container,
			typename sprout::enabler_if<!sprout::containers::is_sub_container<Container>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::containers::deep_internal<Container>::type
		get_deep_internal_impl(Container&& cont) {
			return sprout::forward<Container>(cont);
		}
		template<
			typename Container,
			typename sprout::enabler_if<sprout::containers::is_sub_container<Container>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::containers::deep_internal<Container>::type
		get_deep_internal_impl(Container&& cont) {
			return sprout::detail::get_deep_internal_impl(
				sprout::get_internal(sprout::forward<Container>(cont))
				);
		}
	}	// namespace detail
	//
	// get_deep_internal
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::containers::deep_internal<Container>::type
	get_deep_internal(Container&& cont) {
		return sprout::detail::get_deep_internal_impl(sprout::forward<Container>(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_GET_DEEP_INTERNAL_HPP
