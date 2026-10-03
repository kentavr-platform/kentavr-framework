# SerialUSB

## USB CDC ACM serial interface

### Summary

 - Provides a byte stream between the AVR and a USB host using CDC-ACM
 - Uses [LUFA](https://github.com/abcminiuser/lufa) for the USB device stack,
   CDC class, and low-level USB driver
 - Owns the USB descriptors and LUFA event callbacks
 - Handles EP0 through LUFA's control-endpoint interrupt
 - Flushes CDC output from the USB Start-of-Frame interrupt
 - Can be used as a `Console` transport

### Limitations

 - Requires an AVR MCU with a hardware USB controller supported by LUFA
 - Global interrupts must be enabled after `init()`

### Typical usage

```cpp
SerialUSB usb;

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
application polling call for EP0 or the CDC IN endpoint. Waiting for `DTR()` is
optional and is useful when output should begin only after the host opens the
serial port.

The CDC baud rate is host-provided line-encoding metadata; it does not set the
USB bus speed.

### Console transport

`SerialUSB` provides the stream methods required by `Console`:

`Console` is for formatted output; receive host input directly through the
`SerialUSB` methods described below.

```cpp
SerialUSB usb;
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
held by `peek()`. `peek()` returns the next byte without logically consuming
it. `read()` returns the byte as an `int`, or `-1` if none is available.
`read(buffer, count)` reads up to `count` bytes and returns the number read.

### Writing

`write(...)` supports a single byte, RAM strings, PROGMEM strings, and RAM byte
buffers. `write_all(...)` supports strings and buffers, using the same LUFA CDC
stream write operation. `tx_wait()` submits the partial CDC IN packet;
otherwise LUFA flushes it from the Start-of-Frame interrupt.
