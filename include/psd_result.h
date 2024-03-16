#ifndef PSD_RESULT_H
#define PSD_RESULT_H

#include <stdbool.h>
#include <sys/types.h>

typedef struct psd_result {
        void *pointer;
        char *content;
        int is_error;
} psd_result_t;

#ifdef PSD_RESULT_MACRO__
#define PSD_RESULT__ psd_result__;

#include <stdlib.h>

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

#endif

#endif
