#ifndef SPROUT_TYPE_STRING_ALIAS_HPP
#define SPROUT_TYPE_STRING_ALIAS_HPP

#include <sprout/config.hpp>
#include <sprout/type/string/string.hpp>

#if SPROUT_USE_TEMPLATE_ALIASES

namespace sprout {
	namespace types {
		//
		// string
		//
		template<char... Values>
		using string = sprout::types::basic_string<char, Values...>;
		//
		// wstring
		//
		template<wchar_t... Values>
		using wstring = sprout::types::basic_string<wchar_t, Values...>;
		//
		// u16string
		//
		template<char... Values>
		using u16string = sprout::types::basic_string<char16_t, Values...>;
		//
		// string
		//
		template<char... Values>
		using u32string = sprout::types::basic_string<char32_t, Values...>;
	}	// namespace types
}	// namespace sprout

#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#endif	// #ifndef SPROUT_TYPE_STRING_ALIAS_HPP
