#define PSD_RESULT_MACRO__

#include <psdcli_pathut.h>
#include <psdcli_write.h>

#include <libpng16/png.h>
#include <psd_result.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "psd_header.h"
#include "psd_types.h"

static psd_result_t PSD_RESULT__;

int convert_color_structure(const psd_color_mode_t from)
{
        switch (from) {

        case BITMAP:
                return -1;

        case GRAYSCALE:
                return PNG_COLOR_TYPE_GRAY;

        case INDEXED:
                return -1;

        case RGB:
                return PNG_COLOR_TYPE_RGB;

        case CMYK:
                return -1;

        case MULTICHANNEL:
                return -1;

        case DUOTONE:
                return -1;

        case LAB:
                return -1;

        default:
                return -1;
        }
}

psd_result_t create_write()
{
        png_struct *png =
            png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (png == NULL)
                return_psd_error("null value on png strcut");

        return_psd_success(png);
}

psd_result_t create_info(png_struct *png)
{
        png_info *info = png_create_info_struct(png);

        if (png == NULL)
                return_psd_error("null info");

        return_psd_success(info);
}

psd_result_t set_IHDR(const psd_header_t *const header, //
                      png_struct *const png,            //
                      png_info *const info)             //
{
        psd_size_t width, height, depth;

        width = header->width;
        height = header->height;
        depth = header->depth;

        int color, interlace, compression, filter;
        color = convert_color_structure(header->color_mode);

        if (color == -1)
                return_psd_error("color error");

        interlace = PNG_INTERLACE_NONE;
        compression = PNG_COMPRESSION_TYPE_DEFAULT;
        filter = PNG_FILTER_TYPE_DEFAULT;

        png_set_IHDR(                        //
            png, info, width,                //
            height, depth, color,            //
            interlace, compression, filter); //

        png_write_info(png, info);

        return_psd_success(NULL);
}

psd_result_t write_image(const char *const out,            //
                         const psd_header_t *const header, //
                         psd_byte_t **const bufferpp)      //
{
        char *fin_out = path_set_extension(out, "png");
        FILE *stream = fopen(fin_out, "wb");
        free(fin_out);

        psd_up_error(create_write());
        png_struct *png = psd_result__.pointer;

        psd_up_error(create_info(png));
        png_info *info = psd_result__.pointer;

        png_init_io(png, stream);

        psd_up_error(set_IHDR(header, png, info));
        png_write_info(png, info);
        png_write_image(png, bufferpp);
        png_write_end(png, NULL);

        fclose(stream);
        png_destroy_write_struct(&png, &info);

        return_psd_success(NULL);
}
