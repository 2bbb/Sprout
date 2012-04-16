#ifndef SPROUT_CTYPE_WASCII_HPP
#define SPROUT_CTYPE_WASCII_HPP

#include <sprout/config.hpp>
#include <sprout/ctype/ascii.hpp>

namespace sprout {
	namespace ascii {
		//
		// iswalnum
		// iswalpha
		// iswblank
		// iswcntrl
		// iswdigit
		// iswgraph
		// iswlower
		// iswprint
		// iswpunct
		// iswspace
		// iswupper
		// iswxdigit
		// towlower
		// towupper
		//
		SPROUT_CTYPE_ASCII_DECL(wchar_t, w)
	}	// namespace ascii

	using sprout::ascii::iswalnum;
	using sprout::ascii::iswalpha;
	using sprout::ascii::iswblank;
	using sprout::ascii::iswcntrl;
	using sprout::ascii::iswdigit;
	using sprout::ascii::iswgraph;
	using sprout::ascii::iswlower;
	using sprout::ascii::iswprint;
	using sprout::ascii::iswpunct;
	using sprout::ascii::iswspace;
	using sprout::ascii::iswupper;
	using sprout::ascii::iswxdigit;
	using sprout::ascii::towlower;
	using sprout::ascii::towupper;
}	// namespace sprout

#endif	// #ifndef SPROUT_CTYPE_WASCII_HPP
