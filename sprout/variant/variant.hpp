#ifndef SPROUT_VARIANT_VARIANT_HPP
#define SPROUT_VARIANT_VARIANT_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/utility/operation.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/type/algorithm/find_index.hpp>

namespace sprout {
	namespace detail {
		template<typename... Types>
		class variant_impl {
		protected:
			typedef sprout::tuples::tuple<Types...> tuple_type;;
		private:
			template<typename T, std::ptrdiff_t... Indexes>
			static SPROUT_CONSTEXPR tuple_type init(T&& operand, sprout::index_tuple<Indexes...>) {
				return sprout::tuples::make_clone<tuple_type>(
					typename sprout::tuples::tuple_element<Indexes, tuple_type>::type()...,
					sprout::forward<T>(operand)
					);
			}
		protected:
			tuple_type tuple_;
			int which_;
		protected:
			SPROUT_CONSTEXPR variant_impl()
				: tuple_()
				, which_()
			{}
			template<typename T, typename Index>
			SPROUT_CONSTEXPR variant_impl(T&& operand, Index)
				: tuple_(init(sprout::forward<T>(operand), typename sprout::index_range<0, Index::value>::type()))
				, which_(Index::value)
			{
				static_assert(Index::value < sizeof...(Types), "variant<>: invalid operand");
			}
			void swap(variant_impl& other) SPROUT_NOEXCEPT_EXPR(
				SPROUT_NOEXCEPT_EXPR(swap(std::declval<tuple_type&>(), std::declval<tuple_type&>()))
				)
			{
				using std::swap;
				swap(tuple_, other.tuple_);
				swap(which_, other.which_);
			}
			variant_impl& operator=(variant_impl const&) = default;
		};
	}	// namespace detail
	//
	// variant
	//
	template<typename... Types>
	class variant
		: private sprout::detail::variant_impl<Types...>
	{
	private:
		typedef sprout::detail::variant_impl<Types...> impl_type;;
	public:
		typedef typename impl_type::tuple_type tuple_type;;
	private:
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			I == sizeof...(Types),
			bool
		>::type eq(tuple_type const& l, tuple_type const& r, int which) {
			return false;
		}
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			I != sizeof...(Types),
			bool
		>::type eq(tuple_type const& l, tuple_type const& r, int which) {
			return I == which
				? sprout::tuples::get<I>(l) == sprout::tuples::get<I>(r)
				: eq<I + 1>(l, r, which)
				;
		}
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			static_cast<std::size_t>(I) == sizeof...(Types),
			bool
		>::type lt(tuple_type const& l, tuple_type const& r, int which) {
			return false;
		}
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			static_cast<std::size_t>(I) != sizeof...(Types),
			bool
		>::type lt(tuple_type const& l, tuple_type const& r, int which) {
			return I == which
				? sprout::tuples::get<I>(l) < sprout::tuples::get<I>(r)
				: lt<I + 1>(l, r, which)
				;
		}
		template<int I, typename Elem, typename Traits>
		static typename std::enable_if<
			static_cast<std::size_t>(I) == sizeof...(Types),
			std::basic_ostream<Elem, Traits>&
		>::type output(std::basic_ostream<Elem, Traits>& os, tuple_type const& t, int which) {
			return os;
		}
		template<int I, typename Elem, typename Traits>
		static typename std::enable_if<
			static_cast<std::size_t>(I) != sizeof...(Types),
			std::basic_ostream<Elem, Traits>&
		>::type output(std::basic_ostream<Elem, Traits>& os, tuple_type const& t, int which) {
			return I == which
				? os << sprout::tuples::get<I>(t)
				: output<I + 1>(os, t, which)
				;
		}
	private:
		using impl_type::tuple_;
		using impl_type::which_;
	public:
		// construct/copy/destruct
		SPROUT_CONSTEXPR variant()
			: impl_type()
		{}
		variant(variant const&) = default;
		template<typename T>
		SPROUT_CONSTEXPR variant(T&& operand)
			: impl_type(sprout::forward<T>(operand), sprout::types::find_index<tuple_type, T>())
		{}
		// modifiers
		void swap(variant& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(impl_type::swap(other))) {
			impl_type::swap(other);
		}
		variant& operator=(variant const& rhs) {
			static_cast<impl_type&>(*this) = rhs;
			return *this;
		}
		variant& operator=(variant&& rhs) SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<impl_type>::value) {
			static_cast<impl_type&>(*this) = sprout::move(rhs);
			return *this;
		}
		template<typename T>
		variant& operator=(T&& rhs) {
			static_cast<impl_type&>(*this) = variant(sprout::forward<T>(rhs));
			return *this;
		}
		// queries
		SPROUT_CONSTEXPR int which() const {
			return which_;
		}
		SPROUT_CONSTEXPR bool empty() const {
			return sizeof...(Types) == 0;
		}
		// relational
		friend SPROUT_CONSTEXPR bool operator==(variant const& lhs, variant const& rhs) {
			return lhs.which_ == rhs.which_ && eq<0>(lhs.tuple_, rhs.tuple_, lhs.which_);
		}
		friend SPROUT_CONSTEXPR bool operator!=(variant const& lhs, variant const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(variant const& lhs, variant const& rhs) {
			return lhs.which_ < rhs.which_
				|| (lhs.which_ == rhs.which_ && lt<0>(lhs.tuple_, rhs.tuple_, lhs.which_))
				;
		}
		friend SPROUT_CONSTEXPR bool operator>(variant const& lhs, variant const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(variant const& lhs, variant const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(variant const& lhs, variant const& rhs) {
			return !(lhs < rhs);
		}

		template<typename Elem, typename Traits>
		friend std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& lhs, variant const& rhs) {
			return output<0>(lhs, rhs.tuple_, rhs.which_);
		}
		template<typename U>
		SPROUT_CONSTEXPR typename std::enable_if<
			sprout::types::find_index<tuple_type, U>::value != sizeof...(Types),
			U const&
		>::type get() const {
			return sprout::types::find_index<tuple_type, U>::value == static_cast<std::size_t>(which_)
				? sprout::tuples::get<sprout::types::find_index<tuple_type, U>::value>(tuple_)
				: (throw std::domain_error("variant<>: bad get"), sprout::tuples::get<sprout::types::find_index<tuple_type, U>::value>(tuple_))
				;
		}
		template<typename U>
		typename std::enable_if<
			sprout::types::find_index<tuple_type, U>::value != sizeof...(Types),
			U&
		>::type get() {
			return sprout::types::find_index<tuple_type, U>::value == which_
				? sprout::tuples::get<sprout::types::find_index<tuple_type, U>::value>(tuple_)
				: (throw std::domain_error("variant<>: bad get"), sprout::tuples::get<sprout::types::find_index<tuple_type, U>::value>(tuple_))
				;
		}
	};

	//
	// swap
	//
	template<typename... Types>
	inline void swap(
		sprout::variant<Types...>& lhs,
		sprout::variant<Types...>& rhs
		) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::variant<Types...> >
		: public std::tuple_size<typename sprout::variant<Types...>::tuple_tyep>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::variant<Types...> >
		: public std::tuple_element<I, typename sprout::variant<Types...>::tuple_tyep>
	{};
}	// namespace std

#endif	// #ifndef SPROUT_VARIANT_VARIANT_HPP
