#include <psd_cursor.h>
#include <psd_header.h>
#include <psd_result.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

INIT_PSD_RESULT;

psd_result_t read_signature(psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        u_int32_t sig1, sig2;
        size_t size;

        sig1 = (0x38 << 24) + (0x42 << 16) + (0x50 << 8) + (0x53 << 0),
        sig2 = 0, size = 4;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        sig2 += buffer[0] << 24;
        sig2 += buffer[1] << 16;
        sig2 += buffer[2] << 8;
        sig2 += buffer[3] << 0;

        free(buffer);

        if (sig1 != sig2)
                return_psd_error(
                    "header, read_signature: signature is not correct.");

        return_psd_success(NULL);
}

void print_version(const psd_version_t version)
{
        switch (version) {

        case PSD:
                puts("Psd");
                break;

        case PSB:
                puts("Psb");
                break;

        default:
                puts("Undefined psd version.");
        }
}

psd_result_t read_version(psd_header_t *const header,
                          psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_version_t version;
        size_t size;

        version = 0, size = 2;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        version += buffer[0] << 8;
        version += buffer[1] << 0;

        free(buffer);

        if (version > UNDEFINED_VERSION)
                return_psd_error("Header, read_version: Undefined version");

        header->version = version;
        return_psd_success(NULL);
}

psd_result_t skip_reserved(psd_cursor_t *const cursor)
{
        const size_t size = 6;
        psd_cursor_set(cursor, cursor->current + size);
        return_psd_success(NULL);
}

psd_result_t read_channels(psd_header_t *const header,
                           psd_cursor_t *const cursor)
{

        psd_byte_t *buffer;
        psd_channels_t channels;
        size_t buffer_size;

        channels = 0, buffer_size = 2;

        psd_up_error(psd_cursor_read(cursor, buffer_size));
        buffer = psd_result__.pointer;

        channels += buffer[0] << 8;
        channels += buffer[1] << 0;

        free(buffer);

        if (channels > MAX_PSD_PSB_CHANNELS)
                return_psd_error("The number of channels is too high.");

        header->channels = channels;
        return_psd_success(NULL);
}

psd_result_t read_height(psd_header_t *const header, psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_height_t height;
        size_t buffer_size;

        height = 0, buffer_size = 4;

        psd_up_error(psd_cursor_read(cursor, buffer_size));
        buffer = psd_result__.pointer;

        height += buffer[0] << 24;
        height += buffer[1] << 16;
        height += buffer[2] << 8;
        height += buffer[3] << 0;

        free(buffer);

        if (height > MAX_PSD_HEIGHT || height == 0)
                return_psd_error("height is too high.");

        header->height = height;
        return_psd_success(NULL);
}

psd_result_t read_width(psd_header_t *const psd_header,
                        psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_width_t width;
        size_t size;

        width = 0, size = 4;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        width += buffer[0] << 24;
        width += buffer[1] << 16;
        width += buffer[2] << 8;
        width += buffer[3] << 0;

        free(buffer);

        if (width > MAX_PSD_WIDTH || width == 0)
                return_psd_error("Width is too high.");

        psd_header->width = width;
        return_psd_success(NULL);
}

psd_result_t read_depth(psd_header_t *const header, psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_depth_t depth;
        size_t size;

        depth = 0, size = 2;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        depth += buffer[0] << 8;
        depth += buffer[1] << 0;

        free(buffer);

        if (depth != 0x01 && depth != 0x08 && depth != 0x10 && depth != 0x20)
                return_psd_error("erro psd depth");

        header->depth = depth;
        return_psd_success(NULL);
}

void print_color_mode(const psd_color_mode_t color_mode)
{
        switch (color_mode) {

        case BITMAP:
                puts("Bitmap");
                break;

        case GRAYSCALE:
                puts("Grayscale");

        case INDEXED:
                puts("Indexed");
                break;

        case RGB:
                puts("RGB");
                break;

        case CMYK:
                puts("CMYK");
                break;

        case MULTICHANNEL:
                puts("Multichannel");
                break;

        case DUOTONE:
                puts("Duotone");
                break;

        case LAB:
                puts("Lab");
                break;

        default:
                puts("Undefined");
        }
}

psd_result_t read_color_mode(psd_header_t *const header, psd_cursor_t *cursor)
{
        psd_byte_t *buffer;
        psd_color_mode_t color_mode;
        size_t size;

        color_mode = 0, size = 2;

        psd_up_error(psd_cursor_read(cursor, size));
        buffer = psd_result__.pointer;

        color_mode += buffer[0] << 8;
        color_mode += buffer[1] << 0;
        free(buffer);

        if (color_mode != 0x00 && color_mode != 0x01 && color_mode != 0x02 &&
            color_mode != 0x03 && color_mode != 0x04 && color_mode != 0x07 &&
            color_mode != 0x08 && color_mode != 0x09)
                return_psd_error("Undefined color mode.");

        header->color_mode = color_mode;
        return_psd_success(NULL);
}

void psd_header_print(const psd_header_t header)
{
        printf("version: ");
        print_version(header.version);

        printf("channels: %d\n", header.channels);

        printf("size: %dx%d\n", header.width, header.height);

        printf("depth: %d\n", header.depth);

        printf("color_mode: ");
        print_color_mode(header.color_mode);
}

/*
 *  Length. Description.
 * |    4 | Signature: always equal to '8BPS'.
 * |    2 | Version: always equal to 1. (PSB version is 2)
 * |    6 | Reserved: must be zero.
 * |    2 | The number of channels in the image.
 * |    4 | The height of the image.
 * |    4 | The width of the image.
 * |    2 | The Depth.
 * |    2 | The color mode.
 *
 */
psd_result_t psd_header_read(psd_cursor_t *const cursor)
{
        psd_header_t *header;
        header = malloc(sizeof(psd_header_t));

        psd_up_error(read_signature(cursor));

        psd_up_error(read_version(header, cursor));

        psd_up_error(skip_reserved(cursor));

        psd_up_error(read_channels(header, cursor));

        psd_up_error(read_height(header, cursor));

        psd_up_error(read_width(header, cursor));

        psd_up_error(read_depth(header, cursor));

        psd_up_error(read_color_mode(header, cursor));

        return_psd_success(header);
}

void psd_header_destroy(psd_header_t *const header) { free(header); }
