#ifndef SPROUT_OPERATION_FIT_RESIZE_HPP
#define SPROUT_OPERATION_FIT_RESIZE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/operation/fixed/resize.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// resize
			//
			template<std::size_t N, typename Container>
			struct resize {
			public:
				typedef sprout::sub_array<typename sprout::fixed::result_of::resize<N, Container>::type> type;
			};
		}	// namespace result_of

		//
		// resize
		//
		template<std::size_t N, typename Container, typename T>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::resize<N, Container>::type resize(
			Container const& cont,
			T const& v
			)
		{
			return sprout::sub_copy(
				sprout::fixed::resize<N>(cont, v),
				0,
				sprout::fixed_container_traits<typename sprout::fit::result_of::resize<N, Container>::type>::fixed_size
				);
		}

		//
		// resize
		//
		template<std::size_t N, typename Container>
		SPROUT_CONSTEXPR inline typename sprout::fit::result_of::resize<N, Container>::type resize(
			Container const& cont
			)
		{
			return sprout::sub_copy(
				sprout::fixed::resize<N>(cont),
				0,
				sprout::fixed_container_traits<typename sprout::fit::result_of::resize<N, Container>::type>::fixed_size
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_RESIZE_HPP
