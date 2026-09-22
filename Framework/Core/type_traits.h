/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: type_traits.h
//----------------------------------------------------------------------------------------------*/
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H
//------------------------------------------------------------------------------------------------
struct true_type  { static constexpr bool value = true;  };
struct false_type { static constexpr bool value = false; };
//------------------------------------------------------------------------------------------------
#include "type_traits/is_integer.h"
#include "type_traits/is_floating.h"
#include "type_traits/is_number.h"
#include "type_traits/is_string.h"
#include "type_traits/is_pointer.h"
#include "type_traits/is_function.h"
#include "type_traits/is_enum.h"
#include "type_traits/make_unsigned.h"
//------------------------------------------------------------------------------------------------
#endif // TYPE_TRAITS_H
