#ifndef SPROUT_LIBS_UTILITY_STRING_REF_TEST_STRING_REF_CPP
#define SPROUT_LIBS_UTILITY_STRING_REF_TEST_STRING_REF_CPP

#include <sstream>
#include <type_traits>
#include <sprout/utility/string_ref.hpp>
#include <sprout/string.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void string_ref_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char cstr[] = "foobar1234";
			SPROUT_STATIC_CONSTEXPR auto s = sprout::to_string("hogehoge");
			SPROUT_STATIC_CONSTEXPR auto str1 = sprout::string_ref(cstr);
			SPROUT_STATIC_CONSTEXPR auto str2 = sprout::string_ref(s);

			// begin
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.begin());

			// cbegin
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.cbegin());

			// end
			TESTSPR_BOTH_ASSERT(cstr[9] == *(str1.end() - 1));

			// cend
			TESTSPR_BOTH_ASSERT(cstr[9] == *(str1.cend() - 1));

			// rbegin
			TESTSPR_BOTH_ASSERT(cstr[9] == *str1.rbegin());

			// crbegin
			TESTSPR_BOTH_ASSERT(cstr[9] == *str1.crbegin());

			// rend
			TESTSPR_BOTH_ASSERT(cstr[0] == *(str1.rend() - 1));

			// crend
			TESTSPR_BOTH_ASSERT(cstr[0] == *(str1.crend() - 1));

			// size
			TESTSPR_BOTH_ASSERT(str1.size() == 10);

			// empty
			TESTSPR_BOTH_ASSERT(!str1.empty());
			TESTSPR_BOTH_ASSERT((sprout::string_ref().empty()));

			// max_size
			TESTSPR_BOTH_ASSERT(str1.max_size() == 10);

			// operator[]
			TESTSPR_BOTH_ASSERT(cstr[0] == str1[0]);

			// at
			TESTSPR_BOTH_ASSERT(cstr[0] == str1.at(0));

			// front
			TESTSPR_BOTH_ASSERT(cstr[0] == str1.front());

			// back
			TESTSPR_BOTH_ASSERT(cstr[9] == str1.back());

			// data
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.data());

			// c_str
			TESTSPR_BOTH_ASSERT(cstr[0] == *str1.c_str());

			// swap
			{
				auto s1 = sprout::string_ref("abc");
				auto s2 = sprout::string_ref("ABC");
				s1.swap(s2);
				TESTSPR_ASSERT(s1[0] == 'A');
			}

			// operator=
			{
				auto s = sprout::string_ref("abc");
				s = sprout::string_ref("ABC");
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s = "ABC";
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = sprout::to_string("abc");
				s = 'A';
				TESTSPR_ASSERT(s.size() == 1);
				TESTSPR_ASSERT(s[0] == 'A');
			}

			// find
			TESTSPR_BOTH_ASSERT(str1.find(str2) == npos);
			TESTSPR_BOTH_ASSERT(str1.find(sprout::string_ref("bar")) == 3);
			TESTSPR_BOTH_ASSERT(str1.find(str2.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.find("bar") == 3);
			TESTSPR_BOTH_ASSERT(str1.find(str2.c_str(), 0, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.find("barbar", 0, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.find('b') == 3);

			// rfind
			TESTSPR_BOTH_ASSERT(str1.rfind(str2) == npos);
			TESTSPR_BOTH_ASSERT(str1.rfind(sprout::string_ref("bar")) == 3);
			TESTSPR_BOTH_ASSERT(str1.rfind(str2.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.rfind("bar") == 3);
			TESTSPR_BOTH_ASSERT(str1.rfind(str2.c_str(), npos, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.rfind("barbar", npos, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.rfind('b') == 3);

			// find_first_of
			TESTSPR_BOTH_ASSERT(str1.find_first_of(sprout::string_ref("vwxyz")) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_of(sprout::string_ref("rab")) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("vwxyz") == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("rab") == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("vwxyz", 0, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_of("rabrab", 0, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_of('b') == 3);

			// find_last_of
			TESTSPR_BOTH_ASSERT(str1.find_last_of(sprout::string_ref("vwxyz")) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_of(sprout::string_ref("rab")) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("vwxyz") == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("rab") == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("vwxyz", npos, 3) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_of("rabrab", npos, 3) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_of('r') == 5);

			// find_first_not_of
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(str1) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(sprout::string_ref("foo")) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(str1.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of("foo") == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of(str1.c_str(), 0, 10) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of("foofoo", 0, 3) == 3);
			TESTSPR_BOTH_ASSERT(str1.find_first_not_of('f') == 1);

			// find_last_not_of
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(str1) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(sprout::string_ref("4321")) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(str1.c_str()) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of("4321") == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of(str1.c_str(), npos, 10) == npos);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of("43214321", npos, 4) == 5);
			TESTSPR_BOTH_ASSERT(str1.find_last_not_of('4') == 8);

			// substr
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = str1.substr();
				TESTSPR_BOTH_ASSERT(str3 == "foobar1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = str1.substr(6);
				TESTSPR_BOTH_ASSERT(str3 == "1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = str1.substr(0, 6);
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
			}

			// compare
			TESTSPR_BOTH_ASSERT(str1.compare(str1) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(sprout::string_ref("zzzz")) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(sprout::string_ref("aaaa")) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::string_ref("foo")) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::string_ref("zzzz")) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(0, 3, sprout::string_ref("aaaa")) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::string_ref("foo"), 0, 3) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, sprout::string_ref("zzzz"), 0, 3) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(0, 3, sprout::string_ref("aaaa"), 0, 3) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(str1.c_str()) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare("zzzz") < 0);
			TESTSPR_BOTH_ASSERT(str1.compare("aaaa") > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "foo") == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "zzzz") < 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "aaaa") > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "foo", 3) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "zzzz", 3) < 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, "aaaa", 3) > 0);

			// operator==
			TESTSPR_BOTH_ASSERT(!(str1 == str2));

			// operator!=
			TESTSPR_BOTH_ASSERT(str1 != str2);

			// operator<
			TESTSPR_BOTH_ASSERT(str1 < str2);

			// operator>
			TESTSPR_BOTH_ASSERT(!(str1 > str2));

			// operator<=
			TESTSPR_BOTH_ASSERT(str1 <= str2);

			// operator>=
			TESTSPR_BOTH_ASSERT(!(str1 >= str2));

			// operator<<
			{
				std::ostringstream os;
				os << str1;
				TESTSPR_ASSERT(os.str() == cstr);
			}

			// is_string_ref
			TESTSPR_BOTH_ASSERT(sprout::is_string_ref<decltype(str1)>::value);
			TESTSPR_BOTH_ASSERT(!sprout::is_string_ref<int>::value);

			// sprout::to_hash, sprout::hash
			TESTSPR_BOTH_ASSERT(sprout::to_hash(str1) == sprout::hash<decltype(str1)>()(str1));
			TESTSPR_BOTH_ASSERT(sprout::to_hash(str1) != sprout::to_hash(str2));
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::string_ref_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_UTILITY_STRING_REF_TEST_STRING_REF_CPP
