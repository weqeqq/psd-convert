#ifndef PCURSOR_H
#define PCURSOR_H

#include <psd_result.h>
#include <psd_types.h>

#include <stdio.h>
#include <sys/types.h>

typedef struct psd_cursor {
        size_t current;
        size_t size;
        size_t elsize;
        psd_byte_t *data;
} psd_cursor_t;

psd_result_t psd_cursor_from_buffer(psd_byte_t *const buffer_ptr,
                                    const size_t buffer_size);

psd_result_t psd_cursor_from_stream(FILE *const stream);

psd_result_t psd_cursor_from_file(const char *const file_name);

psd_result_t psd_cursor_read(psd_cursor_t *const psd_cursor,
                             const size_t read_size);

psd_result_t psd_cursor_set(psd_cursor_t *const psd_cursor,
                            const size_t new_pos);

void psd_cursor_destroy(psd_cursor_t *const psd_cursor);

#endif
