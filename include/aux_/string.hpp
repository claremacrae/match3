#ifndef STRING_HPP
#define STRING_HPP

template<char...>
struct string { };

template<class T, T... Chars>
constexpr auto operator""_s() {
    return string<Chars...>{};
}

#endif

