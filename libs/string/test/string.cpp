#ifndef SPROUT_LIBS_STRING_TEST_STRING_CPP
#define SPROUT_LIBS_STRING_TEST_STRING_CPP

#include <cstring>
#include <sstream>
#include <type_traits>
#include <sprout/string.hpp>
#include <sprout/container.hpp>
#include <testspr/tools.hpp>

namespace testspr {
	static void string_test() {
		using namespace sprout;
		{
			SPROUT_STATIC_CONSTEXPR char cstr[] = "foobar1234";
			SPROUT_STATIC_CONSTEXPR auto str1 = to_string(cstr);
			SPROUT_STATIC_CONSTEXPR auto str2 = to_string("hogehoge");

			TESTSPR_BOTH_ASSERT((std::is_same<decltype(str1), sprout::basic_string<char, 10> const>::value));
			TESTSPR_BOTH_ASSERT((std::is_same<decltype(str2), sprout::basic_string<char, 8> const>::value));

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
			TESTSPR_BOTH_ASSERT((string_t<0>::type().empty()));

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
				auto s1 = to_string("abc");
				auto s2 = to_string("ABC");
				s1.swap(s2);
				TESTSPR_ASSERT(s1[0] == 'A');
			}

			// assign
			{
				auto s = to_string("abc");
				s.assign(to_string("ABC"));
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = to_string("abc");
				s.assign(to_string("ABC"), 0, 2);
				TESTSPR_ASSERT(s.size() == 2);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = to_string("abc");
				s.assign("ABC", 2);
				TESTSPR_ASSERT(s.size() == 2);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = to_string("abc");
				s.assign("ABC");
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = to_string("abc");
				s.assign(1, 'A');
				TESTSPR_ASSERT(s.size() == 1);
				TESTSPR_ASSERT(s[0] == 'A');
			}

			// operator=
			{
				auto s = to_string("abc");
				s = to_string("ABC");
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = to_string("abc");
				s = "ABC";
				TESTSPR_ASSERT(s.size() == 3);
				TESTSPR_ASSERT(s[0] == 'A');
			}
			{
				auto s = to_string("abc");
				s = 'A';
				TESTSPR_ASSERT(s.size() == 1);
				TESTSPR_ASSERT(s[0] == 'A');
			}

			// find
			TESTSPR_BOTH_ASSERT(str1.find(str2) == decltype(str1)::npos);
			TESTSPR_BOTH_ASSERT(str1.find(to_string("1234")) == 6);
			TESTSPR_BOTH_ASSERT(str1.find(str2.c_str()) == decltype(str1)::npos);
			TESTSPR_BOTH_ASSERT(str1.find("1234") == 6);
			TESTSPR_BOTH_ASSERT(str1.find(str2.c_str(), 0, 4) == decltype(str1)::npos);
			TESTSPR_BOTH_ASSERT(str1.find("12341234", 0, 4) == 6);
			TESTSPR_BOTH_ASSERT(str1.find('1') == 6);

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
			TESTSPR_BOTH_ASSERT(str1.compare(to_string("zzzz")) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(to_string("aaaa")) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, to_string("foo")) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, to_string("zzzz")) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(0, 3, to_string("aaaa")) > 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, to_string("foo"), 0, 3) == 0);
			TESTSPR_BOTH_ASSERT(str1.compare(0, 3, to_string("zzzz"), 0, 3) < 0);
			TESTSPR_BOTH_ASSERT(str2.compare(0, 3, to_string("aaaa"), 0, 3) > 0);
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

			// operator+
			{
#ifdef SPROUT_CONFIG_USE_INDEX_ITERATOR_IMPLEMENTATION
				// ! Error in GCC4.7
				SPROUT_STATIC_CONSTEXPR auto str3 = str1 + to_string("hogehoge");
				TESTSPR_BOTH_ASSERT(str3 == "foobar1234hogehoge");
#endif

				SPROUT_STATIC_CONSTEXPR auto str4 = str1 + str2;
				TESTSPR_BOTH_ASSERT(str4 == "foobar1234hogehoge");
			}

			// operator<<
			{
				std::ostringstream os;
				os << str1;
				TESTSPR_ASSERT(os.str() == cstr);
			}

			// operator>>
			{
				std::istringstream is("hogehoge piyopiyo");
				auto str3 = str1;
				is >> str3;
				TESTSPR_ASSERT(str3 == "hogehoge");
			}

			// string_from_c_str
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = string_from_c_str<10>(cstr);
				TESTSPR_BOTH_ASSERT(str3 == "foobar1234");
			}
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = string_from_c_str<10>(cstr, 6);
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
			}

			// make_string
			{
				SPROUT_STATIC_CONSTEXPR auto str3 = make_string('f', 'o', 'o', 'b', 'a', 'r');
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
				TESTSPR_BOTH_ASSERT(str3.size() == 6);
			}

			// operator basic_string
			{
				SPROUT_STATIC_CONSTEXPR string_t<10>::type str3 = to_string("foobar");
				TESTSPR_BOTH_ASSERT(str3 == "foobar");
				TESTSPR_BOTH_ASSERT(str3.size() == 6);
			}
		}
	}
}	// namespace testspr

#ifndef TESTSPR_CPP_INCLUDE
#	define TESTSPR_TEST_FUNCTION testspr::string_test
#	include <testspr/include_main.hpp>
#endif

#endif	// #ifndef SPROUT_LIBS_STRING_TEST_STRING_CPP
