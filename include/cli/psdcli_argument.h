#ifndef PSDCLI_ARGUMENT_H
#define PSDCLI_ARGUMENT_H

#include <psd_convert.h>

typedef struct psdcli_arguments {
        char *inp_path;
        char *out_path;
        int recursion_flag;
} psdcli_arguments_t;

psd_result_t arguments_parse(int argc, char **argv);

void arguments_destroy(psdcli_arguments_t *const arguments);

#endif
