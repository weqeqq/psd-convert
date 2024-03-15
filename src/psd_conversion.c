#include <psd_conversion.h>

psd_byte_t **bytep_to_bytepp(const psd_header_t *const header,
                             psd_byte_t *const bufferp)
{
        psd_byte_t **bufferpp;
        psd_size_t width, height, channels;

        width = header->width;
        height = header->height;
        channels = header->channels;

        bufferpp = malloc(sizeof(psd_byte_t *) * height);

        for (psd_size_t i = 0; i < height; ++i)
                bufferpp[i] = malloc(width * channels);

        return bufferpp;
}

psd_byte_t **bytep_to_bytepp_with_free(const psd_header_t *const header,
                                       psd_byte_t *const bufferp)
{
        psd_byte_t **bufferpp;

        bufferpp = bytep_to_bytepp(header, bufferp);
        free(bufferp);

        return bufferpp;
}

psd_byte_t *bytepp_to_bytep(const psd_header_t *const header,
                            psd_byte_t **const bufferpp)
{
        psd_byte_t *bufferp;
        psd_size_t width, height, channels;

        width = header->width;
        height = header->height;
        channels = header->channels;

        bufferp = malloc(width * height * channels);

        for (psd_size_t i = 0, n = 0; i < height; ++i)
                for (psd_size_t j = 0; j < width * channels; ++j, ++n)
                        bufferp[n] = bufferpp[i][j];

        return bufferp;
}

psd_byte_t *bytepp_to_bytep_with_free(const psd_header_t *const header,
                                      psd_byte_t **const bufferpp)
{
        psd_byte_t *bufferp;
        psd_size_t height;

        bufferp = bytepp_to_bytep(header, bufferpp);

        height = header->height;
        for (psd_size_t i = 0; i < height; ++i)
                free(bufferpp[i]);

        return bufferp;
}
