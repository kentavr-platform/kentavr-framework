#ifndef DS18X20_H
#define DS18X20_H
//------------------------------------------------------------------------------------------------
struct B20_Family
{
    static constexpr bool HAS_CONFIG = true;
    static constexpr bool HIGH_RESOLUTION = true;
    static constexpr bool match_family(uint8_t code)
    {
        switch(code)
        {
        case 0x28:      // DS18B20
        case 0x22:      // DS1822
        case 0x3B:      // DS1825
            return true;
        }
        return false;
    }
    union Scratchpad
    {
        struct __attribute__((packed))
        {
            uint16_t            temperature;    // temperature value
            int8_t              TH;             // alarm over value
            int8_t              TL;             // alarm below value
            uint8_t             config;         // config (resolution)
            uint8_t             reserved[3];
            uint8_t             CRC;            // Dallas CRC8
        };
        uint8_t raw[9];
    };
};
//------------------------------------------------------------------------------------------------
struct S20_Family
{
    static constexpr bool HAS_CONFIG = false;
    static constexpr bool HIGH_RESOLUTION = false;
    static constexpr bool match_family(uint8_t code)
    {
        return code == 0x10;    // DS1820 or DS18S20
    }
    union Scratchpad
    {
        struct __attribute__((packed))
        {
            uint16_t            temperature;    // temperature value
            int8_t              TH;             // alarm over value
            int8_t              TL;             // alarm below value
            uint8_t             reserved[2];
            uint8_t             count_remain;
            uint8_t             count_per_c;
            uint8_t             CRC;            // Dallas CRC8
        };
        uint8_t raw[8];
    };
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Base protocol driver for Dallas 1-Wire temperature sensors.
 *
 * This class implements low-level communication and common operations for
 * DS18x20-compatible sensors (DS1820, DS18B20, DS18S20, etc).
 *
 * @note This class does NOT perform device discovery. ROM addresses must be
 * obtained externally via OneWireBus search functions.
 */
template <class Bus, class Family>
class Protocol_DS18x20
{
    static_assert(is_OneWireBus <Bus> :: value, "Invalid bus! This driver supports OneWireBus only.");
public:
    explicit    Protocol_DS18x20(Bus &bus, const OneWireAddress &addr) : bus(bus),
                                                                             address(addr),
                                                                             has_address(true) {};
    bool            is_valid();
    ResultCode      start_conversion();
    ResultCode      set_alarm(int8_t lower_celsius,
                              int8_t upper_celsius,
                              bool make_default = false);
    ResultCode      read_temperature(Temperature &result);
    ResultCode      reset_defaults();
    ResultCode      get_scratchpad(uint8_t **raw);
private:
    Bus      &bus;
protected:
    explicit        Protocol_DS18x20(Bus &bus) : bus(bus) {};
    ResultCode      _read_scratchpad();
    ResultCode      _write_scratchpad();
    ResultCode      _copy_scratchpad();
    OneWireAddress  address;
    typename Family :: Scratchpad scratchpad;
    bool            has_address = false;
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Broadcast interface for DS18B20-family sensors on a OneWire bus.
 *
 * This class provides group operations using the OneWire SKIP_ROM command,
 * allowing all compatible sensors on the bus to execute the same command
 * simultaneously.
 *
 * Unlike Protocol_DS18x20, this class does not represent an individual device
 * and therefore does not store or use a ROM address.
 *
 * Typical use cases:
 * - start temperature conversion on all sensors simultaneously
 * - write shared configuration to all sensors
 * - reduce OneWire traffic in large sensor networks
 *
 * Internally uses private inheritance from Protocol_DS18x20 to reuse protocol
 * implementation while preventing polymorphic use and implicit conversion
 * to individual sensor type.
 *
 * @note Read operations returning device-specific data are intentionally
 * unavailable for this class.
 */
template <class OneWireBus, class Family>
class Protocol_DS18x20_Group : private Protocol_DS18x20 <OneWireBus, Family>
{
    using Base = Protocol_DS18x20 <OneWireBus, Family>;
public:
    explicit                Protocol_DS18x20_Group(OneWireBus &bus) : Base(bus) {};
    using Base ::           start_conversion;
};
//------------------------------------------------------------------------------------------------
#include "DS18x20.tpp"
//------------------------------------------------------------------------------------------------
#endif


