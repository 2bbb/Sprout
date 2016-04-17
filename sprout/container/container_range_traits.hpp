/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/is_const_cast_convertible.hpp>
#include <sprout/type_traits/is_within_namespace_sprout.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/const_iterator_cast.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl begin(...);
	sprout::not_found_via_adl end(...);

	sprout::not_found_via_adl range_begin(...);
	sprout::not_found_via_adl range_end(...);
	sprout::not_found_via_adl range_size(...);
	sprout::not_found_via_adl range_empty(...);
	sprout::not_found_via_adl range_front(...);
	sprout::not_found_via_adl range_back(...);
	sprout::not_found_via_adl range_subscript_at(...);
	sprout::not_found_via_adl range_at(...);
	sprout::not_found_via_adl range_nth(...);
	sprout::not_found_via_adl range_index_of(...);
	sprout::not_found_via_adl range_data(...);
}	// namespace sprout_adl


namespace sprout_container_range_detail {
	using sprout_adl::begin;
	using sprout_adl::end;

	template<typename T>
	struct has_adl_begin_test {
	public:
		template<
			typename U = T,
			typename R = typename sprout::identity<decltype(begin(std::declval<U>()))>::type
		>
		static sprout::is_found_via_adl<R> test(int);
		static sprout::false_type test(...);
	};

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_adl_begin(Container& cont) {
		return begin(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_adl_begin(Container const& cont) {
		return begin(cont);
	}

	template<typename T>
	struct has_adl_end_test {
	public:
		template<
			typename U = T,
			typename R = typename sprout::identity<decltype(end(std::declval<U>()))>::type
		>
		static sprout::is_found_via_adl<R> test(int);
		static sprout::false_type test(...);
	};

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_adl_end(Container& cont) {
		return end(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_adl_end(Container const& cont) {
		return end(cont);
	}
}	// namespace sprout_container_range_detail

namespace sprout {
	namespace detail {
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout_container_range_detail::has_adl_begin_test<T>::test(0))>::type>
		struct has_adl_begin
			: public Base_
		{};
#else
		template<typename T>
		struct has_adl_begin
			: public sprout::identity<decltype(sprout_container_range_detail::has_adl_begin_test<T>::test(0))>::type
		{};
#endif
		template<typename T, bool = sprout::is_within_namespace_sprout<T>::value>
		struct has_adl_begin_without_sprout
			: public sprout::false_type
		{};
		template<typename T>
		struct has_adl_begin_without_sprout<T, false>
			: public sprout::detail::has_adl_begin<T>
		{};

		template<typename T>
		struct has_mem_begin_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().begin())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_begin_test<T>::test(0))>::type>
		struct has_mem_begin
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_begin
			: public sprout::identity<decltype(sprout::detail::has_mem_begin_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_begin
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_begin<T const>::value
						|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_begin<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::const_iterator_cast<type>(sprout::begin(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_begin<Container>::value
				&& sprout::detail::has_mem_begin<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			return cont.begin();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_begin<Container>::value
				&& !sprout::detail::has_mem_begin<Container>::value
				&& sprout::detail::has_adl_begin_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			return sprout_container_range_detail::range_adl_begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_begin<Container>::value
				&& !sprout::detail::has_mem_begin<Container>::value
				&& !sprout::detail::has_adl_begin_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_begin_impl(Container& cont) {
			return std::begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_begin<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_begin_impl(Container const& cont) {
			return cont.begin();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_begin<Container const>::value
				&& sprout::detail::has_adl_begin_without_sprout<Container const&>::value
				,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_begin_impl(Container const& cont) {
			return sprout_container_range_detail::range_adl_begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_begin<Container const>::value
				&& !sprout::detail::has_adl_begin_without_sprout<Container const&>::value
				,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_begin_impl(Container const& cont) {
			return std::begin(cont);
		}

#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout_container_range_detail::has_adl_end_test<T>::test(0))>::type>
		struct has_adl_end
			: public Base_
		{};
#else
		template<typename T>
		struct has_adl_end
			: public sprout::identity<decltype(sprout_container_range_detail::has_adl_end_test<T>::test(0))>::type
		{};
#endif
		template<typename T, bool = sprout::is_within_namespace_sprout<T>::value>
		struct has_adl_end_without_sprout
			: public sprout::false_type
		{};
		template<typename T>
		struct has_adl_end_without_sprout<T, false>
			: public sprout::detail::has_adl_end<T>
		{};

		template<typename T>
		struct has_mem_end_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().end())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_end_test<T>::test(0))>::type>
		struct has_mem_end
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_end
			: public sprout::identity<decltype(sprout::detail::has_mem_end_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_end
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_end<T const>::value
						|| sprout::detail::has_adl_end_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_end<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::const_iterator_cast<type>(sprout::end(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_end<Container>::value
				&& sprout::detail::has_adl_end_without_sprout<Container&>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			return sprout_container_range_detail::range_adl_end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_end<Container>::value
				&& !sprout::detail::has_adl_end_without_sprout<Container&>::value
				&& sprout::detail::has_mem_end<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			return cont.end();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_end<Container>::value
				&& !sprout::detail::has_adl_end_without_sprout<Container&>::value
				&& !sprout::detail::has_mem_end<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_end_impl(Container& cont) {
			return std::end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_adl_end_without_sprout<Container const&>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_end_impl(Container const& cont) {
			return sprout_container_range_detail::range_adl_end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_adl_end_without_sprout<Container const&>::value && sprout::detail::has_mem_end<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_end_impl(Container const& cont) {
			return cont.end();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_adl_end_without_sprout<Container const&>::value && !sprout::detail::has_mem_end<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_end_impl(Container const& cont) {
			return std::end(cont);
		}

		template<typename T>
		struct has_mem_size_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().size())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_size_test<T>::test(0))>::type>
		struct has_mem_size
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_size
			: public sprout::identity<decltype(sprout::detail::has_mem_size_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_size<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_size_impl(Container const& cont) {
			return cont.size();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_size<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_size_impl(Container const& cont) {
			return sprout::distance(sprout::begin(cont), sprout::end(cont));
		}

		template<typename T>
		struct has_mem_empty_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().empty())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_empty_test<T>::test(0))>::type>
		struct has_mem_empty
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_empty
			: public sprout::identity<decltype(sprout::detail::has_mem_empty_test<T>::test(0))>::type
		{};
#endif

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_empty<Container const>::value,
			bool
		>::type
		range_empty_impl(Container const& cont) {
			return cont.empty();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_empty<Container const>::value,
			bool
		>::type
		range_empty_impl(Container const& cont) {
			return sprout::size(cont) == 0;
		}

		template<typename T>
		struct has_mem_front_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().front())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_front_test<T>::test(0))>::type>
		struct has_mem_front
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_front
			: public sprout::identity<decltype(sprout::detail::has_mem_front_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_front
			: public sprout::bool_constant<
				sprout::is_const_cast_convertible<
					typename sprout::container_traits<T const>::reference,
					typename sprout::container_traits<T>::reference
				>::value
				&& (
					sprout::detail::has_mem_front<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_front<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_front_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::reference type;
			return const_cast<type>(sprout::front(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_front<Container>::value
				&& sprout::detail::has_mem_front<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_front_impl(Container& cont) {
			return cont.front();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_front<Container>::value
				&& !sprout::detail::has_mem_front<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_front_impl(Container& cont) {
			return *sprout::begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_front<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_front_impl(Container const& cont) {
			return cont.front();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_front<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_front_impl(Container const& cont) {
			return *sprout::begin(cont);
		}

		template<typename T>
		struct has_mem_back_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().back())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_back_test<T>::test(0))>::type>
		struct has_mem_back
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_back
			: public sprout::identity<decltype(sprout::detail::has_mem_back_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_back
			: public sprout::bool_constant<
				sprout::is_const_cast_convertible<
					typename sprout::container_traits<T const>::reference,
					typename sprout::container_traits<T>::reference
				>::value
				&& (
					sprout::detail::has_mem_back<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_back<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_back_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::reference type;
			return const_cast<type>(sprout::back(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_back<Container>::value
				&& sprout::detail::has_mem_back<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_back_impl(Container& cont) {
			return cont.back();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_back<Container>::value
				&& !sprout::detail::has_mem_back<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_back_impl(Container& cont) {
			return *sprout::begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_back<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_back_impl(Container const& cont) {
			return cont.back();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_back<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_back_impl(Container const& cont) {
			return *sprout::next(sprout::begin(cont), sprout::size(cont) - 1);
		}

		template<typename T>
		struct has_mem_subscript_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>()[std::declval<typename sprout::container_traits<U>::size_type>()])>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_subscript_test<T>::test(0))>::type>
		struct has_mem_subscript
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_subscript
			: public sprout::identity<decltype(sprout::detail::has_mem_subscript_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_subscript_at
			: public sprout::bool_constant<
				sprout::is_const_cast_convertible<
					typename sprout::container_traits<T const>::reference,
					typename sprout::container_traits<T>::reference
				>::value
				&& (
					sprout::detail::has_mem_subscript<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_subscript_at<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_subscript_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			typedef typename sprout::container_traits<Container>::reference type;
			return const_cast<type>(sprout::subscript_at(sprout::as_const(cont), i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_subscript_at<Container>::value
				&& sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_subscript_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont[i];
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_subscript_at<Container>::value
				&& !sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_subscript_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return *sprout::next(sprout::begin(cont), i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_subscript<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_subscript_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont[i];
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_subscript<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_subscript_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return *sprout::next(sprout::begin(cont), i);
		}

		template<typename T>
		struct has_mem_at_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().at(std::declval<typename sprout::container_traits<U>::size_type>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_at_test<T>::test(0))>::type>
		struct has_mem_at
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_at
			: public sprout::identity<decltype(sprout::detail::has_mem_at_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_at
			: public sprout::bool_constant<
				sprout::is_const_cast_convertible<
					typename sprout::container_traits<T const>::reference,
					typename sprout::container_traits<T>::reference
				>::value
				&& (
					sprout::detail::has_mem_at<T const>::value
					|| sprout::detail::has_mem_subscript<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_at<Container>::value,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			typedef typename sprout::container_traits<Container>::reference type;
			return const_cast<type>(sprout::at(sprout::as_const(cont), i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_at<Container>::value
				&& sprout::detail::has_mem_at<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont.at(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_at<Container>::value
				&& !sprout::detail::has_mem_at<Container>::value
				&& sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont[sprout::range_index_check(cont, i)];
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_at<Container>::value
				&& !sprout::detail::has_mem_at<Container>::value
				&& !sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container>::reference
		>::type
		range_at_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return *sprout::next(sprout::begin(cont), sprout::range_index_check(cont, i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_at<Container const>::value,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont.at(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_at<Container const>::value
				&& sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont[sprout::range_index_check(cont, i)];
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_at<Container const>::value
				&& !sprout::detail::has_mem_subscript<Container>::value
				,
			typename sprout::container_traits<Container const>::reference
		>::type
		range_at_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return *sprout::next(sprout::begin(cont), sprout::range_index_check(cont, i));
		}

		template<typename T>
		struct has_mem_nth_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().nth(std::declval<typename sprout::container_traits<U>::size_type>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_nth_test<T>::test(0))>::type>
		struct has_mem_nth
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_nth
			: public sprout::identity<decltype(sprout::detail::has_mem_nth_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_nth
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_nth<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_nth<Container>::value,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::const_iterator_cast<type>(sprout::nth(sprout::as_const(cont), i));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_nth<Container>::value
				&& sprout::detail::has_mem_nth<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return cont.nth(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_nth<Container>::value
				&& !sprout::detail::has_mem_nth<Container>::value
				,
			typename sprout::container_traits<Container>::iterator
		>::type
		range_nth_impl(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return sprout::next(sprout::begin(cont), i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_nth<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_nth_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return cont.nth(i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_nth<Container const>::value,
			typename sprout::container_traits<Container const>::iterator
		>::type
		range_nth_impl(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return sprout::next(sprout::begin(cont), i);
		}

		template<typename T>
		struct has_mem_index_of_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().index_of(std::declval<typename sprout::container_traits<U>::iterator>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_index_of_test<T>::test(0))>::type>
		struct has_mem_index_of
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_index_of
			: public sprout::identity<decltype(sprout::detail::has_mem_index_of_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_index_of
			: public sprout::bool_constant<
				sprout::is_const_iterator_cast_convertible<
					typename sprout::container_traits<T const>::iterator,
					typename sprout::container_traits<T>::iterator
				>::value
				&& (
					sprout::detail::has_mem_index_of<T const>::value
					|| sprout::detail::has_mem_begin<T const>::value
					|| sprout::detail::has_adl_begin_without_sprout<T const&>::value
					)
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_index_of<Container>::value,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			typedef typename sprout::container_traits<Container>::iterator type;
			return sprout::index_of(sprout::as_const(cont), sprout::const_iterator_cast<type>(p));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_index_of<Container>::value
				&& sprout::detail::has_mem_index_of<Container>::value
				,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return cont.index_of(p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_index_of<Container>::value
				&& !sprout::detail::has_mem_index_of<Container>::value
				,
			typename sprout::container_traits<Container>::size_type
		>::type
		range_index_of_impl(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return sprout::distance(sprout::begin(cont), p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::has_mem_index_of<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_index_of_impl(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return cont.index_of(p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::has_mem_index_of<Container const>::value,
			typename sprout::container_traits<Container const>::size_type
		>::type
		range_index_of_impl(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return sprout::distance(sprout::begin(cont), p);
		}

		template<typename T>
		struct has_mem_data_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().data())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_data_test<T>::test(0))>::type>
		struct has_mem_data
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_data
			: public sprout::identity<decltype(sprout::detail::has_mem_data_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct is_substitutable_const_data
			: public sprout::bool_constant<
				sprout::is_const_cast_convertible<
					typename sprout::container_traits<T const>::pointer,
					typename sprout::container_traits<T>::pointer
				>::value
				&& sprout::detail::has_mem_data<T const>::value
			>
		{};

		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::is_substitutable_const_data<Container>::value,
			typename sprout::container_traits<Container>::pointer
		>::type
		range_data_impl(Container& cont) {
			typedef typename sprout::container_traits<Container>::pointer type;
			return const_cast<type>(sprout::data(sprout::as_const(cont)));
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::detail::is_substitutable_const_data<Container>::value,
			typename sprout::container_traits<Container>::pointer
		>::type
		range_data_impl(Container& cont) {
			return cont.data();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
		range_data_impl(Container const& cont) {
			return cont.data();
		}
	}	// namespace detail
}	// namespace sprout

namespace sprout_container_range_detail {
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_begin(Container& cont) {
		return sprout::detail::range_begin_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_begin(Container const& cont) {
		return sprout::detail::range_begin_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_end(Container& cont) {
		return sprout::detail::range_end_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_end(Container const& cont) {
		return sprout::detail::range_end_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_size(Container const& cont) {
		return sprout::detail::range_size_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	range_empty(Container const& cont) {
		return sprout::detail::range_empty_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_front(Container& cont) {
		return sprout::detail::range_front_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_front(Container const& cont) {
		return sprout::detail::range_front_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_back(Container& cont) {
		return sprout::detail::range_back_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_back(Container const& cont) {
		return sprout::detail::range_back_impl(cont);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_subscript_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_subscript_at_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_subscript_at_impl(cont, i);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_at_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_at_impl(cont, i);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	range_nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::detail::range_nth_impl(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::detail::range_nth_impl(cont, i);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	range_index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
		return sprout::detail::range_index_of_impl(cont, p);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
		return sprout::detail::range_index_of_impl(cont, p);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
	range_data(Container& cont) {
		return sprout::detail::range_data_impl(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	range_data(Container const& cont) {
		return sprout::detail::range_data_impl(cont);
	}
}	// namespace sprout_container_range_detail

namespace sprout {
	namespace detail {
		//
		// container_range_traits_default
		//
		template<typename Container>
		struct container_range_traits_default {
		public:
			// iterators:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
			range_begin(Container& cont) {
				using sprout_container_range_detail::range_begin;
				using sprout_adl::range_begin;
				return range_begin(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_begin(Container const& cont) {
				using sprout_container_range_detail::range_begin;
				using sprout_adl::range_begin;
				return range_begin(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
			range_end(Container& cont) {
				using sprout_container_range_detail::range_end;
				using sprout_adl::range_end;
				return range_end(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_end(Container const& cont) {
				using sprout_container_range_detail::range_end;
				using sprout_adl::range_end;
				return range_end(cont);
			}
			// capacity:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_size(Container const& cont) {
				using sprout_container_range_detail::range_size;
				using sprout_adl::range_size;
				return range_size(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_empty(Container const& cont) {
				using sprout_container_range_detail::range_empty;
				using sprout_adl::range_empty;
				return range_empty(cont);
			}
			// element access:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_front(Container& cont) {
				using sprout_container_range_detail::range_front;
				using sprout_adl::range_front;
				return range_front(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_front(Container const& cont) {
				using sprout_container_range_detail::range_front;
				using sprout_adl::range_front;
				return range_front(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_back(Container& cont) {
				using sprout_container_range_detail::range_back;
				using sprout_adl::range_back;
				return range_back(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_back(Container const& cont) {
				using sprout_container_range_detail::range_back;
				using sprout_adl::range_back;
				return range_back(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_subscript_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
				using sprout_container_range_detail::range_subscript_at;
				using sprout_adl::range_subscript_at;
				return range_subscript_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				using sprout_container_range_detail::range_subscript_at;
				using sprout_adl::range_subscript_at;
				return range_subscript_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
			range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
				using sprout_container_range_detail::range_at;
				using sprout_adl::range_at;
				return range_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				using sprout_container_range_detail::range_at;
				using sprout_adl::range_at;
				return range_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
			range_nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
				using sprout_container_range_detail::range_nth;
				using sprout_adl::range_nth;
				return range_nth(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				using sprout_container_range_detail::range_nth;
				using sprout_adl::range_nth;
				return range_nth(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
			range_index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
				using sprout_container_range_detail::range_index_of;
				using sprout_adl::range_index_of;
				return range_index_of(cont, p);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
				using sprout_container_range_detail::range_index_of;
				using sprout_adl::range_index_of;
				return range_index_of(cont, p);
			}
			// data access:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
			range_data(Container& cont) {
				using sprout_container_range_detail::range_data;
				using sprout_adl::range_data;
				return range_data(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
			range_data(Container const& cont) {
				using sprout_container_range_detail::range_data;
				using sprout_adl::range_data;
				return range_data(cont);
			}
		};
		//
		// container_range_traits_const_default
		//
		template<typename Container>
		struct container_range_traits_const_default {
		public:
			// iterators:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_begin(Container const& cont) {
				return sprout::container_range_traits<Container>::range_begin(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_end(Container const& cont) {
				return sprout::container_range_traits<Container>::range_end(cont);
			}
			// capacity:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_size(Container const& cont) {
				return sprout::container_range_traits<Container>::range_size(cont);
			}
			static SPROUT_CONSTEXPR bool
			range_empty(Container const& cont) {
				return sprout::container_range_traits<Container>::range_empty(cont);
			}
			// element access:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_front(Container const& cont) {
				return sprout::container_range_traits<Container>::range_front(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_back(Container const& cont) {
				return sprout::container_range_traits<Container>::range_back(cont);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return sprout::container_range_traits<Container>::range_subscript_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
			range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return sprout::container_range_traits<Container>::range_at(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
			range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
				return sprout::container_range_traits<Container>::range_nth(cont, i);
			}
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
			range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
				return sprout::container_range_traits<Container>::range_index_of(cont, p);
			}
			// data access:
			static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
			range_data(Container const& cont) {
				return sprout::container_range_traits<Container>::range_data(cont);
			}
		};
	}	// namespace detail

	//
	// container_range_traits
	//
	template<typename Container>
	struct container_range_traits
		: public sprout::detail::container_range_traits_default<Container>
	{};
	template<typename Container>
	struct container_range_traits<Container const>
		: public sprout::detail::container_range_traits_const_default<Container>
	{};

	template<typename T, std::size_t N>
	struct container_range_traits<T[N]> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_begin(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_end(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr) + N;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_end(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr) + N;
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
		range_size(T const (&)[N]) {
			return N;
		}
		static SPROUT_CONSTEXPR bool
		range_empty(T const (&)[N]) {
			return false;
		}
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_front(T (& arr)[N]) {
			return arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_front(T const (& arr)[N]) {
			return arr[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_back(T (& arr)[N]) {
			return arr[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_back(T const (& arr)[N]) {
			return arr[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_subscript_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_subscript_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
		range_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return arr[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_nth(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr) + i;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_nth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr) + i;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
		range_index_of(T (& arr)[N], typename sprout::container_traits<T[N]>::iterator p) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return sprout::distance(type(arr), p);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_index_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return sprout::distance(type(arr), p);
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::pointer
		range_data(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::pointer type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
		range_data(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::pointer type;
			return type(arr);
		}
	};
	template<typename T, std::size_t N>
	struct container_range_traits<T const[N]> {
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_begin(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_end(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_end(arr);
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_size(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_size(arr);
		}
		static SPROUT_CONSTEXPR bool
		range_empty(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_empty(arr);
		}
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_front(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_front(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_back(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_back(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_subscript_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return sprout::container_range_traits<T[N]>::range_subscript_at(arr, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
		range_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return sprout::container_range_traits<T[N]>::range_at(arr, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_nth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
			return sprout::container_range_traits<T[N]>::range_nth(arr, i);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
		range_index_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
			return sprout::container_range_traits<T[N]>::range_index_of(arr, p);
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
		range_data(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_data(arr);
		}
	};
}	// namespace sprout

#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/size.hpp>
#include <sprout/container/front.hpp>
#include <sprout/container/back.hpp>
#include <sprout/container/subscript_at.hpp>
#include <sprout/container/at.hpp>
#include <sprout/container/nth.hpp>
#include <sprout/container/index_of.hpp>
#include <sprout/container/data.hpp>
#include <sprout/container/range_index_check.hpp>

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
