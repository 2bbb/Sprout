#ifndef SPROUT_INDEX_TUPLE_INTEGER_N_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_N_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/integer_seq.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>

namespace sprout {
	//
	// integer_n
	//
	namespace detail {
		template<typename T, typename Seq>
		struct integer_n_next_even;
		template<typename T, T... Is>
		struct integer_n_next_even<T, sprout::integer_seq<T, Is...> >
			: public sprout::integer_seq<T, Is..., Is...>
		{};

		template<typename T, typename Seq, T Tail>
		struct integer_n_next_even_odd;
		template<typename T, T... Is, T Tail>
		struct integer_n_next_even_odd<T, sprout::integer_seq<T, Is...>, Tail>
			: public sprout::integer_seq<T, Is..., Is..., Tail>
		{};

		template<typename T, T I, std::size_t N, typename Enable = void>
		struct integer_n_impl;
		template<typename T, T I, std::size_t N>
		struct integer_n_impl<
			T, I, N,
			typename std::enable_if<(N == 0)>::type
		>
			: public sprout::integer_seq<T>
		{};
		template<typename T, T I, std::size_t N>
		struct integer_n_impl<
			T, I, N,
			typename std::enable_if<(N == 1)>::type
		>
			: public sprout::integer_seq<T, I>
		{};
		template<typename T, T I, std::size_t N>
		struct integer_n_impl<
			T, I, N,
			typename std::enable_if<(N > 1 && N % 2 == 0)>::type
		>
			: public sprout::detail::integer_n_next_even<
				T, typename sprout::detail::integer_n_impl<T, I, N / 2>::type
			>
		{};
		template<typename T, T I, std::size_t N>
		struct integer_n_impl<
			T, I, N,
			typename std::enable_if<(N > 1 && N % 2 == 1)>::type
		>
			: public sprout::detail::integer_n_next_even_odd<
				T, typename sprout::detail::integer_n_impl<T, I, N / 2>::type,
				I
			>
		{};
	}	// namespace detail
	template<typename T, T I, std::size_t N>
	struct integer_n
		: public sprout::enable_make_indexes<
			sprout::detail::integer_n_impl<T, I, N>
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_N_HPP
