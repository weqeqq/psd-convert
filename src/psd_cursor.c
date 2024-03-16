#define PSD_RESULT_MACRO__

#include <psd_cursor.h>
#include <psd_result.h>
#include <psd_types.h>

#include <stdlib.h>

static psd_result_t PSD_RESULT__;

psd_result_t psd_cursor_from_buffer(psd_byte_t *const buffer,
                                    const size_t buffer_size)
{
        psd_cursor_t *cursor;
        cursor = malloc(sizeof(psd_cursor_t));

        if (cursor == NULL)
                return_psd_error("Failed to allocate memory.");

        cursor->size = buffer_size;
        cursor->data = buffer;
        cursor->current = 0;

        return_psd_success(cursor);
}

psd_result_t psd_cursor_from_stream(FILE *const stream)
{
#define FREAD_BUFFER fread(buffer, sizeof(psd_byte_t), buffer_size, stream)

        size_t buffer_size;
        psd_byte_t *buffer;
        psd_cursor_t *cursor;

        fseek(stream, 0, SEEK_END);
        buffer_size = ftell(stream);
        rewind(stream);

        buffer = malloc(buffer_size);

        if (FREAD_BUFFER != buffer_size)
                return_psd_error("Failed to read file data.");

        psd_up_error(psd_cursor_from_buffer(buffer, buffer_size));
        cursor = psd_result__.pointer;

        return_psd_success(cursor);
}

psd_result_t psd_cursor_from_file(const char *const filename)
{
        psd_cursor_t *cursor;
        FILE *stream;

        stream = fopen(filename, "rb");

        psd_up_error(psd_cursor_from_stream(stream));
        cursor = psd_result__.pointer;

        fclose(stream);
        return_psd_success(cursor);
}

psd_result_t psd_cursor_read(psd_cursor_t *const cursor, //
                             const size_t read_size)     //
{
        psd_byte_t *read_buffer;

        if (read_size > cursor->size - cursor->current)
                return_psd_error("psd_cursor_read: read_size greater then "
                                 "available cursor size.");

        read_buffer = malloc(read_size);

        for (size_t i = 0; i < read_size; i++)
                read_buffer[i] = cursor->data[cursor->current++];

        return_psd_success(read_buffer);
}

psd_result_t psd_cursor_set(psd_cursor_t *const cursor, //
                            const size_t new_pos)       //
{
        if (new_pos < cursor->size) {
                cursor->current = new_pos;
                return_psd_success(NULL);
        }

        return_psd_error(
            "psd_cursor_set: new_pos is greater then cursor size.");
}

void psd_cursor_destroy(psd_cursor_t *const cursor)
{
        free(cursor->data);
        free(cursor);
}
