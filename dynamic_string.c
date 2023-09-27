// created by Ludwig Bogsveen

#include "dynamic_string.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STRING_MAX(x, y) ((x) > (y) ? (x) : (y))

String new_string()
{
    String str = string_with_capacity(8);
    return str;
}

void delete_string(String *str)
{
    free(str->ptr);
    str->ptr = NULL;
    str->length = 0;
    str->capacity = 0;
}

String string_copy(const String str)
{
    String copy = string_with_capacity(str.length);
    copy.length = str.length;
    memcpy(copy.ptr, str.ptr, (str.length + 1) * sizeof(char));
    return copy;
}

void string_clear(String *str)
{
    memset(str->ptr, 0, str->length * sizeof(char));
    str->length = 0;
}

String string_with_capacity(size_t capacity)
{
    String str = {0};
    str.ptr = malloc((capacity + 1) * sizeof(char)); // the plus 1 is for the null termination
    str.capacity = capacity;
    *(str.ptr) = '\0';
    return str;
}

void string_push_char(String *str, char ch)
{
    if (str->length == str->capacity)
    {
        string_reserve(str, 1);
    }
    str->ptr[str->length] = ch;
    str->ptr[++str->length] = '\0';
}

void string_append(String *str, const char *other)
{
    size_t remaining_capacity = str->capacity - str->length;
    size_t other_length = strlen(other);
    if (remaining_capacity < other_length)
    { // expands the string when it has reached it's maximum capacity
        string_reserve(str, other_length);
    }
    memcpy(str->ptr + str->length, other, (other_length + 1) * sizeof(char)); // Plus 1 is for the null terminator
    str->length += other_length;
}

void string_reserve_exact(String *str, size_t additional)
{
    size_t remaining_capacity = str->capacity - str->length;
    // Early returns when the string capacity is already big enough
    if (remaining_capacity >= additional)
    {
        return;
    }

    str->capacity += additional - remaining_capacity;
    str->ptr = realloc(str->ptr, (str->capacity + 1) * sizeof(char)); // the plus 1 is for the null termination
}

void string_reserve(String *str, size_t additional)
{
    size_t remaining_capacity = str->capacity - str->length;
    // Early returns when the string capacity is already big enough
    if (remaining_capacity >= additional)
    {
        return;
    }

    size_t new_capacity = STRING_MAX(str->capacity / 2 + 8, additional);
    string_reserve_exact(str, new_capacity);
}

int string_printf(String *str, char const *const _Format, ...)
{
    va_list _ArgList;
    va_start(_ArgList, _Format);
    int length = vsnprintf(NULL, 0, _Format, _ArgList);
    string_reserve(str, length);
    va_end(_ArgList);

    va_start(_ArgList, _Format);
    int _Result;
    _Result = vsnprintf(str->ptr + str->length, str->capacity + 1 - str->length, _Format, _ArgList);
    if (_Result > 0)
    {
        str->length += _Result;
    }
    va_end(_ArgList);

    return _Result;
}
