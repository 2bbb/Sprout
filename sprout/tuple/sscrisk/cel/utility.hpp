#ifndef SPROUT_TUPLE_SSCRISK_CEL_UTILITY_HPP
#define SPROUT_TUPLE_SSCRISK_CEL_UTILITY_HPP

#include <cstddef>
#include <type_traits>
#include <sscrisk/cel/utility.hpp>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T1, typename T2>
		struct tuple_size<sscrisk::cel::pair<T1, T2> >
			: public std::integral_constant<std::size_t, 2>
		{};

		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<typename T1, typename T2>
			struct tuple_element_impl<0, sscrisk::cel::pair<T1, T2> > {
			public:
				typedef T1 type;
			};
			template<typename T1, typename T2>
			struct tuple_element_impl<1, sscrisk::cel::pair<T1, T2> > {
			public:
				typedef T2 type;
			};
		}	// namespace detail
		//
		// tuple_element
		//
		template<std::size_t I, typename T1, typename T2>
		struct tuple_element<I, sscrisk::cel::pair<T1, T2> >
			: public sprout::tuples::detail::tuple_element_impl<I, sscrisk::cel::pair<T1, T2> >
		{};

		namespace detail {
			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, sscrisk::cel::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T1& operator()(sscrisk::cel::pair<T1, T2>& t) const {
					return t.first;
				}
				SPROUT_CONSTEXPR T1 const& operator()(sscrisk::cel::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, sscrisk::cel::pair<T1, T2> > {
			public:
			public:
				SPROUT_CONSTEXPR T2& operator()(sscrisk::cel::pair<T1, T2>& t) const {
					return t.second;
				}
				SPROUT_CONSTEXPR T2 const& operator()(sscrisk::cel::pair<T1, T2> const& t) const {
					return t.second;
				}
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace sprout_adl {
		//
		// tuple_get
		//
		template<std::size_t I, typename T1, typename T2>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sscrisk::cel::pair<T1, T2> >::type&
		tuple_get(sscrisk::cel::pair<T1, T2>& t) SPROUT_NOEXCEPT {
			static_assert(I < 2, "tuple_get: index out of range");
			return sprout::tuples::detail::get_impl<I, sscrisk::cel::pair<T1, T2> >()(t);
		}
		template<std::size_t I, typename T1, typename T2>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sscrisk::cel::pair<T1, T2> >::type const&
		tuple_get(sscrisk::cel::pair<T1, T2> const& t) SPROUT_NOEXCEPT {
			static_assert(I < 2, "tuple_get: index out of range");
			return sprout::tuples::detail::get_impl<I, sscrisk::cel::pair<T1, T2> >()(t);
		}
		template<std::size_t I, typename T1, typename T2>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sscrisk::cel::pair<T1, T2> >::type&&
		tuple_get(sscrisk::cel::pair<T1, T2>&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout_adl

#endif	// #ifndef SPROUT_TUPLE_SSCRISK_CEL_UTILITY_HPP
