#define PSD_RESULT_MACRO__

#include "psd_result.h"
#include <psdcli_argument.h>
#include <psdcli_pathut.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static psd_result_t PSD_RESULT__;
static int OPT;

#define INPUT 'i'
#define OUTPUT 'o'
#define RECURSION 'r'
#define HELP 'h'
#define UNDEFINED '?'

#define DEFAULT_INPUT NULL
#define DEFAULT_OUTPUT NULL
#define DEFAULT_RECURSION 0

psdcli_arguments_t *def_arguments()
{
        psdcli_arguments_t *self = malloc(sizeof(psdcli_arguments_t));

        self->inp_path = DEFAULT_INPUT;
        self->out_path = DEFAULT_OUTPUT;
        self->recursion_flag = DEFAULT_RECURSION;

        return self;
}

psd_result_t procopt(psdcli_arguments_t *const arguments)
{
        switch (OPT) {
        case INPUT:
                arguments->inp_path = optarg;
                break;

        case OUTPUT:
                arguments->out_path = optarg;
                break;

        case RECURSION:
                arguments->recursion_flag = 1;
                break;

        case UNDEFINED:
                return_psd_error("undefined argument");
                break;
        }

        return_psd_success(NULL);
}

void print_help()
{
        printf(

            "Help message:\n"
            " -%c (input path)\n"
            " -%c (output path)\n"
            " -%c (recursion flag)\n"
            " -%c (show this message)\n",

            INPUT, OUTPUT, RECURSION, HELP);
}

psd_result_t arguments_parse(int argc, char **argv)
{
#define GETOPT getopt(argc, argv, ":i:o:f:r")
#define OPTFAILURE -1

        psdcli_arguments_t *arguments;

        if (argc == 1) {
                print_help();
                return_psd_error("Arguments needed.");
        }

        arguments = def_arguments();
        while ((OPT = GETOPT) != OPTFAILURE)
                psd_up_error(procopt(arguments));

        if (arguments->inp_path == DEFAULT_INPUT)
                return_psd_error("Input path is required.");

        if (arguments->out_path == DEFAULT_OUTPUT)
                return_psd_error("Output path is required.");

        return_psd_success(arguments);
}

void arguments_destroy(psdcli_arguments_t *const arguments) { free(arguments); }
