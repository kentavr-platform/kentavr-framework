#ifndef IS_ENUM_H
#define IS_ENUM_H
//------------------------------------------------------------------------------------------------
template <class Type>
struct is_enum
{
    static constexpr bool value = __is_enum(Type);
};
//------------------------------------------------------------------------------------------------
#endif // IS_ENUM_H
