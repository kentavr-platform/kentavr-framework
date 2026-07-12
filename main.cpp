//------------------------------------------------------------------------------------------------
#include "core.h"
#include "config.h"
//------------------------------------------------------------------------------------------------
/*  // Several useful global objects
#ifdef DEBUG
    SerialBitOut <D1, 2000000> debug;
    Console console(debug);
#else
    Console console;    // a black-hole object with no output and zero runtime overhead
#endif
*/
//------------------------------------------------------------------------------------------------
void early_init()
{
    // Runs immediately after reset, before stack and runtime initialization.
    // Use with extreme caution: only code that does not use the stack is safe here.
    // See the GCC AVR documentation for section(".initX") and naked functions.
    // ...

    // Startup continues with stack and runtime initialization.
}
//------------------------------------------------------------------------------------------------
int main()
{
    // Initialization and setup

    while(1)
    {
        // main loop

    }

    return 0;
}
//------------------------------------------------------------------------------------------------
