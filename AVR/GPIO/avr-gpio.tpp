/*------------------------------------------------------------------------------------------------
 * gpio.tpp
 *
 * ATTENTION! This file is included from gpio.h and must NOT be built.
 *
//----------------------------------------------------------------------------------------------*/
template <class pin>
__inline void GPIO <pin> :: set_mode(enum GPIO_mode mode)
{
    switch(mode)
    {
    case OUTPUT_HIGH:
        write_high();
        set_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        break;
    case OUTPUT_LOW:
        write_low();
        set_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        break;
    case INPUT_PULLUP:
        clr_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        write_high();
        break;
    case INPUT_OPEN:
        clr_bit(_SFR_IO8(pin :: DDR), pin :: BIT);
        write_low();
        break;
    }
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void GPIO <pin> :: write_high()
{
    set_bit(_SFR_IO8(pin::PORT), pin::BIT);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void GPIO <pin> :: write_low()
{
    clr_bit(_SFR_IO8(pin :: PORT), pin :: BIT);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline uint8_t GPIO <pin> :: read()
{
    return test_bit(_SFR_IO8(pin :: PIN), pin :: BIT);
}
//------------------------------------------------------------------------------------------------
template <class pin>
__inline void GPIO <pin> :: toggle()
{
    if(test_bit(_SFR_IO8(pin :: PORT), pin :: BIT))
    {
        write_low();
    }
    else
    {
        write_high();
    }
}
//------------------------------------------------------------------------------------------------





