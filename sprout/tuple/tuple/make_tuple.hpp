/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_MAKE_TUPLE_HPP
#define SPROUT_TUPLE_TUPLE_MAKE_TUPLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/functional/ref.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/indexes.hpp>

namespace sprout {
	namespace tuples {
		//
		// make_tuple
		//
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<typename sprout::strip_reference<typename std::decay<Types>::type>::type...>
		make_tuple(Types&&... args) {
			return sprout::tuples::tuple<typename std::decay<Types>::type...>(SPROUT_FORWARD(Types, args)...);
		}

		//
		// forward_as_tuple
		//
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types&&...>
		forward_as_tuple(Types&&... args) SPROUT_NOEXCEPT {
			return sprout::tuples::tuple<Types&&...>(SPROUT_FORWARD(Types, args)...);
		}

		//
		// tie
		//
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types&...>
		tie(Types&... args) SPROUT_NOEXCEPT {
			return sprout::tuples::tuple<Types&...>(args...);
		}

		namespace results {
			namespace detail {
				template<typename... Tuples>
				struct tuple_cat_impl;
				template<>
				struct tuple_cat_impl<> {
					typedef sprout::tuples::tuple<> type;
				};
				template<typename Tuple>
				struct tuple_cat_impl<Tuple> {
				private:
					template<typename Tup, typename IndexTuple>
					struct make;
					template<typename Tup, sprout::index_t... Indexes>
					struct make<Tup, sprout::index_tuple<Indexes...> > {
					public:
						typedef sprout::tuples::tuple<typename sprout::tuples::tuple_element<Indexes, Tup>::type...> type;
					};
				public:
					typedef typename make<
						Tuple, typename sprout::tuple_indexes<Tuple>::type
					>::type type;
				};
				template<typename T, typename U, typename... Tuples>
				struct tuple_cat_impl<T, U, Tuples...> {
				private:
					template<typename Tup1, typename IndexTuple1, typename Tup2, typename IndexTuple2>
					struct make;
					template<typename Tup1, sprout::index_t... Indexes1, typename Tup2, sprout::index_t... Indexes2>
					struct make<Tup1, sprout::index_tuple<Indexes1...>, Tup2, sprout::index_tuple<Indexes2...> > {
					public:
						typedef sprout::tuples::tuple<
							typename sprout::tuples::tuple_element<Indexes1, Tup1>::type...,
							typename sprout::tuples::tuple_element<Indexes2, Tup2>::type...
						> type;
					};
				public:
					typedef typename sprout::tuples::results::detail::tuple_cat_impl<
						typename make<
							T, typename sprout::tuple_indexes<T>::type,
							U, typename sprout::tuple_indexes<U>::type
						>::type,
						Tuples...
					>::type type;
				};
			}	// namespace detail
			//
			// tuple_cat
			//
			template<typename... Tuples>
			struct tuple_cat
				: public sprout::tuples::results::detail::tuple_cat_impl<
					typename std::decay<Tuples>::type...
				>
			{};
		}	// namespace results

		namespace detail {
			template<typename... Tuples>
			struct tuple_cat_1st_indexes;
			template<>
			struct tuple_cat_1st_indexes<> {
			public:
				typedef sprout::index_tuple<> type;
			};
			template<typename Head, typename... Tail>
			struct tuple_cat_1st_indexes<Head, Tail...>
				: public sprout::tuple_indexes<typename std::remove_reference<Head>::type>
			{};

			template<typename Result, typename IndexTuple, typename... Tuples>
			struct tuple_cat_impl;
			template<typename Result>
			struct tuple_cat_impl<Result, sprout::index_tuple<> > {
			public:
				template<typename... Args>
				static SPROUT_CONSTEXPR Result
				call(Args&&... args) {
					return Result(SPROUT_FORWARD(Args, args)...);
				}
			};
			template<typename Result, sprout::index_t... Indexes, typename Head, typename... Tail>
			struct tuple_cat_impl<Result, sprout::index_tuple<Indexes...>, Head, Tail...> {
			public:
				template<typename T, typename... Args>
				static SPROUT_CONSTEXPR Result
				call(T&& t, Args&&... args) {
					return sprout::tuples::detail::tuple_cat_impl<
						Result,
						typename sprout::tuples::detail::tuple_cat_1st_indexes<Tail...>::type,
						Tail...
					>::call(
						SPROUT_FORWARD(Args, args)...,
						sprout::tuples::get<Indexes>(SPROUT_FORWARD(T, t))...
						);
				}
			};
		}	// namespace detail
		//
		// tuple_cat
		//
		template<typename... Tuples>
		inline SPROUT_CONSTEXPR typename sprout::tuples::results::tuple_cat<Tuples...>::type
		tuple_cat(Tuples&&... tuples) {
			return sprout::tuples::detail::tuple_cat_impl<
				typename sprout::tuples::results::tuple_cat<Tuples...>::type,
				typename sprout::tuples::detail::tuple_cat_1st_indexes<Tuples...>::type,
				Tuples...
			>::call(SPROUT_FORWARD(Tuples, tuples)...);
		}
	}	// namespace tuples

	namespace results {
		using sprout::tuples::results::tuple_cat;
	}	// namespace results

	using sprout::tuples::make_tuple;
	using sprout::tuples::forward_as_tuple;
	using sprout::tuples::tie;
	using sprout::tuples::tuple_cat;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_MAKE_TUPLE_HPP
