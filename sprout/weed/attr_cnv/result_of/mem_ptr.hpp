#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_MEM_PTR_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_MEM_PTR_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace result_of {
				//
				// mem_ptr
				//
				template<typename T, typename U, typename = void>
				struct mem_ptr
					: public std::result_of<U(T)>
				{};
			}	// namespace result_of
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_MEM_PTR_HPP
