/**
 * @file
 */

#ifndef VECTOR
#define VECTOR

#include <stdlib.h>

#define VECTOR_MAX(x, y) ((x) > (y) ? (x) : (y))

#define CREATE_VECTOR_TYPE(name, prefix, type) \
    DECLARE_VECTOR_TYPE(name, prefix, type) \
    DEFINE_VECTOR_TYPE(name, prefix, type)

#define DECLARE_VECTOR_TYPE(name, prefix, type) \
    typedef struct name { \
        type *ptr; \
        size_t length; \
        size_t capacity; \
    } name; \
    \
    name prefix##_new(); \
    void prefix##_delete(name *vec); \
    name prefix##_copy(const name vec); \
    void prefix##_clear(name *vec); \
    name prefix##_with_capacity(size_t capacity); \
    void prefix##_push(name *vec, type item); \
    void prefix##_append(name *vec, type *arr, size_t arr_len); \
    void prefix##_reserve(name *vec, size_t additional); \
    void prefix##_reserve_exact(name *vec, size_t additional); \

#define DEFINE_VECTOR_TYPE(name, prefix, type) \
    name prefix##_new() { \
        name vec = prefix##_with_capacity(8); \
        return vec; \
    } \
    \
    void prefix##_delete(name *vec) { \
        free(vec->ptr); \
        vec->ptr = NULL; \
        vec->length = 0; \
        vec->capacity = 0; \
    } \
    \
    name prefix##_copy(const name vec) { \
        name copy = prefix##_with_capacity(vec.length); \
        copy.length = vec.length; \
        memcpy(copy.ptr, vec.ptr, vec.length * sizeof(type)); \
        return copy; \
    } \
    \
    void prefix##_clear(name *vec) { \
        memset(vec->ptr, 0, vec->length * sizeof(type)); \
        vec->length = 0; \
    } \
    name prefix##_with_capacity(size_t capacity) { \
        name vec = {0}; \
        vec.ptr = malloc(capacity * sizeof(type)); \
        vec.capacity = capacity; \
        return vec; \
    } \
    \
    void prefix##_push(name *vec, type item) { \
        if (vec->length == vec->capacity) { \
            prefix##_reserve(vec, 1); \
        } \
        vec->ptr[vec->length++] = item; \
    } \
    \
    void prefix##_append(name *vec, type *other, size_t other_len) { \
        size_t remaining_capacity = vec->capacity - vec->length; \
        if (remaining_capacity < other_len) { /*expands the vec when it has reached it's maximum capacity*/ \
            prefix##_reserve(vec, other_len); \
        } \
        \
        memcpy(vec->ptr + vec->length, other, other_len * sizeof(type)); \
        vec->length += other_len; \
    } \
    \
    void prefix##_reserve(name *vec, size_t additional) { \
        size_t new_capacity = VECTOR_MAX(vec->capacity / 2 + 8, additional); \
        prefix##_reserve_exact(vec, new_capacity); \
    } \
    void prefix##_reserve_exact(name *vec, size_t additional) { \
        size_t remaining_capacity = vec->capacity - vec->length;\
        /*Early returns when the vec capacity is already big enough*/ \
        if (remaining_capacity > additional) { \
            return; \
        } \
        \
        vec->capacity += additional - remaining_capacity; \
        vec->ptr = realloc(vec->ptr, vec->capacity * sizeof(type)); \
    } \
    \
    
#endif