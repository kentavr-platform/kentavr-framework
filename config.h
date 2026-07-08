/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: config.h
//----------------------------------------------------------------------------------------------*/
#ifndef CONFIG_H
#define CONFIG_H
//------------------------------------------------------------------------------------------------
FUSES =
{
    .low = (0xFF
        & FUSE_SUT0         // slow (65ms) startup
    #if defined(INTERNAL_CLOCK_8MHZ)
        & FUSE_CKSEL0
        & FUSE_CKSEL2
        & FUSE_CKSEL3
    #elif defined(EXTERNAL_CLOCK)
        & FUSE_CKSEL0
        & FUSE_CKSEL1
        & FUSE_CKSEL2
        & FUSE_CKSEL3
    #endif
    ),
    .high = (0xFF
        & FUSE_SPIEN        // enable SPI programming
        & FUSE_EESAVE       // preserve EEPROM from chip erase command
    ),
    .extended = (0xFF
        & FUSE_BODLEVEL1
    )
};
//------------------------------------------------------------------------------------------------
/** Enable and configure hardware UARTs here

    All UART instances share the same driver implementation.

    Warning: buffer sizes must be power of 2 and <= 256 (8-bit optimized mode). Please note,
    that effective ring buffer capacity is one byte less than the configured buffer size
    (BUFFER_SIZE - 1).

    A buffer size of 0 (zero) completely disables RX or TX respectively - no interrupt,
    no buffer, no code.

    Flow control is not implemented in this design. However you can do it yourself.

 ENABLE_UARTx(
              RX_BUFFER_SIZE,  -- size of reception buffer (required)
              TX_BUFFER_SIZE,  -- size of transmission buffer (required)
             )

    Feel free to uncomment and modify the following lines to enable hardware UARTs.
    See UART for details.
                                                                                                */
// ENABLE_UART0(0, 128);
// ENABLE_UART1(0, 128);
// ENABLE_UART2(0, 128);
// ENABLE_UART3(0, 128);

//------------------------------------------------------------------------------------------------
/**
    Enable settings instance and reserves EEPROM space.

    Allocates an EEPROM object of exactly Size bytes and creates a
    global settings storage instance using that region.

 ENABLE_SETTINGS(SETTINGS_SIZE);
                 SETTINGS_SIZE  -- EEPROM size reserved for settings storage
                                   (header + data + index)


    Uncomment and modify the following lines to enable it.
    See settings for details.
                                                                                                */
// ENABLE_SETTINGS(512);

//------------------------------------------------------------------------------------------------
/**
    Enable and configure I2C busses here
    Feel free to uncomment and modify the following lines to enable hardware I2Cs.
    See I2C for details.
                                                                                                */
// ENABLE_I2C0(32);
// ENABLE_I2C1(32);
//------------------------------------------------------------------------------------------------
#endif
