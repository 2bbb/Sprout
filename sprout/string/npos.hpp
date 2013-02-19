#ifndef SPROUT_STRING_NPOS_HPP
#define SPROUT_STRING_NPOS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/is_uint.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// npos_t
	// npos
	//
	struct npos_t {
	public:
		template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
		struct get
			: public std::integral_constant<UIntType, UIntType(-1)>
		{};
	public:
		template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
		SPROUT_CONSTEXPR operator UIntType() const {
			return UIntType(-1);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::npos_t npos = {};
	}	// anonymous-namespace

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator==(UIntType const& lhs, sprout::npos_t rhs) {
		return lhs == UIntType(rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::npos_t lhs, UIntType const& rhs) {
		return rhs == lhs;
	}
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::npos_t lhs, sprout::npos_t rhs) {
		return true;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator!=(UIntType const& lhs, sprout::npos_t rhs) {
		return !(lhs == rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::npos_t lhs, UIntType const& rhs) {
		return !(lhs == rhs);
	}
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::npos_t lhs, sprout::npos_t rhs) {
		return !(lhs == rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<(UIntType const& lhs, sprout::npos_t rhs) {
		return lhs < UIntType(rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::npos_t lhs, UIntType const& rhs) {
		return rhs == lhs;
	}
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::npos_t lhs, sprout::npos_t rhs) {
		return false;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>(UIntType const& lhs, sprout::npos_t rhs) {
		return rhs < lhs;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::npos_t lhs, UIntType const& rhs) {
		return rhs < lhs;
	}
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::npos_t lhs, sprout::npos_t rhs) {
		return rhs < lhs;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<=(UIntType const& lhs, sprout::npos_t rhs) {
		return !(rhs < lhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::npos_t lhs, UIntType const& rhs) {
		return !(rhs < lhs);
	}
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::npos_t lhs, sprout::npos_t rhs) {
		return !(rhs < lhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>=(UIntType const& lhs, sprout::npos_t rhs) {
		return !(lhs < rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::npos_t lhs, UIntType const& rhs) {
		return !(lhs < rhs);
	}
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::npos_t lhs, sprout::npos_t rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_NPOS_HPP
