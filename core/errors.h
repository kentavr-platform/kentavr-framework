#ifndef ERRORS_H
#define ERRORS_H
#include <avr/pgmspace.h>
//------------------------------------------------------------------------------------------------
#define CAT(x,y) x ## y
#define CONCAT(x,y) CAT(x,y)
#define _QUOT(x) #x
#define QUOTE(x) _QUOT(x)
#define PRAGMA(x) _Pragma(#x)
//------------------------------------------------------------------------------------------------
#define ERROR_LIST      \
    ERR_(NOT_FOUND)     \
    ERR_(NO_MORE)       \
    ERR_(NOT_MODIFIED)  \
    ERR_(NO_SPACE_LEFT) \
    ERR_(REJECTED)      \
    ERR_(INVALID)       \
    ERR_(ABORTED)       \
    ERR_(BUSY)          \
    ERR_(BAD_MODE)      \
    ERR_(BAD_VALUE)     \
    ERR_(BAD_PARAMETER) \
    ERR_(BAD_CHECKSUM)  \
    ERR_(UNKNOWN)
//------------------------------------------------------------------------------------------------
enum ResultCode
{
    OK = 0,
    #define ERR_(name) ERR_##name,
    ERROR_LIST
    #undef ERR_
};
//------------------------------------------------------------------------------------------------
const char PROGMEM err_id[][20] =
{
    "OK",
    #define ERR_(name) QUOTE(CONCAT(ERR_, name)),
    ERROR_LIST
    #undef ERR_
};

//------------------------------------------------------------------------------------------------
#endif // ERRORS_H
