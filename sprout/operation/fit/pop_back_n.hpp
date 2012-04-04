#ifndef SPROUT_OPERATION_FIT_POP_BACK_N_HPP
#define SPROUT_OPERATION_FIT_POP_BACK_N_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/pop_back_n.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// pop_back_n
			//
			template<std::size_t N, typename Container>
			struct pop_back_n {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::pop_back_n<N, Container>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// pop_back_n
		//
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::pop_back_n<N, Container>::type pop_back_n(
			Container const& cont
			)
		{
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::pop_back_n<N>(cont)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont) - N
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_POP_BACK_N_HPP
