#ifndef SPROUT_PIT_HPP
#define SPROUT_PIT_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator.hpp>
#include <sprout/iterator/value_iterator.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	//
	// pit
	//
	template<typename Container>
	class pit {
	public:
		typedef Container container_type;
		typedef typename sprout::container_traits<container_type>::value_type value_type;
		typedef typename sprout::container_traits<container_type>::reference reference;
		typedef typename sprout::container_traits<container_type>::const_reference const_reference;
		typedef typename sprout::value_iterator<reference> iterator;
		typedef typename sprout::value_iterator<const_reference> const_iterator;
		typedef typename sprout::container_traits<container_type>::size_type size_type;
		typedef typename sprout::container_traits<container_type>::difference_type difference_type;
		typedef typename sprout::container_traits<container_type>::pointer pointer;
		typedef typename sprout::container_traits<container_type>::const_pointer const_pointer;
		typedef typename sprout::reverse_iterator<iterator> reverse_iterator;
		typedef typename sprout::reverse_iterator<const_iterator> const_reverse_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = sprout::container_traits<container_type>::static_size;
	public:
		value_type elem;
	public:
		pit() = default;
		void swap(pit& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<value_type&>(), std::declval<value_type&>()))) {
			using std::swap;
			swap(elem, other.elem);
		}
		// iterators:
		iterator begin() {
			return iterator(elem, static_size);
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return const_iterator(elem, static_size);
		}
		iterator end() SPROUT_NOEXCEPT {
			return iterator();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return const_iterator();
		}
		reverse_iterator rbegin() SPROUT_NOEXCEPT {
			return reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		reverse_iterator rend() SPROUT_NOEXCEPT {
			return reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(elem, static_size);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator();
		}
		SPROUT_CONSTEXPR const_reverse_iterator crbegin() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(end());
		}
		SPROUT_CONSTEXPR const_reverse_iterator crend() const SPROUT_NOEXCEPT {
			return const_reverse_iterator(begin());
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return static_size;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return size();
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return static_size == 0;
		}
		// element access:
		reference operator[](size_type i) {
			return elem;
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return elem;
		}
		reference at(size_type i) {
			return i < size()
				? elem
				: (throw std::out_of_range("pit<>: index out of range"), elem)
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size()
				? elem
				: (throw std::out_of_range("pit<>: index out of range"), elem)
				;
		}
		reference front() {
			return elem;
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return elem;
		}
		reference back() {
			return elem;
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return elem;
		}
		// others:
		void rangecheck(size_type i) const {
			if (i >= size()) {
				throw std::out_of_range("pit<>: index out of range");
			}
		}
	};
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::pit<Container>::size_type sprout::pit<Container>::static_size;

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator==(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return lhs.front() == rhs.front();
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator!=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator<(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return lhs.front() < rhs.front();
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator>(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return rhs < lhs;
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator<=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Container>
	SPROUT_CONSTEXPR inline bool operator>=(sprout::pit<Container> const& lhs, sprout::pit<Container> const& rhs) {
		return !(lhs < rhs);
	}

	//
	// swap
	//
	template<typename Container>
	inline void swap(sprout::pit<Container>& lhs, sprout::pit<Container>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::pit<Container> > {
	public:
		typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type deep_copy(Cont&& cont) {
			return copied_type();
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type remake(
			Cont&& cont,
			typename sprout::container_traits<sprout::pit<Container> >::difference_type size,
			Args&&... args
			)
		{
			return sprout::remake<Container>(sprout::forward<Cont>(cont), size, sprout::forward<Args>(args)...);
		}
	};

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits<sprout::pit<Container> > {
	public:
		template<typename sprout::container_traits<sprout::pit<Container> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::pit<
				typename sprout::container_transform_traits<Container>::template rebind_size<Size>::type
			> type;
		};
	};
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename Container>
	struct tuple_size<sprout::pit<Container> >
		: public std::tuple_size<Container>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::pit<Container> >
		: public std::tuple_element<I, Container>
	{};
}	// namespace std

#endif	// #ifndef SPROUT_PIT_HPP
