#ifndef DS18B20_H
#define DS18B20_H
//------------------------------------------------------------------------------------------------
#ifndef DS18X20_H
#error Include sensors/DS18X20 header file first
#endif
//------------------------------------------------------------------------------------------------
enum DS_Temp_Resolution
{
    BITS_9  = 0x1F,     // LSB = 0.5 deg C
    BITS_10 = 0x3F,     // LSB = 0.25 deg C
    BITS_11 = 0x5F,     // LSB = 0.125 deg C
    BITS_12 = 0x7F      // LSB = 0.0625 deg C
};
//------------------------------------------------------------------------------------------------
/**
 * @brief Driver for DS18B20 1-Wire temperature sensor.
 *
 * This class provides a concrete specialization of the generic
 * Protocol_DS18x20 for the legacy DS18B20 devices.
  *
 * These sensors use configurable 9...12-bit resolution.
 *
 * Typical usage example:
 *
 * @code {.cpp}
 *  OneWireBus <A7> bus;
 *  OneWireAddress addr;
 *  Temperature temp;
 *
 *  if(bus.find_first(addr))
 *  {
 *      Sensor_DS18B20 sensor(bus, addr);
 *      sensor.set_resolution(BITS_10);
 *      sensor.start_conversion();
 *      ...
 *      sensor.get_temperature(temp);
 *      ...
 *      sensor.set_alarm(15, 25);
 *  }
 *  ...
 *  Sensor_DS18B20_Group all_sensors(bus);
 *  all_sensors.start_conversion();
 *  ...
 *  bus.find_reset(addr);
 *  while(bus.find_alarm(addr))
 *  {
 *      Sensor_DS18B20 alarm_sensor(bus, addr);
 *      if(!alarm_sensor.is_valid()) continue;
 *      alarm_sensor.read_temperature(temp);
 *      if(temp.is_valid())
 *      {
 *          console.log(temp.millis_celsius);
 *      }
 *  }
 * @endcode
 *
 * @tparam Bus OneWire bus object
 */
template <class Bus>
class Sensor_DS18B20 : public Protocol_DS18x20 <Bus, B20_Family>
{
public:
    using Protocol_DS18x20 <Bus, B20_Family> :: Protocol_DS18x20;
    ResultCode        set_resolution(enum DS_Temp_Resolution bits, bool make_default = false);
};
template <class Bus>
Sensor_DS18B20(Bus&, const OneWireAddress&) -> Sensor_DS18B20 <Bus>;
//------------------------------------------------------------------------------------------------
template <class Bus>
class Sensor_DS18B20_Group : public Protocol_DS18x20_Group <Bus, B20_Family>
{
public:
    using Protocol_DS18x20_Group <Bus, B20_Family> :: Protocol_DS18x20_Group;
    bool is_valid() = delete;
};
template <class Bus>
Sensor_DS18B20_Group(Bus&) -> Sensor_DS18B20_Group <Bus>;
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(Sensor_DS18B20);
SET_CONSOLE_TEMPLATE_TYPE_NAME(Sensor_DS18B20_Group);
//------------------------------------------------------------------------------------------------
#include "DS18B20.tpp"
//------------------------------------------------------------------------------------------------
#endif
