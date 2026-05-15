#ifndef IS_FLOATING_H
#define IS_FLOATING_H
//------------------------------------------------------------------------------------------------
template <class Type>
struct is_floating : false_type {};
//------------------------------------------------------------------------------------------------
template <> struct is_floating <float>  : true_type {};
template <> struct is_floating <double> : true_type {};
//------------------------------------------------------------------------------------------------
#endif // IS_FLOATING_H
