#ifndef SPROUT_COMPOST_UTILITY_ROSENBERG_HPP
#define SPROUT_COMPOST_UTILITY_ROSENBERG_HPP

#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/math/comparison.hpp>

namespace sprout {
	namespace compost {
		//
		// rosenberg_value
		//	Rosenberg �g�́C����J����ƕ�����������40%�C16%�ƂȂ��Ώ̌`�̔g�`�ł���C��1 ���J����C��2�������������D
		//
		template<typename T>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<T>::type
		rosenberg_value(T x, T tau1, T tau2) {
			typedef typename sprout::float_promote<T>::type type;
			return x >= 0 && x <= tau1
					? 3 * sprout::detail::pow2<type>(x / tau1) - 2 * sprout::detail::pow3<type>(x / tau1)
				: x > tau1 && x <= tau1 + tau2
					? 1 - sprout::detail::pow2<type>((x - tau1) / tau2)
				: 0
				;
		}
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_UTILITY_ROSENBERG_HPP
