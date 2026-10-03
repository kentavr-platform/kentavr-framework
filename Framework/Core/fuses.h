/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: Core/fuses.h
//----------------------------------------------------------------------------------------------*/
#ifndef FUSES_H
#define FUSES_H
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
    #if defined(FUSE_CKOPT) && defined(CRYSTAL_FREQ)
        & FUSE_CKOPT        // full-swing crystal oscillator
    #endif
    )
    #if FUSE_MEMORY_SIZE == 3
    ,                       // do not remove this comma
    .extended = (0xFF
        & FUSE_BODLEVEL1
    )
    #endif
};
//------------------------------------------------------------------------------------------------
#endif
