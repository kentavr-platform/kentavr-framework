/*------------------------------------------------------------------------------------------------
 * Project: KentAVR Framework
 *
 * File: avr-isp.h
//----------------------------------------------------------------------------------------------*/
#ifndef AVR_ISP_H
#define AVR_ISP_H
//------------------------------------------------------------------------------------------------
enum AVR_ISP_Fuse : uint8_t
{
    AVR_ISP_FUSE_LOW,
    AVR_ISP_FUSE_HIGH,
    AVR_ISP_FUSE_EXTENDED
};
//------------------------------------------------------------------------------------------------
template <class SPI, class RST_PIN>
class AVR_ISP
{
public:
    ResultCode  init(uint32_t frequency);
    ResultCode  enter_programming_mode();
    void        leave_programming_mode();
    void        forget_target();
    ResultCode  command(const uint8_t command[4], uint8_t response[4]);
    ResultCode  chip_erase();
    ResultCode  read_signature(uint8_t signature[3]);
    ResultCode  read_fuse(AVR_ISP_Fuse fuse, uint8_t &value);
    ResultCode  write_fuse(AVR_ISP_Fuse fuse, uint8_t value);
    ResultCode  read_flash(uint32_t address, uint8_t *data, uint16_t size);
    ResultCode  write_flash_page(uint32_t address, const uint8_t *data, uint16_t page_size);
    ResultCode  read_eeprom(uint16_t address, uint8_t *data, uint16_t size);
    ResultCode  write_eeprom(uint16_t address, const uint8_t *data, uint16_t size);

private:
    bool initialized = false;
    bool active = false;
    uint8_t extended_address = 0;
    uint32_t target_signature = 0; // Signature in low 24 bits; read-byte mask in high bits.
    bool target_supports_rdy_bsy = false;
    static constexpr uint8_t reset_pulse_ms = 1;
    static constexpr uint8_t reset_wait_ms = 20;
    static constexpr uint8_t programming_wait_ms = 20;
    static constexpr uint8_t enable_attempts = 3;
    ResultCode instruction(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t *value = nullptr);
    bool supports_rdy_bsy() const;
    ResultCode wait_for_programming_operation();
    ResultCode select_address(uint32_t address);
};
//------------------------------------------------------------------------------------------------
#include "avr-isp.tpp"
#endif // AVR_ISP_H
