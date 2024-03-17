#include <psd_endian.h>

psd_u8_t psd_u8_from_bendian(const psd_byte_t *const buffer) { return *buffer; }

psd_u16_t psd_u16_from_bendian(const psd_byte_t *const buffer)
{
        psd_u16_t number;
        number = 0;

        number += *(buffer + 0) << 8;
        number += *(buffer + 1) << 0;

        return number;
}

psd_u32_t psd_u32_from_bendian(const psd_byte_t *const buffer)
{
        psd_u32_t number;
        number = 0;

        number += *(buffer + 0) << 24;
        number += *(buffer + 1) << 16;
        number += *(buffer + 2) << 8;
        number += *(buffer + 3) << 0;

        return number;
}

psd_i8_t psd_i8_from_bendian(const psd_byte_t *const buffer) { return *buffer; }

psd_i16_t psd_i16_from_bendian(const psd_byte_t *const buffer)
{
        psd_i16_t number;
        number = 0;

        number += *(buffer + 0) << 8;
        number += *(buffer + 1) << 0;

        return number;
}

psd_i32_t psd_i32_from_bendian(const psd_byte_t *const buffer)
{
        psd_i32_t number;
        number = 0;

        number += *(buffer + 0) << 24;
        number += *(buffer + 1) << 16;
        number += *(buffer + 2) << 8;
        number += *(buffer + 3) << 0;

        return number;
}
