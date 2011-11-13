#ifndef SPROUT_WEED_DETAIL_IS_CONTAINER_AND_ELEM_HPP
#define SPROUT_WEED_DETAIL_IS_CONTAINER_AND_ELEM_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/type/is_container.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T, typename U, typename = void>
			struct is_container_and_elem
				: public std::false_type
			{};
			template<typename T, typename U>
			struct is_container_and_elem<
				T,
				U,
				typename std::enable_if<
					sprout::weed::traits::is_container<T>::value
					&& std::is_same<
						typename T::value_type,
						U
					>::value
				>::type
			>
				: public std::true_type
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_IS_CONTAINER_AND_ELEM_HPP
