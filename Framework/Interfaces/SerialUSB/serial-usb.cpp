/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: serial-usb.cpp
//----------------------------------------------------------------------------------------------*/
#include "AVR/USB/avr-usb.h"
#include "serial-usb.h"
#include "serial-usb-config.h"
//------------------------------------------------------------------------------------------------
#define SERIAL_USB_CONTROL_INTERFACE       0
#define SERIAL_USB_DATA_INTERFACE          1
#define SERIAL_USB_NOTIFICATION_ENDPOINT   (ENDPOINT_DIR_IN  | 1)
#define SERIAL_USB_RX_ENDPOINT             (ENDPOINT_DIR_OUT | 2)
#define SERIAL_USB_TX_ENDPOINT             (ENDPOINT_DIR_IN  | 3)
#define SERIAL_USB_NOTIFICATION_SIZE       8
#define SERIAL_USB_DATA_SIZE               64
//------------------------------------------------------------------------------------------------
namespace
{
    int16_t rx_peeked = -1;

    USB_ClassInfo_CDC_Device_t cdc_interface =
    {
        {
            SERIAL_USB_CONTROL_INTERFACE,
            { SERIAL_USB_TX_ENDPOINT, SERIAL_USB_DATA_SIZE, EP_TYPE_BULK, 1 },
            { SERIAL_USB_RX_ENDPOINT, SERIAL_USB_DATA_SIZE, EP_TYPE_BULK, 1 },
            { SERIAL_USB_NOTIFICATION_ENDPOINT, SERIAL_USB_NOTIFICATION_SIZE, EP_TYPE_INTERRUPT, 1 }
        },
        {}
    };

    typedef struct
    {
        USB_Descriptor_Configuration_Header_t  configuration;
        USB_Descriptor_Interface_t             control_interface;
        USB_CDC_Descriptor_FunctionalHeader_t  cdc_header;
        struct ATTR_PACKED
        {
            USB_Descriptor_Header_t Header;
            uint8_t                 Subtype;
            uint8_t                 Capabilities;
            uint8_t                 DataInterface;
        } cdc_call_management;
        USB_CDC_Descriptor_FunctionalACM_t     cdc_acm;
        USB_CDC_Descriptor_FunctionalUnion_t   cdc_union;
        USB_Descriptor_Endpoint_t              notification_endpoint;
        USB_Descriptor_Interface_t             data_interface;
        USB_Descriptor_Endpoint_t              data_out_endpoint;
        USB_Descriptor_Endpoint_t              data_in_endpoint;
    } ATTR_PACKED SerialUSB_Configuration_t;

    const USB_Descriptor_Device_t device_descriptor PROGMEM =
    {
        { sizeof(USB_Descriptor_Device_t), DTYPE_Device },
        VERSION_BCD(2, 0, 0),
        0x02,
        0x00,
        0x00,
        64,
        SERIAL_USB_VENDOR_ID,
        SERIAL_USB_PRODUCT_ID,
        VERSION_BCD(1, 0, 0),
        NO_DESCRIPTOR,
        NO_DESCRIPTOR,
        NO_DESCRIPTOR,
        1
    };

    const SerialUSB_Configuration_t configuration_descriptor PROGMEM =
    {
        {
            { sizeof(USB_Descriptor_Configuration_Header_t), DTYPE_Configuration },
            sizeof(SerialUSB_Configuration_t),
            2,
            1,
            NO_DESCRIPTOR,
            USB_CONFIG_ATTR_RESERVED,
            USB_CONFIG_POWER_MA(100)
        },
        {
            { sizeof(USB_Descriptor_Interface_t), DTYPE_Interface },
            SERIAL_USB_CONTROL_INTERFACE,
            0,
            1,
            CDC_CSCP_CDCClass,
            CDC_CSCP_ACMSubclass,
            CDC_CSCP_ATCommandProtocol,
            NO_DESCRIPTOR
        },
        {
            { sizeof(USB_CDC_Descriptor_FunctionalHeader_t), CDC_DTYPE_CSInterface },
            CDC_DSUBTYPE_CSInterface_Header,
            VERSION_BCD(1, 1, 0)
        },
        {
            { 5, CDC_DTYPE_CSInterface },
            CDC_DSUBTYPE_CSInterface_CallManagement,
            0,
            SERIAL_USB_DATA_INTERFACE
        },
        {
            { sizeof(USB_CDC_Descriptor_FunctionalACM_t), CDC_DTYPE_CSInterface },
            CDC_DSUBTYPE_CSInterface_ACM,
            0x06
        },
        {
            { sizeof(USB_CDC_Descriptor_FunctionalUnion_t), CDC_DTYPE_CSInterface },
            CDC_DSUBTYPE_CSInterface_Union,
            SERIAL_USB_CONTROL_INTERFACE,
            SERIAL_USB_DATA_INTERFACE
        },
        {
            { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint },
            SERIAL_USB_NOTIFICATION_ENDPOINT,
            EP_TYPE_INTERRUPT,
            SERIAL_USB_NOTIFICATION_SIZE,
            16
        },
        {
            { sizeof(USB_Descriptor_Interface_t), DTYPE_Interface },
            SERIAL_USB_DATA_INTERFACE,
            0,
            2,
            CDC_CSCP_CDCDataClass,
            CDC_CSCP_NoDataSubclass,
            CDC_CSCP_NoDataProtocol,
            NO_DESCRIPTOR
        },
        {
            { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint },
            SERIAL_USB_RX_ENDPOINT,
            EP_TYPE_BULK,
            SERIAL_USB_DATA_SIZE,
            0
        },
        {
            { sizeof(USB_Descriptor_Endpoint_t), DTYPE_Endpoint },
            SERIAL_USB_TX_ENDPOINT,
            EP_TYPE_BULK,
            SERIAL_USB_DATA_SIZE,
            0
        }
    };
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Initialize LUFA and enable USB Start-of-Frame events.
 *
 * Call once before enabling global interrupts. LUFA handles control requests
 * in the control-endpoint ISR; the Start-of-Frame callback services CDC's
 * periodic IN flush.
 */
void SerialUSB :: init()
{
    USB_Init(USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL);
    USB_Device_EnableSOFEvents();
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Check whether the host configured the USB device.
 *
 * This reports the USB device state, not whether a CDC terminal is open.
 *
 * @return true if the device is in the configured state.
 */
bool SerialUSB :: connected()
{
    return USB_DeviceState == DEVICE_STATE_Configured;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Check whether the host has asserted DTR on the CDC interface.
 *
 * DTR is considered active only while the device is configured and the host
 * has supplied a non-zero CDC line-encoding baud rate.
 *
 * @return true if the CDC DTR control-line bit is set and CDC is active.
 */
bool SerialUSB :: DTR()
{
    return connected()
        && cdc_interface.State.LineEncoding.BaudRateBPS
        && (cdc_interface.State.ControlLineStates.HostToDevice & CDC_CONTROL_LINE_OUT_DTR);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Return the number of bytes currently available from the host.
 *
 * The count includes a byte previously fetched by peek() and held in the
 * one-byte lookahead slot.
 *
 * @return Number of bytes currently readable, up to the CDC OUT packet size.
 */
uint8_t SerialUSB :: available()
{
    return CDC_Device_BytesReceived(&cdc_interface) + (rx_peeked >= 0);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Inspect the next byte from the host without consuming it logically.
 *
 * The byte is read from the CDC OUT endpoint and retained in a one-byte
 * lookahead slot until read() consumes it.
 *
 * @return Next byte as an unsigned value promoted to int, or -1 if none exists.
 */
int SerialUSB :: peek()
{
    if(rx_peeked < 0)
    {
        rx_peeked = CDC_Device_ReceiveByte(&cdc_interface);
    }
    return rx_peeked;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read and remove the next byte received from the host.
 *
 * @return Next byte as an unsigned value promoted to int, or -1 if no byte is
 *         available.
 */
int SerialUSB :: read()
{
    if(rx_peeked >= 0)
    {
        int16_t data = rx_peeked;
        rx_peeked = -1;
        return data;
    }
    return CDC_Device_ReceiveByte(&cdc_interface);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Read multiple bytes received from the host.
 *
 * Copies up to @p count bytes into @p buf and stops when no more bytes are
 * immediately available.
 *
 * @param buf Destination buffer.
 * @param count Maximum number of bytes to read.
 *
 * @return Number of bytes copied into @p buf.
 */
uint8_t SerialUSB :: read(uint8_t *buf, const uint8_t count)
{
    uint8_t received = 0;
    while(received < count)
    {
        int data = read();
        if(data < 0)
        {
            break;
        }
        buf[received++] = static_cast <uint8_t> (data);
    }
    return received;
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send one byte to the host.
 *
 * @param data Byte to transmit.
 *
 * @return LUFA endpoint status; a disconnected status is returned if CDC is
 *         not configured or has no active line-encoding baud rate.
 */
uint8_t SerialUSB :: write(char data)
{
    return CDC_Device_SendByte(&cdc_interface, static_cast <uint8_t> (data));
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send a null-terminated RAM string to the host.
 *
 * @param str Null-terminated string in RAM.
 *
 * @return LUFA endpoint stream status.
 */
uint8_t SerialUSB :: write(const char *str)
{
    return CDC_Device_SendString(&cdc_interface, str);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send a null-terminated PROGMEM string to the host.
 *
 * @param fs Flash string wrapper, typically created by _flash("text").
 *
 * @return LUFA endpoint stream status.
 */
uint8_t SerialUSB :: write(FlashStringWrapper fs)
{
    return CDC_Device_SendString_P(&cdc_interface, fs.str);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send a RAM byte buffer to the host.
 *
 * @param buf Pointer to the first byte to transmit.
 * @param count Number of bytes to transmit.
 *
 * @return LUFA endpoint stream status.
 */
uint8_t SerialUSB :: write(const uint8_t *buf, uint16_t count)
{
    return CDC_Device_SendData(&cdc_interface, buf, count);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send a null-terminated RAM string using the complete-stream routine.
 *
 * @param str Null-terminated string in RAM.
 *
 * @return LUFA endpoint stream status.
 */
uint8_t SerialUSB :: write_all(const char *str)
{
    return write(str);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send a null-terminated PROGMEM string using the complete-stream routine.
 *
 * @param fs Flash string wrapper, typically created by _flash("text").
 *
 * @return LUFA endpoint stream status.
 */
uint8_t SerialUSB :: write_all(FlashStringWrapper fs)
{
    return write(fs);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Send a complete RAM byte buffer using the complete-stream routine.
 *
 * @param buf Pointer to the first byte to transmit.
 * @param count Number of bytes to transmit.
 *
 * @return LUFA endpoint stream status.
 */
uint8_t SerialUSB :: write_all(const uint8_t *buf, uint16_t count)
{
    return write(buf, count);
}
//------------------------------------------------------------------------------------------------
/**
 * @brief Flush the pending CDC IN endpoint bank to the host.
 *
 * @return LUFA endpoint status.
 */
uint8_t SerialUSB :: tx_wait()
{
    return CDC_Device_Flush(&cdc_interface);
}
//------------------------------------------------------------------------------------------------
void EVENT_USB_Device_ConfigurationChanged()
{
    rx_peeked = -1;
    CDC_Device_ConfigureEndpoints(&cdc_interface);
}
//------------------------------------------------------------------------------------------------
void EVENT_USB_Device_ControlRequest()
{
    CDC_Device_ProcessControlRequest(&cdc_interface);
}
//------------------------------------------------------------------------------------------------
// LUFA invokes this once per USB frame, providing CDC's periodic IN flush.
void EVENT_USB_Device_StartOfFrame()
{
    CDC_Device_USBTask(&cdc_interface);
}
//------------------------------------------------------------------------------------------------
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t value,
                                    const uint16_t,
                                    const void **descriptor_address,
                                    uint8_t *descriptor_memory_space)
{
    const uint8_t descriptor_type = value >> 8;
    const uint8_t descriptor_index = value & 0xFF;
    uint16_t descriptor_size = NO_DESCRIPTOR;

    *descriptor_memory_space = MEMSPACE_FLASH;

    if (descriptor_type == DTYPE_Device)
    {
        *descriptor_address = &device_descriptor;
        descriptor_size = sizeof(device_descriptor);
    }
    else if ((descriptor_type == DTYPE_Configuration) && (descriptor_index == 0))
    {
        *descriptor_address = &configuration_descriptor;
        descriptor_size = sizeof(configuration_descriptor);
    }

    return descriptor_size;
}
//------------------------------------------------------------------------------------------------
