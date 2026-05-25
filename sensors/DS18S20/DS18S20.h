#ifndef DS18S20_H
#define DS18S20_H
//------------------------------------------------------------------------------------------------
#ifndef DS1820_H
#error Include sensors/DS1820 header file first
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
 *      Sensor_DS18S20 sensor(bus, addr);
 *      sensor.start_conversion();
 *      ...
 *      sensor.get_temperature(temp);
 *      ...
 *      sensor.set_alarm(15, 25);
 *  }
 *  ...
 *  Sensor_DS18S20_Group all_sensors(bus);
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
 *
 * @note This driver implementation is an absolete copy of DS1820 driver.
 */
template <class Bus>
class Sensor_DS18S20 : public Sensor_DS1820 <Bus>
{
public:
    using Sensor_DS1820 <Bus> :: Sensor_DS1820;
};
template <class Bus>
Sensor_DS18S20(Bus&, const OneWireAddress&) -> Sensor_DS18S20 <Bus>;
//------------------------------------------------------------------------------------------------
template <class Bus>
class Sensor_DS18S20_Group : public Sensor_DS1820_Group <Bus>
{
public:
    using Sensor_DS1820_Group <Bus> :: Sensor_DS1820_Group;
};
template <class Bus>
Sensor_DS18S20_Group(Bus&) -> Sensor_DS18S20_Group <Bus>;
//------------------------------------------------------------------------------------------------
SET_CONSOLE_TEMPLATE_TYPE_NAME(Sensor_DS18S20);
SET_CONSOLE_TEMPLATE_TYPE_NAME(Sensor_DS18S20_Group);
//------------------------------------------------------------------------------------------------
#endif
