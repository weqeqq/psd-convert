#ifndef READ_PSD_H
#define READ_PSD_H

#include <psd_cursor.h>
#include <psd_header.h>
#include <psd_types.h>
#include <sys/types.h>

typedef enum psd_compression {
        RAW,                    // 0
        RLE,                    // 1
        ZIP_WITHOUT_PREDICTION, // 2
        ZIP_WITH_PREDICTION,    // 3
        UNDEFINED_COMPRESSION,  // 4
} psd_compression_t;

psd_result_t read_and_decompress_data(              //
    const psd_channels_t channels,                  //
    const psd_width_t width,                        //
    const psd_height_t height,                      //
    const psd_compression_t *const compression_ptr, //
    psd_cursor_t *const psd_cursor);                //

#endif
