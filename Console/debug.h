#ifndef DEBUG_H
#define DEBUG_H
//------------------------------------------------------------------------------------------------
template <class Type>
struct DebugDEC
{
    FlashStringWrapper name;
    Type value;
};
//------------------------------------------------------------------------------------------------
template <class Type>
struct DebugHEX
{
    FlashStringWrapper name;
    Type value;
};
//------------------------------------------------------------------------------------------------
// default console-printable value (may be overriten for variable classes)
template <class Type>
__inline Type console_value(const Type &value)     { return value; }
//------------------------------------------------------------------------------------------------
// default Object type-namer = empty string
template <class Type>
FlashStringWrapper console_type_name(const Type &)
{
    return FlashStringWrapper {nullptr};
}
//------------------------------------------------------------------------------------------------
// Object type-namer macro:
#define CONSOLE_TYPE_NAME(Type)                                  \
    __inline FlashStringWrapper console_type_name(const Type &)  \
    {                                                            \
        return _flash(#Type);                                    \
    }

#define SET_CONSOLE_TEMPLATE_TYPE_NAME(Type)                                \
    template <class... Args>                                                \
    __inline FlashStringWrapper console_type_name(const Type <Args...> &)   \
    {                                                                       \
        return _flash(#Type);                                               \
    }
//------------------------------------------------------------------------------------------------
#define VAR(var)    DebugDEC <decltype(console_value(var))> {_flash(#var), var}
#define REG(reg)    DebugHEX <decltype(reg)> {_flash(#reg), reg}
//------------------------------------------------------------------------------------------------
#endif // DEBUG_H
