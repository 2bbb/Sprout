#ifndef SPROUT_STRING_CONTAINER_HPP
#define SPROUT_STRING_CONTAINER_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/string/string.hpp>
#include <sprout/container/traits.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename T, std::size_t N, typename Traits>
	struct container_construct_traits<sprout::basic_string<T, N, Traits> > {
	public:
		typedef sprout::basic_string<T, N, Traits> copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return sprout::forward<Cont>(cont);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			typedef sprout::detail::make_construct_impl<copied_type> impl_type;
			return impl_type::make(impl_type::length(sprout::forward<Args>(args)...), sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::basic_string<T, N, Traits> >::difference_type size,
			Args&&... args
			)
		{
			typedef sprout::detail::make_construct_impl<copied_type> impl_type;
			return impl_type::make(size, sprout::forward<Args>(args)...);
		}
	};

	//
	// container_transform_traits
	//
	template<typename T, std::size_t N, typename Traits>
	struct container_transform_traits<sprout::basic_string<T, N, Traits> > {
	public:
		template<typename sprout::container_traits<sprout::basic_string<T, N, Traits> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::basic_string<T, Size, Traits> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_CONTAINER_HPP
