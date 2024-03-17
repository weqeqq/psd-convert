#define PSD_RESULT_MACRO__

#include <psd_cursor.h>
#include <psd_header.h>
#include <psd_result.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static psd_result_t PSD_RESULT__;

psd_result_t psd_read_signature(psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        u_int32_t sig1, sig2;

        sig1 = (0x38 << 24) + (0x42 << 16) + (0x50 << 8) + (0x53 << 0),
        sig2 = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_SIGNATURE_SIZE));
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

psd_result_t psd_read_version(psd_header_t *const header,
                              psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_version_t version;

        version = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_VERSION_SIZE));
        buffer = psd_result__.pointer;

        version += buffer[0] << 8;
        version += buffer[1] << 0;

        free(buffer);

        if (!PSD_VERSION_COND(version))
                return_psd_error("Header, read_version: Undefined version");

        header->version = version;
        return_psd_success(NULL);
}

psd_result_t skip_reserved(psd_cursor_t *const cursor)
{
        psd_cursor_set(cursor, cursor->current + PSD_RESERVED_SIZE);
        return_psd_success(NULL);
}

psd_result_t psd_read_channels(psd_header_t *const header,
                               psd_cursor_t *const cursor)
{

        psd_byte_t *buffer;
        psd_size_t channels;

        channels = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_CHANNELS_SIZE));
        buffer = psd_result__.pointer;

        channels += buffer[0] << 8;
        channels += buffer[1] << 0;

        free(buffer);

        if (!PSD_CHANNELS_COND(channels))
                return_psd_error("The number of channels is too high.");

        header->channels = channels;
        return_psd_success(NULL);
}

psd_result_t psd_read_height(psd_header_t *const header,
                             psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_size_t height;

        height = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_HEIGHT_SIZE));
        buffer = psd_result__.pointer;

        height += buffer[0] << 24;
        height += buffer[1] << 16;
        height += buffer[2] << 8;
        height += buffer[3] << 0;

        free(buffer);

        if (!PSD_HEIGHT_PSD_COND(height))
                return_psd_error("height is too high.");

        header->height = height;
        return_psd_success(NULL);
}

psd_result_t psd_read_width(psd_header_t *const psd_header,
                            psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_size_t width;

        width = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_WIDTH_SIZE));
        buffer = psd_result__.pointer;

        width += buffer[0] << 24;
        width += buffer[1] << 16;
        width += buffer[2] << 8;
        width += buffer[3] << 0;

        free(buffer);

        if (!PSD_WIDTH_PSD_COND(width))
                return_psd_error("Width is too high.");

        psd_header->width = width;
        return_psd_success(NULL);
}

psd_result_t psd_read_depth(psd_header_t *const header,
                            psd_cursor_t *const cursor)
{
        psd_byte_t *buffer;
        psd_size_t depth;

        depth = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_DEPTH_SIZE));
        buffer = psd_result__.pointer;

        depth += buffer[0] << 8;
        depth += buffer[1] << 0;

        free(buffer);

        if (!PSD_DEPTH_COND(depth))
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
                break;

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

psd_result_t psd_read_color_mode(psd_header_t *const header,
                                 psd_cursor_t *cursor)
{
        psd_byte_t *buffer;
        psd_color_mode_t color_mode;

        color_mode = 0;

        psd_up_error(psd_cursor_read(cursor, PSD_COLOR_MODE_SIZE));
        buffer = psd_result__.pointer;

        color_mode += buffer[0] << 8;
        color_mode += buffer[1] << 0;
        free(buffer);

        if (!PSD_COLOR_MODE_COND(color_mode))
                return_psd_error("Undefined color mode.");

        header->color_mode = color_mode;
        return_psd_success(NULL);
}

void psd_header_print(const psd_header_t header)
{
        printf("version: ");
        print_version(header.version);

        printf("channels: %ld\n", header.channels);

        printf("size: %ldx%ld\n", header.width, header.height);

        printf("depth: %ld\n", header.depth);

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

        psd_up_error_with_handle(psd_read_signature(cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(psd_read_version(header, cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(skip_reserved(cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(psd_read_channels(header, cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(psd_read_height(header, cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(psd_read_width(header, cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(psd_read_depth(header, cursor),
                                 psd_header_destroy(header));

        psd_up_error_with_handle(psd_read_color_mode(header, cursor),
                                 psd_header_destroy(header));

        return_psd_success(header);
}

void psd_header_destroy(psd_header_t *const header) { free(header); }
