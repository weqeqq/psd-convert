#include <psdcli_pathut.h>

#include <dirent.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char *remove_last_char_if_needed(const char *const str, const char inp_char)
{
        char *final;
        size_t str_size, last_str_ind, final_size, last_final_ind;

        str_size = strlen(str);
        last_str_ind = str_size - 1;

        final_size = (*(str + last_str_ind) == inp_char)
                         ? str_size - sizeof((char)inp_char)
                         : str_size;
        last_final_ind = final_size - 1;

        final = malloc(final_size + STR_NULL_CHAR_SIZE);
        strncpy(final, str, final_size);

        *(final + last_final_ind + STR_NULL_CHAR_SIZE) = STR_NULL_CHAR;
        return final;
}

char *remove_last_path_sep_if_needed(const char *const str)
{
        return remove_last_char_if_needed(str, PATH_SEP_CHAR);
}

char *remove_last_ext_sep_if_needed(const char *const str)
{
        return remove_last_char_if_needed(str, EXT_SEP_CHAR);
}

char *path_join(const char *const str1, const char *const str2)
{
        char *str1_without_path_sep, *final;
        size_t str1_without_path_sep_size, str2_size, final_size,
            final_last_ind;

        str1_without_path_sep = remove_last_char_if_needed(str1, PATH_SEP_CHAR);
        str1_without_path_sep_size = strlen(str1_without_path_sep);

        if (path_is_absolute(str2))
                return str1_without_path_sep;
        str2_size = strlen(str2);

        final_size =
            str1_without_path_sep_size + str2_size + PATH_SEP_CHAR_SIZE;
        final_last_ind = final_size - 1;
        final = malloc(final_size + STR_NULL_CHAR_SIZE);

        strcpy(final, str1_without_path_sep);
        strcat(final, PATH_SEP_STR);
        strcat(final, str2);

        *(final + final_last_ind + STR_NULL_CHAR_SIZE) = STR_NULL_CHAR;

        free(str1_without_path_sep);
        return final;
}

int path_is_file(const char *const str)
{
        struct stat str_stat;

        if (stat(str, &str_stat) == -1)
                return 0;

        return S_ISREG(str_stat.st_mode);
}

int path_is_directory(const char *const str)
{
        struct stat str_stat;

        if (stat(str, &str_stat) == -1)
                return 0;

        return S_ISDIR(str_stat.st_mode);
}

int path_is_exists(const char *const str)
{
        struct stat str_stat;

        if (stat(str, &str_stat) == -1)
                return 0;

        return 1;
}

char *path_extension(const char *const str)
{
        char *final, *ext;
        size_t ext_size, final_size, final_last_ind;

        ext = strrchr(str, EXT_SEP_CHAR);
        ext_size = strlen(ext);

        final_size = ext_size - EXT_SEP_CHAR_SIZE;
        final_last_ind = final_size - 1;
        final = malloc(final_size + STR_NULL_CHAR_SIZE);

        memmove(final, ext + EXT_SEP_CHAR_SIZE, ext_size - EXT_SEP_CHAR_SIZE);
        *(final + final_last_ind + STR_NULL_CHAR_SIZE) = STR_NULL_CHAR;

        return final;
}

char *path_remove_extension(const char *const str)
{
        char *ext, *final;
        size_t ext_size, str_size, final_size, final_last_ind;

        ext = path_extension(str);
        ext_size = strlen(ext);
        free(ext);

        if (ext_size == 0)
                return strdup(str);
        str_size = strlen(str);

        final_size = str_size - EXT_SEP_CHAR_SIZE - ext_size;
        final_last_ind = final_size - 1;
        final = malloc(final_size + STR_NULL_CHAR_SIZE);

        strncpy(final, str, final_size);
        *(final + final_last_ind + STR_NULL_CHAR_SIZE) = STR_NULL_CHAR;

        return final;
}

char *path_remove_extension_with_free(char *const str)
{
        char *final;

        final = path_remove_extension(str);
        free(str);

        return final;
}

char *path_append_extension(const char *const str, const char *const ext)
{
        char *str_without_ext_sep, *final;
        size_t str_without_ext_sep_size, ext_size, final_size, final_last_ind;

        ext_size = strlen(ext);
        if (ext_size == 0)
                return strdup(str);

        str_without_ext_sep = remove_last_ext_sep_if_needed(str);
        str_without_ext_sep_size = strlen(str_without_ext_sep);

        final_size = str_without_ext_sep_size + EXT_SEP_CHAR + ext_size;
        final_last_ind = final_size - 1;
        final = malloc(final_size + STR_NULL_CHAR_SIZE);

        strcpy(final, str_without_ext_sep);
        strcat(final, EXT_SEP_STR);
        strcat(final, ext);

        *(final + final_last_ind + STR_NULL_CHAR_SIZE) = STR_NULL_CHAR;

        free(str_without_ext_sep);
        return final;
}

char *path_append_extension_with_free(char *const str, const char *const ext)
{
        char *final;

        final = path_append_extension(str, ext);
        free(str);

        return final;
}

char *path_set_extension(const char *const str, const char *const ext)
{
        char *final;

        if (!strcmp(ext, EMPTY_STR))
                return strdup(str);

        final = path_remove_extension(str);
        final = path_append_extension_with_free(final, ext);

        return final;
}

char *path_set_extension_with_free(char *const str, const char *const ext)
{
        char *final;

        final = path_set_extension(str, ext);
        free(str);

        return final;
}

int path_is_absolute(const char *const str)
{
        if (*str != PATH_SEP_CHAR)
                return 0;

        return 1;
}

int path_is_relative(const char *const str)
{
        if (*str == PATH_SEP_CHAR)
                return 0;

        return 1;
}

char *path_absolute(const char *const str)
{
        char *final, *current;

        if (path_is_absolute(str))
                return strdup(str);

        current = malloc(PATH_MAX);
        getcwd(current, PATH_MAX);

        final = path_join(current, str);
        free(current);

        return final;
}

char *path_absolute_with_free(char *const str)
{
        char *final;

        final = path_absolute(str);
        free(str);

        return final;
}

int path_parent_directory_is_exists(const char *const str)
{
        char *parent;
        int is_exists;

        parent = path_parent_directory(str);
        is_exists = path_is_exists(parent);
        free(parent);

        return is_exists;
}

char *path_parent_directory(const char *const str)
{
        char *absolute, *absolute_without_sep, *element, *final;
        size_t absolute_without_sep_size, element_size, final_size,
            final_last_ind;

        if (!strcmp(str, EMPTY_STR))
                return strdup(str);

        absolute = path_absolute(str);

        absolute_without_sep = remove_last_path_sep_if_needed(absolute);
        absolute_without_sep_size = strlen(absolute_without_sep);

        free(absolute);

        element = strrchr(absolute_without_sep, PATH_SEP_CHAR);
        element_size = strlen(element);

        final_size = absolute_without_sep_size - element_size;
        final_last_ind = final_size - 1;
        final = malloc(final_size + STR_NULL_CHAR_SIZE);

        strncpy(final, absolute_without_sep, final_size);
        *(final + final_last_ind + STR_NULL_CHAR_SIZE) = STR_NULL_CHAR;

        free(absolute_without_sep);
        return final;
}

char *path_parent_directory_with_free(char *const str)
{
        char *final;

        final = path_parent_directory(str);
        free(str);

        return final;
}
