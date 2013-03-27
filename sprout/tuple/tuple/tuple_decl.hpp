#ifndef SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair_fwd.hpp>
#include <sprout/type_traits/is_convert_constructible.hpp>
#include <sprout/tpp/algorithm/all_of.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>
#include <sprout/tuple/tuple/flexibly_construct.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t Index, typename Head, bool IsEmpty>
			class head_base;
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
				template<typename...>
				friend class tuple;
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
				template<typename...>
				friend class tuple;
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
			public:
				void swap(tuple_impl& t)
				SPROUT_NOEXCEPT_EXPR(
					SPROUT_NOEXCEPT_EXPR(sprout::swap(head(std::declval<tuple_impl&>()), head(t)))
					&& SPROUT_NOEXCEPT_EXPR(std::declval<inherited_type&>().swap(tail(t)))
					)
				{
					sprout::swap(head(*this), head(t));
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
		}	// namespace detail

		//
		// tuple
		//
		template<typename... Types>
		class tuple
			: public sprout::tuples::detail::tuple_impl<0, Types...>
		{
		private:
			typedef sprout::tuples::detail::tuple_impl<0, Types...> impl_type;
		public:
			struct has_nothrow_swap
				: public sprout::tpp::all_of_c<
					SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(sprout::swap(std::declval<Types&>(), std::declval<Types&>()), false)...
				>
			{};
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple();
			explicit SPROUT_CONSTEXPR tuple(Types const&... elements);
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			explicit SPROUT_CONSTEXPR tuple(UTypes&&... elements);
			SPROUT_CONSTEXPR tuple(tuple const&);
			SPROUT_CONSTEXPR tuple(tuple&&);
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes const&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...> const& t);
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...>&& t);
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == 2 && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::pair<UTypes...> const& t);
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == 2 && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::pair<UTypes...>&& t);
			template<typename... UTypes>
			explicit SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, UTypes&&... elements);
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const& t);
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&& t);
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UTypes...> const& t);
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UTypes...>&& t);
			// tuple assignment
			tuple& operator=(tuple const& rhs);
			tuple& operator=(tuple&& rhs)
			SPROUT_NOEXCEPT_EXPR(sprout::tpp::all_of<std::is_nothrow_move_assignable<Types>...>::value);
			template<typename... UTypes>
			tuple& operator=(sprout::tuples::tuple<UTypes...> const& rhs);
			template<typename... UTypes>
			tuple& operator=(sprout::tuples::tuple<UTypes...>&& rhs);
			// tuple swap
			void swap(tuple& other)
			SPROUT_NOEXCEPT_EXPR(has_nothrow_swap::value);
		};
		template<>
		class tuple<> {
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple();
			SPROUT_CONSTEXPR tuple(tuple const&);
			SPROUT_CONSTEXPR tuple(tuple&&);
			template<typename... UTypes>
			explicit SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, UTypes&&... elements);
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const& t);
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&& t);
			// tuple swap
			void swap(tuple&) SPROUT_NOEXCEPT;
		};

		//
		// swap
		//
		template<typename... Types>
		inline void
		swap(sprout::tuples::tuple<Types...>& lhs, sprout::tuples::tuple<Types...>& rhs)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)));

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
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
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
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP
