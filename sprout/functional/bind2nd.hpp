#ifndef SPROUT_FUNCTIONAL_BIND2ND_HPP
#define SPROUT_FUNCTIONAL_BIND2ND_HPP

#include <sprout/config.hpp>
#include <sprout/functional/base.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// D.9.3 Class template binder2nd
	template<typename Fn, typename T = void, typename = void>
	class binder2nd;
	template<typename Fn, typename T>
	class binder2nd<
		Fn, T,
		typename std::enable_if<sprout::is_strict_binary_function<Fn>::value>::type
	>
		: public sprout::unary_function<typename Fn::first_argument_type, typename Fn::result_type>
	{
	public:
		typedef typename std::conditional<
			std::is_void<T>::value,
			typename Fn::second_argument_type,
			T
		>::type value_type;
	protected:
		Fn op;
		value_type value;
	public:
		SPROUT_CONSTEXPR binder2nd(Fn const& x, value_type const& y)
			: op(x), value(y)
		{}
		SPROUT_CONSTEXPR typename Fn::result_type
		operator()(typename Fn::first_argument_type const& x) const {
			return op(x, value);
		}
	};
	template<typename Fn, typename T>
	class binder2nd<
		Fn, T,
		typename std::enable_if<!sprout::is_strict_binary_function<Fn>::value>::type
	> {
	public:
		typedef T value_type;
	protected:
		Fn op;
		value_type value;
	public:
		SPROUT_CONSTEXPR binder2nd(Fn const& x, value_type const& y)
			: op(x), value(y)
		{}
		template<typename U>
		SPROUT_CONSTEXPR decltype(op(std::declval<U const&>(), value))
		operator()(U const& x) const {
			return op(x, value);
		}
	};

	// D.9.3 bind2nd
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder2nd<Fn, T>
	bind2nd(Fn const& fn, T const& x) {
		return sprout::binder2nd<Fn, T>(fn, typename sprout::binder2nd<Fn, T>::value_type(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND2ND_HPP
