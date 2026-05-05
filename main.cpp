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
    /* GPIO manipulation */
//    GPIO <B0> led0;
//    led0.set_mode(OUTPUT_HIGH);
//    led0.write_high();

    /* one-line touch even without object */
//    GPIO <B1> :: set_mode(OUTPUT_LOW);
//    GPIO <B1> :: write_high();
//
    /* LED driver */
    //LED_A <B2> led2;
    //led2.on();

    UART0 :: init(BAUD_115200);
    GPIO <A7> :: set_mode(OUTPUT_HIGH);
    //mdelay(100);
    enable_interrupts();



    while(1)
    {

        //UART0 :: write("\x55\x55");
        //UART0 :: write(_flash("ABC\r\n"));
        GPIO <A7> :: write_high();
        UART0 :: write("_123");
        GPIO <A7> :: write_low();
        //UART0 :: tx_wait();
        GPIO <A7> :: write_high();
        udelay(300);
        //led2.on();
    }

    return 0;
}
//------------------------------------------------------------------------------------------------
