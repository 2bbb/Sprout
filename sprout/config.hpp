#ifndef SPROUT_CONFIG_HPP
#define SPROUT_CONFIG_HPP

#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define SPROUT_CONSTEXPR constexpr
#else	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define SPROUT_CONSTEXPR
#endif	// #ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

#ifndef SPROUT_CONFIG_DISABLE_NOEXCEPT
#	define SPROUT_NOEXCEPT noexcept
#	define SPROUT_NOEXCEPT_EXPR(EXPR) noexcept(EXPR)
#else	// #ifndef SPROUT_CONFIG_DISABLE_NOEXCEPT
#	define SPROUT_NOEXCEPT
#	define SPROUT_NOEXCEPT_EXPR(EXPR)
#endif	// #ifndef SPROUT_CONFIG_DISABLE_NOEXCEPT

#ifndef SPROUT_CONFIG_USE_SSCRISK_CEL
#	define HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL <sprout/detail/functional.hpp>
#	define HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL <sprout/detail/algorithm.hpp>
#	define HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL <sprout/detail/iterator.hpp>
#	define NS_SSCRISK_CEL_OR_SPROUT_DETAIL sprout::detail
#else	// #ifndef SPROUT_CONFIG_USE_SSCRISK_CEL
#	define HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT_DETAIL <sscrisk/cel/functional.hpp>
#	define HDR_ALGORITHM_SSCRISK_CEL_OR_SPROUT_DETAIL <sscrisk/cel/algorithm.hpp>
#	define HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL <sscrisk/cel/iterator.hpp>
#	define NS_SSCRISK_CEL_OR_SPROUT_DETAIL sscrisk::cel
#endif	// #ifndef SPROUT_CONFIG_USE_SSCRISK_CEL

#endif	// #ifndef SPROUT_CONFIG_HPP
