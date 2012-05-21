#ifndef SPROUT_FUNCTIONAL_REF_HPP
#define SPROUT_FUNCTIONAL_REF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/has_xxx.hpp>
#include <sprout/type_traits/inherit_if_xxx.hpp>
#include <sprout/functional/base.hpp>
#include <sprout/functional/weak_result_type.hpp>

namespace sprout {
	// 20.8.3 reference_wrapper

	namespace detail {
		template<bool Unary, bool Binary, typename T>
		struct reference_wrapper_base_impl;
		template<typename T>
		struct reference_wrapper_base_impl<false, false, T>
			: public sprout::weak_result_type<T>
		{};
		template<typename T>
		struct reference_wrapper_base_impl<true, false, T>
			: public sprout::weak_result_type<T>
		{
		public:
			typedef typename T::argument_type argument_type;
		};
		template<typename T>
		struct reference_wrapper_base_impl<false, true, T>
			: public sprout::weak_result_type<T>
		{
		public:
			typedef typename T::first_argument_type first_argument_type;
			typedef typename T::second_argument_type second_argument_type;
		};
			template<typename T>
		struct reference_wrapper_base_impl<true, true, T>
			: public sprout::weak_result_type<T>
		{
		public:
			typedef typename T::argument_type argument_type;
			typedef typename T::first_argument_type first_argument_type;
			typedef typename T::second_argument_type second_argument_type;
		};
		template<typename T>
		struct reference_wrapper_base
			: public sprout::detail::reference_wrapper_base_impl<
				sprout::detail::has_argument_type<T>::value,
				sprout::detail::has_first_argument_type<T>::value
					&& sprout::detail::has_second_argument_type<T>::value
					,
				T
			>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res(T1)>
			: public sprout::unary_function<T1, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res(T1) const>
			: public sprout::unary_function<T1, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res(T1) volatile>
			: public sprout::unary_function<T1, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res(T1) const volatile>
			: public sprout::unary_function<T1, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res(T1, T2)>
			: public sprout::binary_function<T1, T2, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res(T1, T2) const>
			: public sprout::binary_function<T1, T2, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res(T1, T2) volatile>
			: public sprout::binary_function<T1, T2, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res(T1, T2) const volatile>
			: public sprout::binary_function<T1, T2, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res(*)(T1)>
			: public sprout::unary_function<T1, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res(*)(T1, T2)>
			: public sprout::binary_function<T1, T2, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res (T1::*)()>
			: public sprout::unary_function<T1*, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res (T1::*)(T2)>
			: public sprout::binary_function<T1*, T2, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res (T1::*)() const>
			: public sprout::unary_function<T1 const*, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res (T1::*)(T2) const>
			: public sprout::binary_function<T1 const*, T2, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res (T1::*)() volatile>
			: public sprout::unary_function<T1 volatile*, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res (T1::*)(T2) volatile>
			: public sprout::binary_function<T1 volatile*, T2, Res>
		{};
		template<typename Res, typename T1>
		struct reference_wrapper_base<Res (T1::*)() const volatile>
			: public sprout::unary_function<T1 const volatile*, Res>
		{};
		template<typename Res, typename T1, typename T2>
		struct reference_wrapper_base<Res (T1::*)(T2) const volatile>
			: public sprout::binary_function<T1 const volatile*, T2, Res>
		{};
	}	// namespace detail

	template<typename T>
	class reference_wrapper
		: public sprout::detail::reference_wrapper_base<typename std::remove_cv<T>::type>
	{
	public:
		// types
		typedef T type;
	private:
		T* t_;
	public:
		// construct/copy/destroy
		SPROUT_CONSTEXPR reference_wrapper(T& t) SPROUT_NOEXCEPT
			: t_(&t)
		{}
		reference_wrapper(T&&) = delete;
		reference_wrapper(reference_wrapper<T> const&) SPROUT_NOEXCEPT = default;
		// assignment
		reference_wrapper& operator=(reference_wrapper<T> const&) SPROUT_NOEXCEPT = default;
		// access
		SPROUT_CONSTEXPR operator T& () const SPROUT_NOEXCEPT {
			return *t_;
		}
		SPROUT_CONSTEXPR T& get() const SPROUT_NOEXCEPT {
			return *t_;
		}
		SPROUT_CONSTEXPR T* get_pointer() const SPROUT_NOEXCEPT {
			return t_;
		}
		// invocation
		template<typename... Args>
		SPROUT_CONSTEXPR typename std::result_of<T& (Args&&...)>::type
		operator() (Args&&... args) const {
			return (*t_)(sprout::forward<Args>(args)...);
		}
	};

	//
	// ref
	// cref
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::reference_wrapper<T> ref(T& t) SPROUT_NOEXCEPT {
		return sprout::reference_wrapper<T>(t);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::reference_wrapper<T const> cref(T const& t) SPROUT_NOEXCEPT {
		return sprout::reference_wrapper<T const>(t);
	}
	template<typename T>
	void ref(T const&&) = delete;
	template<typename T>
	void cref(T const&&) = delete;
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::reference_wrapper<T> ref(sprout::reference_wrapper<T> t) SPROUT_NOEXCEPT {
		return t;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::reference_wrapper<T const> cref(sprout::reference_wrapper<T> t) SPROUT_NOEXCEPT {
		return sprout::reference_wrapper<T const>(t.get());
	}

	//
	// is_reference_wrapper
	//
	template<typename T>
	struct is_reference_wrapper
		: public std::false_type
	{};
	template<typename T>
	struct is_reference_wrapper<T const>
		: public sprout::is_reference_wrapper<T>
	{};
	template<typename T>
	struct is_reference_wrapper<T volatile>
		: public sprout::is_reference_wrapper<T>
	{};
	template<typename T>
	struct is_reference_wrapper<T const volatile>
		: public sprout::is_reference_wrapper<T>
	{};
	template<typename T>
	struct is_reference_wrapper<sprout::reference_wrapper<T> >
		: public std::true_type
	{};

	//
	// unwrap_reference
	//
	template<typename T>
	struct unwrap_reference {
	public:
		typedef T type;
	};
	template<typename T>
	struct unwrap_reference<sprout::reference_wrapper<T> > {
	public:
		typedef T type;
	};
	template<typename T>
	struct unwrap_reference<T const>
		: public sprout::unwrap_reference<T>
	{};
	template<typename T>
	struct unwrap_reference<T volatile>
		: public sprout::unwrap_reference<T>
	{};
	template<typename T>
	struct unwrap_reference<T const volatile>
		: public sprout::unwrap_reference<T>
	{};

	//
	// strip_reference
	//
	template<typename T>
	struct strip_reference {
	public:
		typedef T type;
	};
	template<typename T>
	struct strip_reference<sprout::reference_wrapper<T> > {
	public:
		typedef T& type;
	};
	template<typename T>
	struct strip_reference<T const>
		: public sprout::strip_reference<T>
	{};
	template<typename T>
	struct strip_reference<T volatile>
		: public sprout::strip_reference<T>
	{};
	template<typename T>
	struct strip_reference<T const volatile>
		: public sprout::strip_reference<T>
	{};

	//
	// unwrap_ref
	//
	template<typename T>
	inline typename sprout::unwrap_reference<T>::type& unwrap_ref(T& t) {
		return t;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::unwrap_reference<T const>::type& unwrap_ref(T const& t) {
		return t;
	}

	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T* get_pointer(sprout::reference_wrapper<T> const& r) {
		return r.get_pointer();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_REF_HPP
