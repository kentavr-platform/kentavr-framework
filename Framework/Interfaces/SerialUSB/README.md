# SerialUSB

`SerialUSB` is a ready-to-use CDC ACM stream for USB-capable AVR microcontrollers.
It is built on LUFA, which provides the USB device stack, CDC class handling,
and low-level USB driver.

You may use it as a `Console` transport as well:

```cpp
SerialUSB usb;
Console console(usb);

int main()
{
    usb.init();
    enable_interrupts();

    // Wait until the host opens the CDC serial port.
    while (!usb.DTR()) {}

    console.clear();
    console.log(_flash("USB console ready"));

    while (true)
    {
        // Application work; LUFA services USB through its interrupts.
    }
}
```

Call `init()` once before enabling global interrupts. EP0 control requests are
handled by LUFA's control-endpoint ISR, and the CDC IN endpoint is flushed from
the USB Start-of-Frame interrupt (once per millisecond). There is no USB polling
call in the application loop. `connected()` reports whether the host selected
the USB configuration; `DTR()` additionally waits for the host to assert DTR
on the CDC port.

The stream provides `write(...)`, `write_all(...)`, and `tx_wait()` for
`Console`. For input, use `available()`, `peek()`, and `read(...)`:

```cpp
if(usb.available())
{
    int data = usb.read();
    if(data >= 0)
    {
        // Process the received byte.
    }
}
```

`peek()` returns the next byte without logically removing it. `read()` returns
`-1` when no byte is available; `read(buffer, count)` reads up to `count` bytes
and returns the number read. Input is accepted after the device is configured
and the host sets a non-zero CDC line-encoding baud rate.

Writes are not queued for later if the device is not configured or the host has
not set a non-zero CDC line-encoding baud rate. In that state LUFA returns a
disconnected endpoint status and sends no data.
