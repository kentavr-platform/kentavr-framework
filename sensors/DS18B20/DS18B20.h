#ifndef DS18B20_H
#define DS18B20_H
//------------------------------------------------------------------------------------------------
enum DS_Temp_Resolution
{
    BITS_9  = 0x1F,     // LSB = 0.5 deg C
    BITS_10 = 0x3F,     // LSB = 0.25 deg C
    BITS_11 = 0x5F,     // LSB = 0.125 deg C
    BITS_12 = 0x7F      // LSB = 0.0625 deg C
};
//------------------------------------------------------------------------------------------------
template <class OneWireBus>
class Sensor_DS18B20
{
public:
    explicit    Sensor_DS18B20(OneWireBus &bus, const OneWireAddress &addr) : bus(bus),
                                                                             address(addr),
                                                                             has_address(true) {};
    ResultCode        start_conversion();
    ResultCode        set_alarm(int8_t lower_celsius, int8_t upper_celsius, bool make_default = false);
    ResultCode        set_resolution(enum DS_Temp_Resolution bits, bool make_default = false);
    ResultCode        read_temperature(Temperature &result);
    ResultCode        reset_defaults();
    ResultCode        get_scratchpad(uint8_t **raw);
private:
    OneWireBus &bus;
    // scratchpad buffer
    union
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
    } scratchpad;
    OneWireAddress          address;
    ResultCode              _read_scratchpad();
    ResultCode              _write_scratchpad();
    ResultCode              _copy_scratchpad();
protected:
    explicit                Sensor_DS18B20(OneWireBus &bus) : bus(bus) {};
    bool                    has_address = false;
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Broadcast interface for DS18B20-family sensors on a OneWire bus.
 *
 * This class provides group operations using the OneWire SKIP_ROM command,
 * allowing all compatible sensors on the bus to execute the same command
 * simultaneously.
 *
 * Unlike Sensor_DS18B20, this class does not represent an individual device
 * and therefore does not store or use a ROM address.
 *
 * Typical use cases:
 * - start temperature conversion on all sensors simultaneously
 * - write shared configuration to all sensors
 * - reduce OneWire traffic in large sensor networks
 *
 * Internally uses private inheritance from Sensor_DS18B20 to reuse protocol
 * implementation while preventing polymorphic use and implicit conversion
 * to individual sensor type.
 *
 * @note Read operations returning device-specific data are intentionally
 * unavailable for this class.
 */
template <class OneWireBus>
class Sensor_DS18B20_Group : private Sensor_DS18B20 <OneWireBus>
{
    using Base = Sensor_DS18B20 <OneWireBus>;
public:
    explicit                Sensor_DS18B20_Group(OneWireBus &bus) : Base(bus) {};
    using Base ::           start_conversion;
};
//------------------------------------------------------------------------------------------------
#include "DS18B20.tpp"
//------------------------------------------------------------------------------------------------
#endif // DS18B20_H


