#ifndef DS1825_H
#define DS1825_H
//------------------------------------------------------------------------------------------------
#ifndef DS18B20_H
#error Include sensors/DS18B20 header file first
#endif
//------------------------------------------------------------------------------------------------
template <class Bus>
class Sensor_DS1825 : public Sensor_DS18B20 <Bus>
{
public:
    using Sensor_DS18B20 <Bus> :: Sensor_DS18B20;
};
template <class Bus>
Sensor_DS1825(Bus&, const OneWireAddress&) -> Sensor_DS1825 <Bus>;
//------------------------------------------------------------------------------------------------
template <class Bus>
class Sensor_DS1825_Group : public Sensor_DS18B20_Group <Bus>
{
public:
    using Sensor_DS18B20_Group <Bus> :: Sensor_DS18B20_Group;
};
template <class Bus>
Sensor_DS1825_Group(Bus&, const OneWireAddress&) -> Sensor_DS1825_Group <Bus>;
//------------------------------------------------------------------------------------------------
#endif
