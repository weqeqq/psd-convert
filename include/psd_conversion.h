#ifndef PSD_CONVERSIONS_H
#define PSD_CONVERSIONS_H

#include <psd_header.h>
#include <psd_types.h>

psd_byte_t **bytep_to_bytepp(const psd_header_t *const psd_header_ptr,
                             psd_byte_t *const buffer_ptr);

psd_byte_t **bytep_to_bytepp_with_free(const psd_header_t *const psd_header_ptr,
                                       psd_byte_t *const buffer_ptr);

psd_byte_t *bytepp_to_bytep(const psd_header_t *const psd_header_ptr,
                            psd_byte_t **const buffer_ptr_ptr);

psd_byte_t *bytepp_to_bytep_with_free(const psd_header_t *const psd_header_ptr,
                                      psd_byte_t **const buffer_ptr_ptr);

#endif
