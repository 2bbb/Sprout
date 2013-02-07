#ifndef SPROUT_OPERATION_FIT_PUSH_FRONT_N_HPP
#define SPROUT_OPERATION_FIT_PUSH_FRONT_N_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/push_front_n.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// push_front_n
			//
			template<std::size_t N, typename Container, typename T, typename... Values>
			struct push_front_n {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::push_front_n<N, Container, T, Values...>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// push_front_n
		//
		template<std::size_t N, typename Container, typename T, typename... Values>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::push_front_n<N, Container, T, Values...>::type
		push_front_n(Container const& cont, T const& v, Values const&... values) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::push_front_n<N>(cont, v, values...)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) + (1 + sizeof...(Values)) * N
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_PUSH_FRONT_N_HPP
