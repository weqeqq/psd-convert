#define PSD_RESULT_MACRO__

#include <psd_cursor.h>
#include <psd_header.h>
#include <psd_read.h>
#include <psd_result.h>
#include <psd_section.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static psd_result_t PSD_RESULT__;

psd_result_t psd_skip_color_mode_data_section(psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        size_t section_size = 0;
        const size_t size = 4;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        section_size += buffer[0] << 24;
        section_size += buffer[1] << 16;
        section_size += buffer[2] << 8;
        section_size += buffer[3] << 0;

        free(buffer);

        psd_up_error(psd_cursor_set(cursor, cursor->current + section_size));
        return_psd_success(NULL);
}

psd_result_t psd_skip_image_resources_section(psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        size_t section_size = 0;
        const size_t size = 4;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        section_size += buffer[0] << 24;
        section_size += buffer[1] << 16;
        section_size += buffer[2] << 8;
        section_size += buffer[3] << 0;

        free(buffer);

        psd_up_error(psd_cursor_set(cursor, cursor->current + section_size));
        return_psd_success(NULL);
}

psd_result_t
psd_skip_layer_and_mask_information_section(psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        size_t section_size = 0;
        const size_t size = 4;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        section_size += buffer[0] << 24;
        section_size += buffer[1] << 16;
        section_size += buffer[2] << 8;
        section_size += buffer[3] << 0;

        free(buffer);

        psd_up_error(psd_cursor_set(cursor, cursor->current + section_size));
        return_psd_success(NULL);
}

// Read compression method.
psd_result_t read_compression_type(psd_compression_t *const out_buffer,
                                   psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        const size_t size = 2;
        *out_buffer = 0;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        *out_buffer += buffer[0] << 8;
        *out_buffer += buffer[1] << 0;

        free(buffer);

        if (*out_buffer > UNDEFINED_COMPRESSION)
                return_psd_error("Invalid compression type.");

        return_psd_success(NULL);
}

psd_result_t psd_read_image_data(const psd_header_t *const header,
                                 psd_cursor_t *const cursor)
{
        psd_compression_t *compression;
        const psd_channels_t channels = header->channels;
        const psd_width_t width = header->width;
        const psd_height_t height = header->height;

        compression = malloc(sizeof(psd_compression_t));
        psd_up_error(read_compression_type(compression, cursor));
        psd_up_error(read_and_decompress_data(channels, width, height,
                                              compression, cursor));

        free(compression);
        return_psd_success(psd_result__.pointer);
}
