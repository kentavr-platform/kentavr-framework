#ifndef IS_INTEGER_H
#define IS_INTEGER_H
//------------------------------------------------------------------------------------------------
template <class Type>
struct is_integer : false_type {};
//------------------------------------------------------------------------------------------------
template <> struct is_integer <char>                : true_type {};
template <> struct is_integer <signed char>         : true_type {};
template <> struct is_integer <unsigned char>       : true_type {};

template <> struct is_integer <short>               : true_type {};
template <> struct is_integer <unsigned short>      : true_type {};

template <> struct is_integer <int>                 : true_type {};
template <> struct is_integer <unsigned int>        : true_type {};

template <> struct is_integer <long>                : true_type {};
template <> struct is_integer <unsigned long>       : true_type {};

template <> struct is_integer <long long>           : true_type {};
template <> struct is_integer <unsigned long long>  : true_type {};
//------------------------------------------------------------------------------------------------
#endif // IS_INTEGER_H
