//------------------------------------------------------------------------------------------------
#include "core.h"
//------------------------------------------------------------------------------------------------
#ifdef DEBUG
    SerialBitOut<D1, 2000000> debug;
    Console console(debug);
#else
    Console console;
#endif
Settings settings(EEPROM, 0, 512);
//------------------------------------------------------------------------------------------------
void early_init()
{
    // Run this code IMMIDEATELY at reset interrupt. Use with caution - stack
    // pointer is NOT initialized yet. Read about section(".initX") attribute
    // for more information.
    // ...

    // then continue stack and other initalizations
}
//------------------------------------------------------------------------------------------------
int main()
{
    // debug console

//    uint16_t test = 12345;
    console.clear();
    console.log(_flash("DEBUG READY"));
    //settings._write_header();
    settings.clear();
    console.dump_eeprom(0, 512, true);





//    uint8_t *ptr;

    while(1)
    {


    }

    return 0;
}
//------------------------------------------------------------------------------------------------
