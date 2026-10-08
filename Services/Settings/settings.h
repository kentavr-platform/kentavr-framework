/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: settings.h
//----------------------------------------------------------------------------------------------*/
#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>
#include <stddef.h>
//------------------------------------------------------------------------------------------------
/**
 * @brief Persistent key-value storage in EEPROM.
 *
 * Settings provides a lightweight EEPROM-backed storage for application
 * configuration data. Values are identified by a user-defined 32-bit key and
 * their binary size.
 *
 * The storage is divided into three regions:
 * - Header area at the beginning of EEPROM.
 * - Data area growing upward from the header.
 * - Index area growing downward from the end of the storage region.
 *
 * Each stored setting consists of:
 * - Raw binary data located in the data area.
 * - An index record containing the key, size, and data address.
 *
 * New settings are appended without relocating existing data. Existing
 * settings with the same key and size are updated in place.
 *
 * @tparam Size Size of the EEPROM storage region in bytes.
 *
 * @note Settings are uniquely identified by the pair (key, size).
 * Settings with the same key but different sizes are treated as different
 * entries.
 *
 * @note The storage uses a simple append-only layout and does not perform
 * garbage collection or compaction.
 *
 * @note The constructor automatically validates the storage header and formats
 * the storage if corruption or an incompatible format is detected.
 *
 * Storage layout:
 * @code
 * +--------------------+
 * | Header             |
 * +--------------------+
 * | Data area          |  grows upward
 * |                    |
 * |      Free space    |
 * |                    |
 * | Index area         |  grows downward
 * +--------------------+
 * @endcode
 */
template <EEPROM_Storage :: offset_t Size>
class Settings
{
public:
    static_assert(Size <= E2END + 1, "Settings size exceeds EEPROM size");
    explicit Settings();
    ResultCode read(uint32_t key, void *data, size_t size);

    template <class Type>
    ResultCode read(uint32_t key, Type &value);

    ResultCode write(uint32_t key, const void *data, size_t size);

    template <class Type>
    ResultCode write(uint32_t key, const Type &value);

    bool is_valid() const;
    void format();
    uint16_t get_free_space() const;
private:
    void _read_header()                 { EEPROM.read(kst_base, &header, sizeof(Header)); }
    void _write_header()                { EEPROM.write(kst_base, &header, sizeof(Header)); }
    using offset_t = EEPROM_Storage :: offset_t;
    static constexpr offset_t kst_base = 0;
    static constexpr offset_t kst_size = Size;
    static constexpr uint32_t MAGIC   = 0x5F31534BUL;   // "KS1_"
    struct __attribute__((packed)) Header
    {
        uint32_t magic;
        uint16_t data_end;
        uint16_t index_end;
        uint16_t entries_count;
        uint8_t reserved[6];
    } header;
    static_assert(sizeof(Header) == 16, "Unexpected header size");
    struct __attribute__((packed)) IndexRecord
    {
        uint32_t key;
        uint16_t size;
        uint16_t addr;
    };
    static_assert(sizeof(IndexRecord) == 8, "Unexpected entry size");
    ResultCode _find(IndexRecord &entry) const;
};
//------------------------------------------------------------------------------------------------
#include "settings.tpp"
//------------------------------------------------------------------------------------------------
#define ENABLE_SETTINGS(Size)                                                    \
    static_assert((Size) <= E2END + 1, "Settings size exceeds EEPROM size");     \
    uint8_t _settings_eeprom_reserved[(Size)] EEMEM __attribute__((used)) = {};  \
    Settings <Size> settings;
//------------------------------------------------------------------------------------------------
#endif
