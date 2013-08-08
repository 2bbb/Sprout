/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/numeric/dft/fixed/amplitude_spectrum.hpp>

namespace sprout {
	namespace fixed {
		//
		// spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::amplitude_spectrum(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		spectrum(InputIterator first, InputIterator last) {
			return sprout::fixed::amplitude_spectrum<Result>(first, last);
		}
	}	// namespace fixed

	using sprout::fixed::spectrum;
}	// namespace sprout

#include <sprout/numeric/dft/fixed/phase_spectrum.hpp>

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP
