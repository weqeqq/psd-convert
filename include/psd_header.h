#ifndef PHEADER_H
#define PHEADER_H

#include <psd_cursor.h>
#include <psd_result.h>
#include <psd_types.h>
#include <sys/types.h>

#define MAX_PSD_PSB_CHANNELS 56
#define MAX_PSD_WIDTH 30000
#define MAX_PSB_WIDTH 300000
#define MAX_PSD_HEIGHT 30000
#define MAX_PSB_HEIGHT 300000

typedef enum psd_version {
        PSD,
        PSB,
        UNDEFINED_VERSION,
} psd_version_t;

void print_version(const psd_version_t psd_version);

typedef enum psd_color_mode {
        BITMAP,
        GRAYSCALE,
        INDEXED,
        RGB,
        CMYK,
        MULTICHANNEL = 7,
        DUOTONE,
        LAB,
        UNDEFINED_COLOR_MODE,
} psd_color_mode_t;

void print_color_mode(const psd_color_mode_t psd_color_mode);

typedef struct psd_header {
        psd_version_t version;
        psd_channels_t channels;
        psd_height_t height;
        psd_width_t width;
        psd_depth_t depth;
        psd_color_mode_t color_mode;
} psd_header_t;

void psd_header_print(const psd_header_t);

psd_result_t psd_header_read(psd_cursor_t *const psd_cursor_ptr);

void psd_header_destroy(psd_header_t *const psd_header_ptr);

#endif
