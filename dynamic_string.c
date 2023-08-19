// created by Ludwig Bogsveen

#include "dynamic_string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

String new_string() {
    String str = string_with_capacity(8);
    return str;
}

void delete_string(String *str) {
    free(str->ptr);
}

String string_copy(const String str) {
    String copy = string_with_capacity(str.length);
    copy.length = str.length;
    strcpy_s(copy.ptr, copy.capacity + 1, str.ptr);
    return copy;
}

String string_with_capacity(size_t capacity) {
    String str = {0};
    str.ptr = malloc((capacity + 1) * sizeof(char)); // the plus 1 is for the null termination
    str.capacity = capacity;
    *(str.ptr) = '\0';
    return str;
}

void string_push_char(String* str, char ch) {
    if (str->length == str->capacity) {
        string_expand(str, 0);
    }
    str->ptr[str->length] = ch;
    str->ptr[++str->length] = '\0';
}

void string_push_string(String *str, const char *other) {
    size_t remaining_capacity = str->capacity - str->length;
    size_t other_length = strlen(other);
    if (remaining_capacity < other_length) { //expands the string when it has reached it's maximum capacity
        string_expand(str, str->length + other_length);
    }
    
    strcpy_s(str->ptr + str->length, str->capacity + 1 - str->length, other); //Plus 1 is for the null terminator
    str->length += other_length;
}

void string_reserve(String *str, size_t capacity) {
    //Early returns when the string capacity is already big enough
    if (str->capacity > capacity) {
        return;
    }

    str->ptr = realloc(str->ptr, (capacity + 1) * sizeof(char)); // the plus 1 is for the null termination
    str->capacity = capacity;
}

void string_expand(String *str, size_t minimum_capacity) {
    size_t new_capacity = max(str->capacity + str->capacity / 2 + 8, minimum_capacity);
    string_reserve(str, new_capacity);
} 

int string_printf(String *str, char const* const _Format, ...) {
    int _Result;
    va_list _ArgList;
    __crt_va_start(_ArgList, _Format);
    int length = vsnprintf(NULL,  0, _Format, _ArgList);
    string_expand(str, str->length + length);
    _Result = vsnprintf(str->ptr + str->length,  str->capacity + 1 - str->length, _Format, _ArgList);
    __crt_va_end(_ArgList);
    return _Result;
}