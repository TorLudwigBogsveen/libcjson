/**
 * @file
 */

#ifndef STRING
#define STRING

#include <stddef.h>

typedef struct String {
    char *ptr;
    size_t length;
    size_t capacity;
} String;

String new_string();

void delete_string(String *str);

String string_copy(String str);

String string_with_capacity(size_t capacity);

void string_push_char(String *str, char ch);

void string_append(String *str, const char *other);

void string_reserve(String *str, size_t additional);

void string_reserve_exact(String *str, size_t additional);

int string_printf(String *str, char const* const _Format, ...);

#endif