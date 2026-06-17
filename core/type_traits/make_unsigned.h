#ifndef MAKE_UNSIGNED_H
#define MAKE_UNSIGNED_H
//------------------------------------------------------------------------------------------------
template <class Type>
struct make_unsigned;

template <> struct make_unsigned <char>               { using type = unsigned char; };
template <> struct make_unsigned <signed char>        { using type = unsigned char; };
template <> struct make_unsigned <unsigned char>      { using type = unsigned char; };

template <> struct make_unsigned <short>              { using type = unsigned short; };
template <> struct make_unsigned <unsigned short>     { using type = unsigned short; };

template <> struct make_unsigned <int>                { using type = unsigned int; };
template <> struct make_unsigned <unsigned int>       { using type = unsigned int; };

template <> struct make_unsigned <long>               { using type = unsigned long; };
template <> struct make_unsigned <unsigned long>      { using type = unsigned long; };

template <> struct make_unsigned <long long>          { using type = unsigned long long; };
template <> struct make_unsigned <unsigned long long> { using type = unsigned long long; };
//------------------------------------------------------------------------------------------------
#endif
