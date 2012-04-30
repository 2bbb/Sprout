#ifndef SPROUT_RANGE_RANGE_CONTAINER_HPP
#define SPROUT_RANGE_RANGE_CONTAINER_HPP

#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>

namespace sprout {
	namespace range {
		//
		// range_container
		//
		template<typename Iterator>
		struct range_container
			: public sprout::container_traits<Iterator>
		{
		public:
			typedef Iterator iterator;
			typedef iterator const_iterator;
			typedef typename std::iterator_traits<Iterator>::value_type value_type;
			typedef typename std::iterator_traits<Iterator>::reference reference;
			typedef typename std::remove_reference<reference>::type const& const_reference;
			typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
			typedef typename std::make_unsigned<difference_type>::type size_type;
			typedef typename std::iterator_traits<Iterator>::pointer pointer;
			typedef typename std::remove_pointer<pointer>::type const* const_pointer;
		private:
			iterator first_;
			iterator last_;
		public:
			// construct/copy/destroy:
			range_container() = default;
			SPROUT_CONSTEXPR range_container(iterator first, iterator last)
				: first_(first)
				, last_(last)
			{}

			template<typename Iterator2>
			void swap(range_container<Iterator2>& other) {
				using std::swap;
				swap(other.first_, first_);
				swap(other.last_, last_);
			}
			// iterators:
			SPROUT_CONSTEXPR iterator begin() const {
				return first_;
			}
			SPROUT_CONSTEXPR iterator end() const {
				return last_;
			}
			// capacity:
			SPROUT_CONSTEXPR size_type size() const {
				return sprout::distance(first_, last_);
			}
			SPROUT_CONSTEXPR bool empty() const {
				return first_ == last_;
			}
			// element access:
			SPROUT_CONSTEXPR reference operator[](size_type i) const {
				return *sprout::next(first_, i);
			}
			SPROUT_CONSTEXPR reference at(size_type i) const {
				return i < size() ? *sprout::next(first_, i)
					: (throw std::out_of_range("sprout::range::range_container<>: index out of range"), *sprout::next(first_, i))
					;
			}
			SPROUT_CONSTEXPR reference front() const {
				return *first_;
			}
			SPROUT_CONSTEXPR reference back() const {
				return *sprout::next(first_, size() - 1);
			}
			// others:
			template<typename Iterator2>
			range_container<Iterator>& operator=(range_container<Iterator2> const& rhs) {
				first_ = rhs.first_;
				last_ = rhs.last_;
				return *this;
			}
			template<typename Iterator2>
			range_container<Iterator>& operator=(range_container<Iterator2>&& rhs) {
				first_ = std::move(rhs.first_);
				last_ = std::move(rhs.last_);
				return *this;
			}
		};

		//
		// swap
		//
		template<typename Iterator>
		inline void swap(sprout::range::range_container<Iterator>& lhs, sprout::range::range_container<Iterator>& rhs) {
			lhs.swap(rhs);
		}

		//
		// is_range_container
		//
		template<typename T>
		struct is_range_container
			: public std::false_type
		{};
		template<typename T>
		struct is_range_container<T const>
			: public sprout::range::is_range_container<T>
		{};
		template<typename T>
		struct is_range_container<T volatile>
			: public sprout::range::is_range_container<T>
		{};
		template<typename T>
		struct is_range_container<T const volatile>
			: public sprout::range::is_range_container<T>
		{};
		template<typename Iterator>
		struct is_range_container<sprout::range::range_container<Iterator> >
			: public std::true_type
		{};

		//
		// make_range_container
		//
		template<typename Range>
		inline SPROUT_CONSTEXPR sprout::range::range_container<typename sprout::range::lvalue_iterator<Range>::type>
		make_range_container(Range&& range) {
			return sprout::range::range_container<typename sprout::range::lvalue_iterator<Range>::type>(
				sprout::begin(sprout::forward<Range>(range)),
				sprout::end(sprout::forward<Range>(range))
				);
		}
	}	// namespace range

	//
	// container_traits
	//
	template<typename Iterator>
	struct container_traits<sprout::range::range_container<Iterator> >
		: public sprout::detail::container_traits_default<sprout::range::range_container<Iterator> >
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_RANGE_CONTAINER_HPP
