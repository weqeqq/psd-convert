#define PSD_RESULT_MACRO__

#include <psdcli_argument.h>
#include <psdcli_extract.h>
#include <psdcli_pathut.h>
#include <psdcli_write.h>

#include <psd_cursor.h>

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

static psd_result_t PSD_RESULT__;

psd_result_t convert_file(const char *const input_psd_path,
                          const char *const output_image_path);

psd_result_t convert_dir(const char *const input_directory,
                         const char *const output_directory,
                         const int recursion_flag);

int main(int argc, char **argv)
{
        psdcli_arguments_t *arguments;
        int recursion_flag;
        char *inp, *out;

        double start, end;
        start = clock();

        psd_unwrap_result(arguments_parse(argc, argv));
        arguments = psd_result__.pointer;

        recursion_flag = arguments->recursion_flag;
        inp = arguments->inp_path;
        out = arguments->out_path;
        arguments_destroy(arguments);

        if (!path_is_exists(inp)) {
                puts("main: Input path does not exists.");
                exit(EXIT_FAILURE);
        }

        if (path_is_file(inp))
                psd_unwrap_result(convert_file(inp, out));

        if (path_is_directory(inp))
                psd_unwrap_result(convert_dir(inp, out, recursion_flag));

        end = clock();
        printf("Success, elapsed: %f sec.", (end - start) / CLOCKS_PER_SEC);

        return EXIT_SUCCESS;
}

psd_result_t convert_file(const char *const inp, const char *const out)
{
#define bufferpp_destroy                                                       \
        for (size_t i = 0; i < header->height; ++i)                            \
                free(buffer[i]);                                               \
                                                                               \
        free(buffer)

        psd_cursor_t *cursor;
        psd_header_t *header;
        psd_byte_t **buffer;

        if (!path_is_exists(inp))
                return_psd_error("convert_file, path_is_exists:"
                                 "Input path does not exists.");

        if (!path_parent_directory_is_exists(out))
                return_psd_error("convert_file,"
                                 "path_parent_directory_is_exists:"
                                 "Output path does not exists.");

        printf("%s -> ", inp);

        psd_up_error(psd_cursor_from_file(inp));
        cursor = psd_result__.pointer;

        psd_up_error_with_handle(psd_header_read(cursor), puts("err");
                                 psd_cursor_destroy(cursor));
        header = psd_result__.pointer;

        psd_up_error_with_handle(extract_image_pp(header, cursor), puts("err");
                                 psd_cursor_destroy(cursor);
                                 psd_header_destroy(header));
        buffer = psd_result__.pointer;

        psd_up_error_with_handle(write_image(out, header, buffer), puts("err");
                                 bufferpp_destroy; psd_cursor_destroy(cursor);
                                 psd_header_destroy(header));

        bufferpp_destroy;
        psd_header_destroy(header);
        psd_cursor_destroy(cursor);

        puts("ok");
        return_psd_success(NULL);
}

psd_result_t convert_dir(const char *const inp, const char *const out,
                         const int recursion_flag)
{

        struct dirent *entry;
        DIR *directory;

        if (!path_is_exists(inp))
                return_psd_error("convert_dir, path_is_exists:"
                                 "Input directory does not exists.");

        if (!path_parent_directory_is_exists(out))
                return_psd_error("convert_dir, path_is_exists:"
                                 "Output parent directory does not exists.");

        if (!path_is_exists(out))
                mkdir(out, S_IRWXU);

        directory = opendir(inp);
        if (directory == NULL)
                return_psd_error("convert_dir, opendir:"
                                 "Return NULL value.");

        while ((entry = readdir(directory)) != NULL) {

#define free_string                                                            \
        free(fin_inp);                                                         \
        free(fin_out);

                char *base_name;
                base_name = entry->d_name;

                if (!strcmp(base_name, ".") || !strcmp(base_name, ".."))
                        continue;

                char *fin_inp = path_join(inp, base_name);
                char *fin_out = path_join(out, base_name);

                if (path_is_file(fin_inp))

                        psd_up_error_with_handle(convert_file(fin_inp, fin_out),
                                                 free_string);

                if (!recursion_flag) {
                        free_string;
                        continue;
                }

                if (path_is_directory(fin_inp))

                        psd_up_error_with_handle(
                            convert_dir(fin_inp, fin_out, recursion_flag),
                            free_string);

                free_string;
        }

        closedir(directory);
        return_psd_success(NULL);
}
