#define PSD_RESULT_MACRO__

#include <psd_cursor.h>
#include <psd_read.h>
#include <psd_result.h>
#include <psd_types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static psd_result_t PSD_RESULT__;

psd_result_t read_channel_size(size_t *const out_buffer,
                               const psd_size_t height,
                               psd_cursor_t *const cursor)
{
        const size_t buffer_size = 2;
        *out_buffer = 0;

        for (u_int n = 0; n < height; ++n) {
                psd_byte_t *buffer;
                size_t size = 0;

                psd_up_error(psd_cursor_read(cursor, buffer_size));
                buffer = psd_result__.pointer;

                size += buffer[0] << 8;
                size += buffer[1] << 0;

                free(buffer);
                *out_buffer += size;
        }

        return_psd_success(NULL);
}

// Rle data decompreesing.
void rle(psd_byte_t *const inp_buffer, //
         psd_byte_t *const out_buffer, //
         size_t const SIZE)            //
{
        size_t inp_n = 0;
        size_t out_n = 0;

        for (; inp_n < SIZE;) {
                char value = inp_buffer[inp_n];
                inp_n++;

                if (value > 0) {
                        size_t unique = value + 1;

                        for (size_t n = 0; n < unique; ++n) {
                                out_buffer[out_n] = inp_buffer[inp_n];
                                inp_n++;
                                out_n++;
                        }

                } else {
                        size_t repeat = abs(value) + 1;

                        for (size_t n = 0; n < repeat; ++n) {
                                out_buffer[out_n] = inp_buffer[inp_n];
                                out_n++;
                        }

                        inp_n++;
                }
        }
}

psd_result_t decompress_data(psd_byte_t *const inp_buffer,               //
                             psd_byte_t *const out_buffer,               //
                             size_t const SIZE,                          //
                             const psd_compression_t *const compression) //
{
        switch (*compression) {
        case RLE:
                rle(inp_buffer, out_buffer, SIZE);
                return_psd_success(NULL);

        case ZIP_WITH_PREDICTION:
                return_psd_error("Zip with does not support now.");

        case ZIP_WITHOUT_PREDICTION:
                return_psd_error(
                    "Zip without prediction does not support now.");

        default:
                return_psd_error("Undefined image data compression method.");
        }
}

// Read and decompress data.
psd_result_t read_and_decompress_data(
    const psd_size_t channels, const psd_size_t width, const psd_size_t height,
    const psd_compression_t *const compression, psd_cursor_t *const cursor)
{
        size_t decompressed_channel_size;
        size_t decompressed_buffer_size;

        psd_byte_t *decompressed_buffer;
        size_t *compressed_channel_sizes;

        decompressed_channel_size = width * height;
        decompressed_buffer_size = decompressed_channel_size * channels;

        compressed_channel_sizes = malloc(channels * sizeof(size_t));
        decompressed_buffer = malloc(decompressed_buffer_size);

        for (size_t n = 0; n < channels; ++n)
                psd_up_error(read_channel_size(&compressed_channel_sizes[n],
                                               height, cursor));

        for (size_t n = 0; n < channels; n++) {
                psd_byte_t *compressed_channel;
                psd_byte_t *decompressed_channel;

                psd_up_error(
                    psd_cursor_read(cursor, compressed_channel_sizes[n]));

                compressed_channel = psd_result__.pointer;
                decompressed_channel = malloc(decompressed_channel_size);

                psd_up_error(
                    decompress_data(compressed_channel, decompressed_channel,
                                    compressed_channel_sizes[n], compression));

                for (size_t buffer_i = n, channel_i = 0;
                     buffer_i < decompressed_buffer_size;
                     buffer_i += channels, channel_i++) {

                        decompressed_buffer[buffer_i] =
                            decompressed_channel[channel_i];
                }

                free(compressed_channel);
                free(decompressed_channel);
        }

        free(compressed_channel_sizes);
        return_psd_success(decompressed_buffer);
}
