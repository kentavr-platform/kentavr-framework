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
#define VAR(var)    DebugDEC <decltype(var)> {_flash(#var), var}
#define REG(reg)    DebugHEX <decltype(reg)> {_flash(#reg), reg}
//------------------------------------------------------------------------------------------------
#endif // DEBUG_H
