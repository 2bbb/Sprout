#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_NEGATE_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_NEGATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace result_of {
				//
				// negate
				//
				template<typename T, typename = void>
				struct negate;
				// -unused -> unused
				template<typename T>
				struct negate<
					T,
					typename std::enable_if<
						sprout::weed::traits::is_unused<T>::value
					>::type
				> {
				public:
					typedef sprout::weed::unused type;
				};
			}	// namespace result_of
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_NEGATE_HPP
