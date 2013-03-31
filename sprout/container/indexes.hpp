#ifndef SPROUT_CONTAINER_INDEXES_HPP
#define SPROUT_CONTAINER_INDEXES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/index_tuple/detail/make_indexes_helper.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// container_indexes
		//
		template<typename Container>
		struct container_indexes
			: public sprout::detail::make_indexes_helper<
				sprout::make_index_tuple<sprout::container_traits<Container>::static_size>
			>
		{};
	}	// namespace containers

	//
	// container_indexes
	//
	template<typename Container>
	struct container_indexes
		: public sprout::containers::container_indexes<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INDEXES_HPP
