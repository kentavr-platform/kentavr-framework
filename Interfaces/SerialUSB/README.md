# SerialUSB

## USB CDC ACM serial interface

### Summary

 - Provides a byte stream between the AVR and a USB host using CDC-ACM
 - Uses [LUFA](https://github.com/abcminiuser/lufa) for the USB device stack,
   CDC class, and low-level USB driver
 - Owns the USB descriptors and LUFA event callbacks
 - Handles EP0 through LUFA's control-endpoint interrupt
 - Flushes CDC output from the USB Start-of-Frame interrupt
 - Discards incoming packets in the background in `TX_only` mode
 - Selects `RX_only`, `TX_only`, or `RX_TX` at runtime through the constructor
 - Can be used as a `Console` transport

### Limitations

 - Requires an AVR MCU with a hardware USB controller supported by LUFA
 - Global interrupts must be enabled after `init()`
 - Provides one CDC interface; use one `SerialUSB` object

### Configuration

Enable USB and interrupt-driven control requests in the application's
`usb-config.h`:

```cpp
#define ENABLE_USB
#define INTERRUPT_CONTROL_ENDPOINT
```

`INTERRUPT_CONTROL_ENDPOINT` enables LUFA's `USB_COM_vect` handler for EP0.
It is required for the interrupt-driven usage shown below, which does not
call `USB_USBTask()` in the application loop. Without this definition, EP0
requires regular polling through `USB_USBTask()`.

These definitions must be visible when compiling all USB sources, including
LUFA, rather than defined only in `main.cpp`. KentAVR's ATmega32U4, Leonardo,
and Pro Micro project targets force-include `AVR/USB/avr-usb-config.h`, which
includes the application's `usb-config.h`.

Keep SOF events and CDC automatic flushing enabled: do not define
`NO_SOF_EVENTS` or `NO_CLASS_DRIVER_AUTOFLUSH`.

### Typical usage

```cpp
SerialUSB usb(TX_only);

int main()
{
    usb.init();
    enable_interrupts();

    while(!usb.DTR()) {}

    usb.write_all(_flash("USB ready\r\n"));

    while(true)
    {
        // LUFA handles USB events through interrupts.
    }
}
```

`init()` must be called once before `enable_interrupts()`. There is no
application polling call for EP0 or the CDC IN endpoint with the configuration
above. Waiting for `DTR()` is optional and is useful when output should begin
only after the host opens the serial port. `connected()` reports whether the
USB device is configured; `DTR()` additionally requires a nonzero CDC baud
rate and the host's DTR control-line bit.

The CDC baud rate is host-provided line-encoding metadata; it does not set the
USB bus speed.

### Directions

Directions are relative to the MCU. Select the mode when constructing the
object, before `init()`:

```cpp
SerialUSB usb;              // RX_TX by default
// SerialUSB usb(RX_only);   // Receive only
// SerialUSB usb(TX_only);   // Transmit only
```

In `TX_only` mode, the driver releases incoming CDC OUT packets and discards their
contents in the background. The application does not need to call `read()`
to consume host echo or other unwanted input.

In `RX_only` and `RX_TX` modes, the application reads directly from the hardware OUT
bank. There is no software RX queue. An unread packet holds the bank and
pauses further reception until the application consumes it.

`RX_only` mode disables writes; write methods and `tx_wait()` return LUFA's
`ENDPOINT_RWSTREAM_DeviceDisconnected` status without transmitting data.

The CDC descriptors and hardware endpoints remain the same in every mode.

### Console transport

`SerialUSB` provides the stream methods required by `Console`. Use `TX_only`
for an output-only console. Receive host input directly through the
`SerialUSB` methods described below when using `RX_TX`.

```cpp
SerialUSB usb(TX_only);
Console console(usb);

int main()
{
    usb.init();
    enable_interrupts();

    while(!usb.DTR()) {}

    console.clear();
    console.log(_flash("USB console ready"));

    while(true)
    {
        // Application work.
    }
}
```

### Reading

Use `available()`, `peek()`, and `read()` to receive bytes from the host:

```cpp
if(usb.available())
{
    int data = usb.read();
    if(data >= 0)
    {
        usb.write((char) data);
    }
}
```

`available()` reports bytes currently in the CDC OUT packet, including a byte
held by `peek()`. `peek()` retains that one byte until `read()` consumes it
logically. `read()` returns the byte as an `int`, or `-1` if none is available.
In `TX_only` mode, `available()` returns zero and `peek()` and `read()` return `-1`.
`read(buffer, count)` reads up to `count` bytes and returns the number read.

### Writing

`write(...)` supports a single byte, RAM strings, PROGMEM strings, and RAM byte
buffers. `write_all(...)` supports strings and buffers, using the same LUFA CDC
stream write operation. `tx_wait()` submits the partial CDC IN packet;
otherwise LUFA flushes it from the Start-of-Frame interrupt.

Writes may block while waiting for the host to accept a packet. Write methods
and `tx_wait()` return a LUFA status code: zero on success. Before USB is
configured or the host supplies a nonzero CDC baud rate, they return
`ENDPOINT_RWSTREAM_DeviceDisconnected`; output is not queued for later delivery.
