#ifndef DS1820_H
#define DS1820_H
//------------------------------------------------------------------------------------------------
#ifndef DS18X20_H
#error Include sensors/DS18X20 header file first
#endif
//------------------------------------------------------------------------------------------------
/**
 * @brief Driver for DS18S20 1-Wire temperature sensor.
 *
 * This class provides a concrete specialization of the generic
 * Protocol_DS18x20 for the legacy DS18S20 devices.
  *
 * These sensors use 9-bit resolution with extended resolution
 * computation based on count_per_c / count_remain.
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
 *      Sensor_DS1820 sensor(bus, addr);
 *      sensor.start_conversion();
 *      ...
 *      sensor.get_temperature(temp);
 *      ...
 *      sensor.set_alarm(15, 25);
 *  }
 *  ...
 *  Sensor_DS1820_Group all_sensors(bus);
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
class Sensor_DS1820 : public Protocol_DS18x20 <Bus, S20_Family>
{
public:
    using Protocol_DS18x20 <Bus, S20_Family> :: Protocol_DS18x20;
};
template <class Bus>
Sensor_DS1820(Bus&, const OneWireAddress&) -> Sensor_DS1820 <Bus>;
//------------------------------------------------------------------------------------------------
template <class Bus>
class Sensor_DS1820_Group : public Protocol_DS18x20_Group <Bus, S20_Family>
{
public:
    using Protocol_DS18x20_Group <Bus, S20_Family> :: Protocol_DS18x20_Group;
    bool is_valid() = delete;
};
template <class Bus>
Sensor_DS1820_Group(Bus&) -> Sensor_DS1820_Group <Bus>;
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(Sensor_DS1820);
SET_CONSOLE_TEMPLATE_TYPE_NAME(Sensor_DS1820_Group);
//------------------------------------------------------------------------------------------------
#endif
