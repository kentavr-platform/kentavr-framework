# USB

## AVR USB controller and LUFA integration

This module exposes the USB device stack for AVR microcontrollers with a
hardware USB controller. The protocol stack, USB controller driver, and class
drivers come from [LUFA](https://github.com/abcminiuser/lufa).


### Configuration

`avr-usb-config.h` configures LUFA for the AVR8 architecture in device-only
mode, sets `F_USB` from the framework clock, and enables interrupt-driven
control endpoint handling with `INTERRUPT_CONTROL_ENDPOINT`.

With this option, LUFA services EP0 control requests from its USB control
endpoint ISR, so the application does not need to call `USB_USBTask()` just to
service EP0. The option applies to the LUFA build as a whole and must be
defined consistently for LUFA source files and application code. Other USB
class drivers may still require their own periodic `*_USBTask()` calls.

### Using LUFA

Use LUFA's device and class APIs to configure endpoints, provide descriptors,
and implement the callbacks required by the selected USB class. USB class
processing is still application-specific; interrupt-driven EP0 handling does
not automatically service every class driver.
