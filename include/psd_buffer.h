#ifndef PSD_BUFFER_H
#define PSD_BUFFER_H

#define psd_assign_bufferp(buffer_variable, size, values...)                   \
        {                                                                      \
                psd_byte_t psd_tmp_buffer__[size] = values;                    \
                                                                               \
                buffer_variable = (psd_byte_t *)malloc(size);                  \
                                                                               \
                for (psd_size_t i = 0; i < (size); ++i) {                      \
                        buffer_variable[i] = psd_tmp_buffer__[i];              \
                }                                                              \
        }

#define psd_assign_bufferpp(buffer_variable, rows, cols, values...)            \
        {                                                                      \
                psd_byte_t psd_tmp_buffer__[(rows) * (cols)] = values;         \
                                                                               \
                buffer_variable =                                              \
                    (psd_byte_t **)malloc((rows) * sizeof(psd_byte_t *));      \
                                                                               \
                for (psd_size_t i = 0, n = 0; i < (rows); ++i) {               \
                        buffer_variable[i] = (psd_byte_t *)malloc((cols));     \
                                                                               \
                        for (psd_size_t j = 0; j < (cols); ++j, ++n) {         \
                                buffer_variable[i][j] = psd_tmp_buffer__[n];   \
                        }                                                      \
                }                                                              \
        }

#endif
