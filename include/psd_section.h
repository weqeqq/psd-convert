#ifndef PSD_SECTION_H
#define PSD_SECTION_H

#include <psd_header.h>

psd_result_t //
psd_skip_color_mode_data_section(psd_cursor_t *const psd_cursor_ptr);

psd_result_t //
psd_skip_image_resources_section(psd_cursor_t *const psd_cursor_ptr);

psd_result_t //
psd_skip_layer_and_mask_information_section(psd_cursor_t *const psd_cursor_ptr);

psd_result_t psd_read_image_data(const psd_header_t *const psd_header,
                                 psd_cursor_t *const psd_cursor_ptr);

#endif
