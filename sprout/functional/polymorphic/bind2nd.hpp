#ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND2ND_HPP
#define SPROUT_FUNCTIONAL_POLYMORPHIC_BIND2ND_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// binder2nd_
	// bind2nd_
	//
	template<typename Fn, typename T>
	class binder2nd_ {
	protected:
		Fn op;
		T value;
	public:
		SPROUT_CONSTEXPR binder2nd_(Fn&& x, T&& y)
			: op(sprout::forward<Fn>(x)), value(sprout::forward<T>(y))
		{}
		template<typename Arg>
		SPROUT_CONSTEXPR decltype(op(std::declval<Arg>(), value))
		operator()(Arg&& x)
		const SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(op(std::declval<Arg>(), value)))
		{
			return op(sprout::forward<Arg>(x), value);
		}
	};
	template<typename Fn, typename T>
	inline SPROUT_CONSTEXPR sprout::binder2nd_<typename std::decay<Fn>::type, typename std::decay<T>::type>
	bind2nd_(Fn&& fn, T&& x) {
		typedef sprout::binder2nd_<typename std::decay<Fn>::type, typename std::decay<T>::type> type;
		return type(sprout::forward<Fn>(fn), sprout::forward<T>(x));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_POLYMORPHIC_BIND2ND_HPP
