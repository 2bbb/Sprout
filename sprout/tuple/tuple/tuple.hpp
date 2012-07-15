#ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>
#include <sprout/tuple/tuple/type_traits.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t Index, typename Head, bool IsEmpty>
			class head_base;
			//!!!
			// EBO disabled
//			template<std::size_t Index, typename Head>
//			class head_base<Index, Head, true>
//				: public Head
//			{
//			public:
//				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
//					return t;
//				}
//				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
//					return t;
//				}
//			public:
//				SPROUT_CONSTEXPR head_base()
//					: Head()
//				{}
//				SPROUT_CONSTEXPR head_base(Head const& v)
//					: Head(v)
//				{}
//				template<typename UHead>
//				SPROUT_CONSTEXPR head_base(UHead&& v)
//					: Head(sprout::forward<UHead>(v))
//				{}
//			};
			template<std::size_t Index, typename Head>
			class head_base<Index, Head, true> {
			public:
				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
			private:
				Head head_;
			public:
				SPROUT_CONSTEXPR head_base()
					: head_()
				{}
				SPROUT_CONSTEXPR head_base(Head const& v)
					: head_(v)
				{}
				template<typename UHead>
				SPROUT_CONSTEXPR head_base(UHead&& v)
					: head_(sprout::forward<UHead>(v))
				{}
			};
			template<std::size_t Index, typename Head>
			class head_base<Index, Head, false> {
			public:
				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
			private:
				Head head_;
			public:
				SPROUT_CONSTEXPR head_base()
					: head_()
				{}
				SPROUT_CONSTEXPR head_base(Head const& v)
					: head_(v)
				{}
				template<typename UHead>
				SPROUT_CONSTEXPR head_base(UHead&& v)
					: head_(sprout::forward<UHead>(v))
				{}
			};

			template<std::size_t Index, typename... Types>
			class tuple_impl;
			template<std::size_t Index>
			class tuple_impl<Index> {
			public:
				template<std::size_t, typename...>
				friend class sprout::tuples::detail::tuple_impl;
			protected:
				void swap(tuple_impl&) SPROUT_NOEXCEPT {}
			public:
				tuple_impl() = default;
				template<typename... UTypes>
				explicit SPROUT_CONSTEXPR tuple_impl(UTypes&&... args) SPROUT_NOEXCEPT {}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl const&) = default;
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&&) = default;
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...> const& t) SPROUT_NOEXCEPT {}
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...>&& t) SPROUT_NOEXCEPT {}
				tuple_impl& operator=(tuple_impl const&) = default;
				tuple_impl& operator=(tuple_impl&& t) = default;
				template<typename... UTypes>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UTypes...> const&) SPROUT_NOEXCEPT {
					return *this;
				}
				template<typename... UTypes>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UTypes...>&&) SPROUT_NOEXCEPT {
					return *this;
				}
			};
			template<std::size_t Index, typename Head, typename... Tail>
			class tuple_impl<Index, Head, Tail...>
				: public sprout::tuples::detail::tuple_impl<Index + 1, Tail...>
				, private sprout::tuples::detail::head_base<Index, Head, std::is_empty<Head>::value>
			{
			public:
				template<std::size_t, typename...>
				friend class sprout::tuples::detail::tuple_impl;
			public:
				typedef sprout::tuples::detail::tuple_impl<Index + 1, Tail...> inherited_type;
				typedef sprout::tuples::detail::head_base<Index, Head, std::is_empty<Head>::value> base_type;
			public:
				static SPROUT_CONSTEXPR Head& head(tuple_impl& t) SPROUT_NOEXCEPT {
					return base_type::head(t);
				}
				static SPROUT_CONSTEXPR Head const& head(tuple_impl const& t) SPROUT_NOEXCEPT {
					return base_type::head(t);
				}
				static SPROUT_CONSTEXPR inherited_type& tail(tuple_impl& t) SPROUT_NOEXCEPT {
					return t;
				}
				static SPROUT_CONSTEXPR inherited_type const& tail(tuple_impl const& t) SPROUT_NOEXCEPT {
					return t;
				}
			protected:
				void swap(tuple_impl& t) SPROUT_NOEXCEPT_EXPR(
					SPROUT_NOEXCEPT_EXPR(swap(std::declval<Head&>(), std::declval<Head&>()))
					&& SPROUT_NOEXCEPT_EXPR(tail(t).swap(tail(t)))
					)
				{
					using std::swap;
					swap(head(*this), head(t));
					inherited_type::swap(tail(t));
				}
			public:
				SPROUT_CONSTEXPR tuple_impl()
					: inherited_type()
					, base_type()
				{}
				explicit SPROUT_CONSTEXPR tuple_impl(Head const& h, Tail const&... tail)
					: inherited_type(tail...)
					, base_type(h)
				{}
				template<typename UHead, typename... UTail>
				explicit SPROUT_CONSTEXPR tuple_impl(UHead&& h, UTail&&... tail)
					: inherited_type(sprout::forward<UTail>(tail)...)
					, base_type(sprout::forward<UHead>(h))
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl const&) = default;
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&& t)
				SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_constructible<Head>::value && std::is_nothrow_move_constructible<inherited_type>::value)
					: inherited_type(sprout::move(tail(t)))
					, base_type(sprout::forward<Head>(head(t)))
				{}
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...> const& t)
					: inherited_type(sprout::tuples::detail::tuple_impl<Index, UTypes...>::tail(t))
					, base_type(sprout::tuples::detail::tuple_impl<Index, UTypes...>::head(t))
				{}
				template<typename UHead, typename... UTail>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UHead, UTail...>&& t)
					: inherited_type(sprout::move(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::tail(t)))
					, base_type(sprout::forward<UHead>(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::head(t)))
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index> const& t)
					: inherited_type()
					, base_type()
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index>&& t)
					: inherited_type()
					, base_type()
				{}
				tuple_impl& operator=(tuple_impl const& t) {
					head(*this) = head(t);
					tail(*this) = tail(t);
					return *this;
				}
				tuple_impl& operator=(tuple_impl&& t)
				SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<Head>::value && std::is_nothrow_move_assignable<inherited_type>::value)
				{
					head(*this) = sprout::forward<Head>(head(t));
					tail(*this) = sprout::move(tail(t));
					return *this;
				}
				template<typename... UTypes>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UTypes...> const& t) {
					head(*this) = sprout::tuples::detail::tuple_impl<Index, UTypes...>::head(t);
					tail(*this) = sprout::tuples::detail::tuple_impl<Index, UTypes...>::tail(t);
					return *this;
				}
				template<typename UHead, typename... UTail>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>&& t) {
					head(*this) = sprout::forward<UHead>(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::head(t));
					tail(*this) = sprout::move(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::tail(t));
					return *this;
				}
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index> const& t) {
					*this = sprout::move(tuple_impl());
					return *this;
				}
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index>&& t) {
					*this = sprout::move(tuple_impl());
					return *this;
				}
			};

			template<bool Head, bool... Tail>
			struct and_impl;
			template<>
			struct and_impl<true>
				: public std::true_type
			{};
			template<>
			struct and_impl<false>
				: public std::false_type
			{};
			template<bool... Tail>
			struct and_impl<true, Tail...>
				: public std::integral_constant<bool, sprout::tuples::detail::and_impl<Tail...>::value>
			{};
			template<bool... Tail>
			struct and_impl<false, Tail...>
				: public std::false_type
			{};
			template<typename... Types>
			struct and_
				: public sprout::tuples::detail::and_impl<Types::value...>
			{};

			template<bool Head, bool... Tail>
			struct or_impl;
			template<>
			struct or_impl<true>
				: public std::true_type
			{};
			template<>
			struct or_impl<false>
				: public std::false_type
			{};
			template<bool... Tail>
			struct or_impl<true, Tail...>
				: public std::true_type
			{};
			template<bool... Tail>
			struct or_impl<false, Tail...>
				: public std::integral_constant<bool, sprout::tuples::detail::or_impl<Tail...>::value>
			{};
			template<typename... Types>
			struct or_
				: public sprout::tuples::detail::and_impl<Types::value...>
			{};
		}	// namespace detail

		//
		// tuple
		//
		template<typename... Types>
		class tuple
			: public sprout::tuples::detail::tuple_impl<0, Types...>
		{
		public:
			typedef sprout::tuples::detail::tuple_impl<0, Types...> inherited_type;
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple()
				: inherited_type()
			{}
			explicit SPROUT_CONSTEXPR tuple(Types const&... elements)
				: inherited_type(elements...)
			{}
			template<
				typename U,
				typename = typename std::enable_if<
					!sprout::tuples::is_tuple<typename std::remove_reference<U>::type>::value
				>::type
			>
			explicit SPROUT_CONSTEXPR tuple(U&& elem)
				: inherited_type(sprout::forward<U>(elem))
			{}
			template<
				typename U1,
				typename U2,
				typename... UTypes
			>
			explicit SPROUT_CONSTEXPR tuple(U1&& elem1, U2&& elem2, UTypes&&... elements)
				: inherited_type(sprout::forward<U1>(elem1), sprout::forward<U2>(elem2), sprout::forward<UTypes>(elements)...)
			{}
			SPROUT_CONSTEXPR tuple(tuple const&) = default;
			SPROUT_CONSTEXPR tuple(tuple&&) = default;
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...> const& t)
				: inherited_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...> const&>(t))
			{}
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...>&& t)
				: inherited_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...>&&>(t))
			{}
			// tuple assignment
			tuple& operator=(tuple const& rhs) {
				static_cast<inherited_type&>(*this) = rhs;
				return *this;
			}
			tuple& operator=(tuple&& rhs) SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<inherited_type>::value) {
				static_cast<inherited_type&>(*this) = sprout::move(rhs);
				return *this;
			}
			template<typename... UTypes>
			tuple& operator=(sprout::tuples::tuple<UTypes...> const& rhs) {
				static_cast<inherited_type&>(*this) = rhs;
				return *this;
			}
			template<typename... UTypes>
			tuple& operator=(sprout::tuples::tuple<UTypes...>&& rhs) {
				static_cast<inherited_type&>(*this) = sprout::move(rhs);
				return *this;
			}
			// tuple swap
			void swap(tuple& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(inherited_type::swap(other))) {
				inherited_type::swap(other);
			}
		};
		template<>
		class tuple<> {
		public:
			// tuple swap
			void swap(tuple&) SPROUT_NOEXCEPT {}
		};

		//
		// swap
		//
		template<typename... Types>
		inline void swap(
			sprout::tuples::tuple<Types...>& lhs,
			sprout::tuples::tuple<Types...>& rhs
			) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
		{
			lhs.swap(rhs);
		}

		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<typename Head, typename... Tail>
			struct tuple_element_impl<0, sprout::tuples::tuple<Head, Tail...> > {
			public:
				typedef Head type;
			};
			template<std::size_t I, typename Head, typename... Tail>
			struct tuple_element_impl<I, sprout::tuples::tuple<Head, Tail...> >
				: public sprout::tuples::detail::tuple_element_impl<I - 1, sprout::tuples::tuple<Tail...> >
			{};
		}	// namespace detail
	}	// namespace tuples

	using sprout::tuples::tuple;
	using sprout::tuples::swap;
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::tuples::tuple<Types...> >
		: public std::integral_constant<std::size_t, sizeof...(Types)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::tuples::tuple<Types...> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::tuples::tuple<Types...> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
