#ifndef PSDCLI_PATHUT_H
#define PSDCLI_PATHUT_H

#include <psd_convert.h>

#define PATH_SEP_STR ("/")
#define PATH_SEP_CHAR ('/')

#define PATH_SEP_STR_SIZE strlen((char *)PATH_SEP_STR)
#define PATH_SEP_CHAR_SIZE sizeof((char)PATH_SEP_CHAR)
#define STR_NULL_STR "\0"
#define STR_NULL_CHAR '\0'

#define STR_NULL_STR_SIZE strlen((char *)STR_NULL_STR)
#define STR_NULL_CHAR_SIZE sizeof((char)STR_NULL_CHAR)

#define EXT_SEP_STR "."
#define EXT_SEP_CHAR '.'

#define EXT_SEP_STR_SIZE (strlen((char *)EXT_SEP_STR))
#define EXT_SEP_CHAR_SIZE (sizeof((char)EXT_SEP_CHAR))

#define EMPTY_STR ""

char *remove_last_path_sep_if_needed(const char *const string);

char *remove_last_ext_sep_if_needed(const char *const string);

char *path_join(const char *const string1, const char *const string2);

int path_is_exists(const char *const string);

int path_parent_directory_is_exists(const char *const string);

int path_is_absolute(const char *const string);

int path_is_file(const char *const STR);

int path_is_directory(const char *const STR);

char *path_extension(const char *const string);

char *path_remove_extension(const char *const stirng);

char *path_remove_extension_with_free(char *const string);

char *path_append_extension(const char *const string,
                            const char *const extension);

char *path_append_extension_with_free(char *const string,
                                      const char *const extension);

char *path_set_extension(const char *const STR, const char *const EXT);

char *path_set_extension_with_free(char *const str, const char *const ext);

char *path_absolute(const char *const string);

char *path_absolute_with_free(char *const string);

char *path_basename();

char *path_parent_directory(const char *const string);

char *path_parent_directory_with_free(char *const string);

#endif
