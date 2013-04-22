#ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
#define SPROUT_GENERATOR_NEXT_GENERATOR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/generator/generator_access_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl next_generator(...);
}	// namespace sprout_adl

namespace sprout_generator_detail {
	using sprout_adl::next_generator;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::next_generator(std::declval<Gen&>()))
	next_generator(Gen& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen>::next_generator(std::declval<Gen&>())))
	{
		return sprout::generators::generator_access_traits<Gen>::next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::next_generator(std::declval<Gen&&>()))
	>::type
	next_generator(Gen&& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::next_generator(std::declval<Gen&&>())))
	{
		return sprout::generators::generator_access_traits<Gen>::next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen const>::next_generator(std::declval<Gen const&>()))
	next_generator(Gen const& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen const>::next_generator(std::declval<Gen const&>())))
	{
		return sprout::generators::generator_access_traits<Gen const>::next_generator(gen);
	}

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(next_generator(std::declval<Gen&>()))
	call_next_generator(Gen& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(next_generator(std::declval<Gen&>())))
	{
		return next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(next_generator(std::declval<Gen&&>()))
	>::type
	call_next_generator(Gen&& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(next_generator(std::declval<Gen&&>())))
	{
		return next_generator(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(next_generator(std::declval<Gen const&>()))
	call_next_generator(Gen const& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(next_generator(std::declval<Gen const&>())))
	{
		return next_generator(gen);
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// next_generator
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_next_generator(std::declval<T>()))
		next_generator(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout_generator_detail::call_next_generator(std::declval<T>())))
		{
			return sprout_generator_detail::call_next_generator(sprout::forward<T>(t));
		}
	}	// namespace generators

	using sprout::generators::next_generator;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_NEXT_GENERATOR_HPP
