//------------------------------------------------------------------------------------------------
#include "core.h"
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
    GPIO <B0> led0;
    led0.set_mode(OUTPUT_HIGH);
    led0.write_high();

    while(1)
    {
        mdelay(100);
        led0.toggle();
    }

    return 0;
}
//------------------------------------------------------------------------------------------------
