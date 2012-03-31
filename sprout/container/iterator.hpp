#ifndef SPROUT_CONTAINER_ITERATOR_HPP
#define SPROUT_CONTAINER_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// iterator
		//
		template<typename Container>
		struct iterator {
		public:
			typedef typename sprout::container_traits<Container>::iterator type;
		};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_ITERATOR_HPP
