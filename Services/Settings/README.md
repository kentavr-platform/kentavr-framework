# Settings

## EEPROM-backed key-value settings storage


### Summary

 - Stores application settings in internal EEPROM
 - Identifies values by `(key, size)`
 - Supports typed and raw binary values
 - Updates existing values in place

The module uses [EEPROM_Storage](../../AVR/EEPROM) internally.


### Enabling

Reserve EEPROM space and create the global `settings` object in `config.h`:
```cpp
ENABLE_SETTINGS(512);
```

`512` is the number of EEPROM bytes reserved for settings.


### Basic usage

```cpp
static constexpr uint32_t KEY_TIMEOUT = 0x1001;
uint16_t timeout = 1000;
settings.write(KEY_TIMEOUT, timeout);
settings.read(KEY_TIMEOUT, timeout);
```

Typed access uses `sizeof(Type)` as part of the setting identity.


### Raw access

```cpp
uint8_t data[] = {1, 2, 3, 4};
uint8_t copy[sizeof(data)];
settings.write(0x2001, data, sizeof(data));
settings.read(0x2001, copy, sizeof(copy));
```

The same key with a different size is treated as a different setting.



## Under the hood

The reserved region contains a header, a data area growing upward, and an index
area growing downward.

Existing settings are updated in place. New `(key, size)` pairs are appended.
There is no garbage collection or compaction.
