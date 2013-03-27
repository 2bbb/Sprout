#ifndef SPROUT_UTILITY_PAIR_PAIR_DECL_HPP
#define SPROUT_UTILITY_PAIR_PAIR_DECL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair_fwd.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>

namespace sprout {
	//
	// pair
	//
	template <typename T1, typename T2>
	struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	private:
		template <typename... Args1, typename... Args2, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
		SPROUT_CONSTEXPR pair(
			sprout::tuples::tuple<Args1...> first_args,
			sprout::tuples::tuple<Args2...> second_args,
			sprout::index_tuple<Indexes1...>,
			sprout::index_tuple<Indexes2...>
			);
	public:
		SPROUT_CONSTEXPR pair(pair const&);
		SPROUT_CONSTEXPR pair(pair&&);
		SPROUT_CONSTEXPR pair();
		SPROUT_CONSTEXPR pair(T1 const& x, T2 const& y);
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(U&& x, V&& y);
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V> const& other);
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V>&& other);
		template <typename... Args1, typename... Args2>
		SPROUT_CONSTEXPR pair(
			sprout::tuples::tuple<Args1...> first_args,
			sprout::tuples::tuple<Args2...> second_args
			);
		pair& operator=(pair const& other);
		template<typename U, typename V>
		pair& operator=(sprout::pair<U, V> const& other);
		pair& operator=(pair&& other)
		SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<T1>::value && std::is_nothrow_move_assignable<T2>::value);
		template<typename U, typename V>
		pair& operator=(sprout::pair<U, V>&& other);
		void swap(pair& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(first, other.first)) && SPROUT_NOEXCEPT_EXPR(sprout::swap(second, other.second)));
	};

	//
	// swap
	//
	template<typename T1, typename T2>
	inline void
	swap(sprout::pair<T1, T2>& lhs, sprout::pair<T1, T2>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)));
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_PAIR_DECL_HPP
