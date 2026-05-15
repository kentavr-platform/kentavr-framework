#ifndef IS_FUNCTION_H
#define IS_FUNCTION_H
//------------------------------------------------------------------------------------------------
template <class Type>
struct is_function : public false_type {};

template <class Ret, class... Args>
struct is_function <Ret(Args...)> : public true_type {};

template <class Ret, class... Args>
struct is_function <Ret(Args...) const> : public true_type {};

template <class Ret, class... Args>
struct is_function <Ret(Args...) volatile> : public true_type {};

template <class Ret, class... Args>
struct is_function <Ret(Args...) const volatile> : public true_type {};

template <class Ret, class... Args>
struct is_function <Ret(Args..., ...)> : public true_type {};
//------------------------------------------------------------------------------------------------
#endif // IS_POINTER_H
