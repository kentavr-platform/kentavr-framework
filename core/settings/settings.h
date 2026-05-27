#ifndef SETTINGS_H
#define SETTINGS_H
#include <stdint.h>
#include <stddef.h>
//------------------------------------------------------------------------------------------------
// reserve whole EEPROM to prevent other allocations
EEMEM uint8_t _settings_storage[E2END + 1];
//------------------------------------------------------------------------------------------------
template <class Storage>
class Settings
{
public:
    using offset_t = typename Storage :: offset_t;
    Settings(Storage &storage, offset_t base, offset_t size)
        : storage(storage), kst_base(base), kst_size(size)              { _read_header(); }


    ResultCode read(uint32_t key, void *data, size_t size);
    ResultCode write(uint32_t key, const void *data, size_t size);

    void clear();

//private:
    static constexpr uint32_t MAGIC   = 0x3154534BUL;   // "KST1"
    struct __attribute__((packed)) Header
    {
        uint32_t magic;
        uint16_t data_end;
        uint16_t index_end;
        uint16_t entries_count;
        uint8_t reserved[6];
    } header;
    static_assert(sizeof(Header) == 16, "Unexpected header size");
    struct __attribute__((packed)) Index_Record
    {
        uint32_t key;
        uint16_t addr;
        uint16_t size;
    };
    static_assert(sizeof(Index_Record) == 8, "Unexpected entry size");

    void _read_header()              { storage.read(kst_base, &header, sizeof(Header)); }
    void _write_header()             { storage.write(kst_base, &header, sizeof(Header)); }
    void _add_index(uint16_t addr, const Index_Record &record);
    bool _validate_header() const;
    uint16_t get_free_space() const         { return header.index_end - header.data_end; }

    ResultCode find(uint32_t key, Index_Record &entry, uint16_t *entry_addr = nullptr) const;



    static void* eeprom_addr(uint16_t offset);
    static const void* eeprom_caddr(uint16_t offset);
    static bool equals_eeprom(uint16_t addr, const void *data, size_t size);
    Storage &storage;
    offset_t kst_base;
    offset_t kst_size;
};
//------------------------------------------------------------------------------------------------
#include "settings.tpp"
//------------------------------------------------------------------------------------------------
#endif
