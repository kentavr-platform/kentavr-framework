# EEPROM
## Internal EEPROM storage wrapper for AVR microcontrollers


### Summary

 - Wraps EEPROM routines in a small storage-style API
 - Provides raw block reads and writes
 - Provides typed reads and writes for trivially copyable values
 - Uses `eeprom_update_*` functions for writes, avoiding unnecessary EEPROM cell rewrites
 - Exposes a global `EEPROM` object for common use

The module is available through:
```cpp
#include "AVR/EEPROM/avr-eeprom.h"
```

It is also included by `core.h`.


### Typical usage and definitions

Any of the following code styles may be used.


#### Object-like style
```cpp
uint16_t value = 1234;
EEPROM.write(0, value);
EEPROM.read(0, value);
```



#### Static style
```cpp
uint16_t value = 1234;
EEPROM_Storage :: write(0, value);
EEPROM_Storage :: read(0, value);
```


### Basic workflow
1. Choose an EEPROM address.
2. Write a typed value or a raw byte block.
3. Read it back using the same type or size.
4. Keep your own EEPROM address map, or use the higher-level Settings module.

> [!WARNING]
> The wrapper does not reserve addresses and does not check for overlapping user data.
> Application code must keep EEPROM layout consistent.



### Typed access

Write and read a value:
```cpp
struct Config
{
    uint16_t timeout_ms;
    uint8_t mode;
};
Config cfg = {1000, 2};
EEPROM.write(0, cfg);
EEPROM.read(0, cfg);
```

Typed access stores the binary representation of the object:
```cpp
EEPROM.write(address, value);   // writes sizeof(value) bytes
EEPROM.read(address, value);    // reads sizeof(value) bytes
```

> [!WARNING]
> Typed access is intended for plain binary data.
> Do not store pointers or objects whose meaning depends on runtime addresses.


### Raw block access

Write and read a byte block:
```cpp
uint8_t data[] = {1, 2, 3, 4};
uint8_t copy[sizeof(data)];
EEPROM.write(16, data, sizeof(data));
EEPROM.read(16, copy, sizeof(copy));
```

Raw access uses a byte address and an explicit size:
```cpp
EEPROM.write(address, data, size);
EEPROM.read(address, data, size);
```


### Address type

EEPROM addresses use:
```cpp
EEPROM_Storage :: offset_t
```

Currently this is `uint16_t`.

The valid EEPROM address range depends on the selected MCU and is defined by
avr-libc as:
```cpp
0 ... E2END
```

> [!WARNING]
> The wrapper does not validate that `addr + size` fits into EEPROM.
> Passing an invalid range is a programming error.



### Erasing EEPROM

Erase the whole internal EEPROM by writing `0xFF` to every EEPROM cell:
```cpp
EEPROM.erase();
```

This iterates from address `0` to `E2END`.

> [!WARNING]
> `erase()` updates the whole EEPROM and can take noticeable time.
> EEPROM has limited write endurance; do not erase it repeatedly in a fast loop.



### Result codes

All current methods return `OK` after calling the underlying avr-libc EEPROM
routine:

| Method | Result |
|---|---|
| `read(...)` | `OK` |
| `write(...)` | `OK` |

The API uses `ResultCode` for compatibility with higher-level storage modules.


### Settings module

For structured application settings prefer the higher-level [Settings](../../core/settings) module:

`Settings` uses `EEPROM_Storage` internally and manages a small key-value layout
inside a reserved EEPROM region.



## Under the hood

`EEPROM_Storage` is a stateless class around avr-libc functions:
```cpp
eeprom_read_block(...)
eeprom_update_block(...)
eeprom_update_byte(...)
```

Writes use update operations, so EEPROM cells are written only when the new
value differs from the stored value.

The module also defines a global object:
```cpp
inline EEPROM_Storage EEPROM;
```

This allows object-like calls without allocating any per-instance state.
