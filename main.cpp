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

    UART0 uart;

    uart.init(2000000);
    //GPIO <A7> :: set_mode(OUTPUT_HIGH);
    //mdelay(100);

    enable_interrupts();
    while(1)
    {

        //uint8_t str[] = "_1234 (in /data/Apparat/MAVR/kentavr-firmware/output)\r\n";
        //UART0 :: write("\x55\x55");
        //uart.write(_flash("ABC\r\n"));
        //GPIO <A7> :: write_high();
        //uart.write_all("asdas;kldj;lkjasd\r\n");
        //UART0 :: write_all((const char*)str);
        //UART0 :: write(_flash("1"));
        //GPIO <A7> :: write_low();
        //UART0 :: tx_wait();
        //GPIO <A7> :: write_high();
//        uint8_t data;
        //uart.send(0x30 + uart.available());
        if(uart.available())
        {
            uart.write(uart.read());
        }
        mdelay(1);
        //led2.on();
    }

    return 0;
}
//------------------------------------------------------------------------------------------------
