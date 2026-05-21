#ifndef UNITS_H
#define UNITS_H
//------------------------------------------------------------------------------------------------
struct Temperature
{
    __inline bool is_valid()                 const { return valid; };
    __inline int16_t get_int_celsius()       const { return (millis_celsius + 500) / 1000; }
    __inline int16_t get_int_fahrenheit()    const { return (millis_celsius * 9 + 2500) / 5000 + 32; }
    __inline int16_t get_int_kelvin()        const { return (millis_celsius + 273150 + 500) / 1000; }
    // WARNING: float is very expensive in MCU!
    __inline float get_float_celsius()       const { return (float) millis_celsius / 1000.0f; };
    __inline float get_float_fahrenheit()    const { return (float) millis_celsius * 9.0f / 5000.0f + 32.0f; };
    __inline float get_float_kelvin()        const { return (float) millis_celsius / 1000.0f + 273.15f; };

    int32_t millis_celsius = INT32_MIN;
    bool valid = false;
};
//------------------------------------------------------------------------------------------------

#endif // UNITS_H
