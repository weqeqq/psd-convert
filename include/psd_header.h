#ifndef PSD_HEADER_H
#define PSD_HEADER_H

#include <psd_cursor.h>
#include <psd_result.h>
#include <psd_types.h>
#include <sys/types.h>

#define PSD_SIGNATURE_SIZE 4
#define PSD_VERSION_SIZE 2
#define PSD_RESERVED_SIZE 6
#define PSD_CHANNELS_SIZE 2
#define PSD_HEIGHT_SIZE 4
#define PSD_WIDTH_SIZE 4
#define PSD_DEPTH_SIZE 2
#define PSD_COLOR_MODE_SIZE 2

#define PSD_MAX_CHANNELS 56
#define PSD_MAX_WIDTH_PSD 30000
#define PSD_MAX_WIDTH_PSB 300000
#define PSD_MAX_HEIGHT_PSD 30000
#define PSD_MAX_HEIGHT_PSB 300000

#define PSD_VERSION_COND(value) ((value) < UNDEFINED_VERSION)
#define PSD_CHANNELS_COND(value) ((value) < PSD_MAX_CHANNELS)

#define PSD_HEIGHT_PSD_COND(value)                                             \
        ((value) < PSD_MAX_HEIGHT_PSD && (value) != 0)

#define PSD_HEIGHT_PSB_COND(value)                                             \
        ((value) < PSD_MAX_HEIGHT_PSB && (value) != 0)

#define PSD_WIDTH_PSD_COND(value) ((value) < PSD_MAX_WIDTH_PSD && (value) != 0)
#define PSD_WIDTH_PSB_COND(value) ((value) < PSD_MAX_WIDTH_PSB && (value) != 0)

#define PSD_DEPTH_COND(value)                                                  \
        ((value) == 1 || (value) == 8 || (value) == 16 || (value) == 32)

#define PSD_COLOR_MODE_COND(value)                                             \
        ((value) == BITMAP || (value) == GRAYSCALE || (value) == INDEXED ||    \
         (value) == RGB || (value) == CMYK || (value) == MULTICHANNEL ||       \
         (value) == DUOTONE || (value) == LAB)

typedef enum psd_version {
        PSD,
        PSB,
        UNDEFINED_VERSION,
} psd_version_t;

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

typedef struct psd_header {
        psd_version_t version;
        psd_channels_t channels;
        psd_height_t height;
        psd_width_t width;
        psd_depth_t depth;
        psd_color_mode_t color_mode;
} psd_header_t;

psd_result_t psd_read_signature(psd_cursor_t *const psd_cursor_ptr);

void print_version(const psd_version_t psd_version);

psd_result_t psd_read_version(psd_header_t *const psd_header_ptr,
                              psd_cursor_t *const psd_cursor_ptr);

psd_result_t psd_skip_reserved(psd_cursor_t *const psd_cursor_ptr);

psd_result_t psd_read_channels(psd_header_t *const psd_header_ptr,
                               psd_cursor_t *const psd_cursor_ptr);

psd_result_t psd_read_height(psd_header_t *const psd_header_ptr,
                             psd_cursor_t *const psd_cursor_ptr);

psd_result_t psd_read_width(psd_header_t *const psd_header_ptr,
                            psd_cursor_t *const psd_cursor_ptr);

psd_result_t psd_read_depth(psd_header_t *const psd_header_ptr,
                            psd_cursor_t *const psd_cursor_ptr);

void print_color_mode(const psd_color_mode_t psd_color_mode);

psd_result_t psd_read_color_mode(psd_header_t *const psd_header_ptr,
                                 psd_cursor_t *const psd_cursor_ptr);

void psd_header_print(const psd_header_t);

psd_result_t psd_header_read(psd_cursor_t *const psd_cursor_ptr);

void psd_header_destroy(psd_header_t *const psd_header_ptr);

#endif
