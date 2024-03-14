#ifndef PSD_RESULT_H
#define PSD_RESULT_H

#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct psd_result {
        void *pointer;
        char *content;
        int is_error;
} psd_result_t;

#define INIT_PSD_RESULT static psd_result_t psd_result__;

#define return_psd_success(ptr)                                                \
        do {                                                                   \
                psd_result__.pointer = (ptr);                                  \
                psd_result__.is_error = 0;                                     \
                                                                               \
                return psd_result__;                                           \
        } while (0)

#define return_psd_error(text)                                                 \
        do {                                                                   \
                psd_result__.pointer = NULL;                                   \
                psd_result__.is_error = 1;                                     \
                psd_result__.content = (text);                                 \
                                                                               \
                return psd_result__;                                           \
        } while (0)

#define psd_up_error(func)                                                     \
        do {                                                                   \
                psd_result__ = (func);                                         \
                                                                               \
                if (psd_result__.is_error)                                     \
                        return psd_result__;                                   \
        } while (0)

#endif

#define psd_up_error_with_handle(func, handle)                                 \
        do {                                                                   \
                psd_result__ = (func);                                         \
                                                                               \
                if (psd_result__.is_error) {                                   \
                        handle;                                                \
                        return psd_result__;                                   \
                }                                                              \
        } while (0);

#define psd_unwrap_result(func)                                                \
        do {                                                                   \
                psd_result__ = (func);                                         \
                                                                               \
                if (psd_result__.is_error) {                                   \
                        puts(psd_result__.content);                            \
                        exit(1);                                               \
                }                                                              \
        } while (0)
