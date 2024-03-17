#ifndef PSD_ENDIAN_H
#define PSD_ENDIAN_H

#include <psd_types.h>

psd_u8_t psd_u8_from_bendian(const psd_byte_t *const buffer);

psd_u16_t psd_u16_from_bendian(const psd_byte_t *const buffer);

psd_u32_t psd_u32_from_bendian(const psd_byte_t *const buffer);

psd_i8_t psd_i8_from_bendian(const psd_byte_t *const buffer);

psd_i16_t psd_i16_from_bendian(const psd_byte_t *const buffer);

psd_i32_t psd_i32_from_bendian(const psd_byte_t *const buffer);

#endif
