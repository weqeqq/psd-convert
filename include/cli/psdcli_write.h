#ifndef PSDCLI_WRITE_PNG_H
#define PSDCLI_WRITE_PNG_H

#include <psd_convert.h>

psd_result_t write_image(const char *const output_path_str,        //
                         const psd_header_t *const psd_header_ptr, //
                         psd_byte_t **const image_buffer_ptr_ptr); //

#endif
