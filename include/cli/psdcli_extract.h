#ifndef PSDCLI_EXTRACT_H
#define PSDCLI_EXTRACT_H

#include <psd_convert.h>

psd_result_t extract_image_p(const psd_header_t *const psd_header_ptr,
                             psd_cursor_t *const psd_cursor_ptr);

psd_result_t extract_image_pp(const psd_header_t *const psd_header,
                              psd_cursor_t *const psd_cursor_ptr);

#endif
