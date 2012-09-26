#ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
#define SPROUT_GENERATOR_NEXT_GENERATOR_HPP

#include <utility>
#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace generators {
		void next_generator();
	}	// namespace generators
}	// namespace sprout

namespace sprout_generator_detail {
	using sprout::tuples::get;

	template<typename T>
	struct has_spr_next_generator_test {
	public:
		template<
			typename U = T,
			typename = decltype(sprout::generators::next_generator(std::declval<U>()))
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<typename T>
	struct has_spr_next_generator
		: public decltype(sprout_generator_detail::has_spr_next_generator_test<T>::test(0))
	{};

	template<typename T>
	struct has_mem_next_generator_test {
	public:
		template<
			typename U = T,
			typename = decltype(std::declval<U>().next_generator())
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<typename T>
	struct has_mem_next_generator
		: public decltype(sprout_generator_detail::has_mem_next_generator_test<T>::test(0))
	{};

	template<typename T>
	struct has_tuple_get_next_generator_test {
	public:
		template<
			typename U = T,
			typename = decltype(get<1>(std::declval<U>()))
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<typename T>
	struct has_tuple_get_next_generator
		: public decltype(sprout_generator_detail::has_tuple_get_next_generator_test<T>::test(0))
	{};

	template<typename T, typename Enable = void>
	struct select_spr_next_generator;
	template<typename T>
	struct select_spr_next_generator<
		T,
		typename std::enable_if<sprout_generator_detail::has_spr_next_generator<T>::value>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_spr_next_generator<
		T,
		typename std::enable_if<!sprout_generator_detail::has_spr_next_generator<T>::value>::type
	>
		: public std::false_type
	{};

	template<typename T, typename Enable = void>
	struct select_mem_next_generator;
	template<typename T>
	struct select_mem_next_generator<
		T,
		typename std::enable_if<
			sprout_generator_detail::has_mem_next_generator<T>::value
			&& !sprout_generator_detail::has_spr_next_generator<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_mem_next_generator<
		T,
		typename std::enable_if<!(
			sprout_generator_detail::has_mem_next_generator<T>::value
			&& !sprout_generator_detail::has_spr_next_generator<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename Enable = void>
	struct select_tuple_get_next_generator;
	template<typename T>
	struct select_tuple_get_next_generator<
		T,
		typename std::enable_if<
			sprout_generator_detail::has_tuple_get_next_generator<T>::value
			&& !sprout_generator_detail::has_spr_next_generator<T>::value
			&& !sprout_generator_detail::has_mem_next_generator<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_tuple_get_next_generator<
		T,
		typename std::enable_if<!(
			sprout_generator_detail::has_tuple_get_next_generator<T>::value
			&& !sprout_generator_detail::has_spr_next_generator<T>::value
			&& !sprout_generator_detail::has_mem_next_generator<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename = void>
	struct noexcept_next_generator;
//	template<typename T>
//	struct noexcept_next_generator<T, typename std::enable_if<sprout_generator_detail::select_spr_next_generator<T>::value>::type>
//		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(sprout::generators::next_generator(std::declval<T>()), false)>
//	{};
	template<typename T>
	struct noexcept_next_generator<T, typename std::enable_if<sprout_generator_detail::select_mem_next_generator<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(std::declval<T>().next_generator(), false)>
	{};
	template<typename T>
	struct noexcept_next_generator<T, typename std::enable_if<sprout_generator_detail::select_tuple_get_next_generator<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(get<1>(std::declval<T>()), false)>
	{};

	template<typename T, typename = void>
	struct next_generator_result;
//	template<typename T>
//	struct next_generator_result<T, typename std::enable_if<sprout_generator_detail::select_spr_next_generator<T>::value>::type> {
//	public:
//		typedef decltype(sprout::generators::next_generator(std::declval<T>())) type;
//	};
	template<typename T>
	struct next_generator_result<T, typename std::enable_if<sprout_generator_detail::select_mem_next_generator<T>::value>::type> {
	public:
		typedef decltype(std::declval<T>().next_generator()) type;
	};
	template<typename T>
	struct next_generator_result<T, typename std::enable_if<sprout_generator_detail::select_tuple_get_next_generator<T>::value>::type> {
	public:
		typedef decltype(get<1>(std::declval<T>())) type;
	};

//	template<
//		typename T,
//		typename sprout::enabler_if<sprout_generator_detail::select_spr_next_generator<T>::value>::type = sprout::enabler
//	>
//	inline SPROUT_CONSTEXPR typename sprout_generator_detail::next_generator_result<T>::type
//	next_generator_impl(T&& t)
//		SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_next_generator<T>::value))
//	{
//		return sprout::generators::next_generator(sprout::forward<T>(t));
//	}
	template<
		typename T,
		typename sprout::enabler_if<sprout_generator_detail::select_mem_next_generator<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_generator_detail::next_generator_result<T>::type
	next_generator_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_next_generator<T>::value))
	{
		return sprout::forward<T>(t).next_generator();
	}
	template<
		typename T,
		typename sprout::enabler_if<sprout_generator_detail::select_tuple_get_next_generator<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_generator_detail::next_generator_result<T>::type
	next_generator_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_next_generator<T>::value))
	{
		return get<1>(sprout::forward<T>(t));
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// next_generator
		//
		template<typename T>
		inline SPROUT_CONSTEXPR typename sprout_generator_detail::next_generator_result<T>::type
		next_generator(T&& t)
			SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_next_generator<T>::value))
		{
			return sprout_generator_detail::next_generator_impl(sprout::forward<T>(t));
		}
	}	// namespace generators

	using sprout::generators::next_generator;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
