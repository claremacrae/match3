#ifndef MPL_STRING_KU9OMNN6
#define MPL_STRING_KU9OMNN6

#include <boost/mpl/vector.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

//--------------------------------------------------------------------------------
// http://cpp-next.com/archive/2012/10/using-strings-in-c-template-metaprograms/
//--------------------------------------------------------------------------------

#ifndef MPLSTR_MAX_LENGTH
  #define MPLSTR_MAX_LENGTH 32
#endif

#define MPLSTR_PRE(z, n, s) mplstr::push_back_if_c<
#define MPLSTR_POST(z, n, s) , mplstr::char_at(s, n), (n >= sizeof(s))>::type

#define _S(s) \
	BOOST_PP_REPEAT(MPLSTR_MAX_LENGTH, MPLSTR_PRE, s) \
	boost::mpl::string<> \
	BOOST_PP_REPEAT(MPLSTR_MAX_LENGTH, MPLSTR_POST, s)

//----------------------------------------

namespace mplstr
{
	template<class S, char C, bool EOS>
	struct push_back_if_c : boost::mpl::push_back<S, boost::mpl::char_<C>> {};

	template<class S, char C>
	struct push_back_if_c<S, C, true> : S {}; // termination case

	template<int N> constexpr
	char char_at(char const(&s)[N], int i) {
		return ((i >= N) ? '\0' : s[i]);
	}
}

#endif

