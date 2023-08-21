/**
 * @file
 */

#ifndef VECTOR
#define VECTOR

#include <stdlib.h>

#define VECTOR_MAX(x, y) ((x) > (y) ? (x) : (y))

#define CREATE_VECTOR_TYPE(name, type) \
    DECLARE_VECTOR_TYPE(name, type) \
    DEFINE_VECTOR_TYPE(name, type)

#define DECLARE_VECTOR_TYPE(name, type) \
    typedef struct type##Vec { \
        type *ptr; \
        size_t length; \
        size_t capacity; \
    } type##Vec; \
    \
    type##Vec new_##name##vec(); \
    void delete_##name##vec(type##Vec *vec); \
    type##Vec vec##name##_copy(type##Vec vec); \
    type##Vec vec##name##_with_capacity(size_t capacity); \
    void vec##name##_push(type##Vec *vec, type item); \
    void vec##name##_append(type##Vec *vec, type *arr, size_t arr_len); \
    void vec##name##_reserve(type##Vec *vec, size_t additional); \
    void vec##name##_reserve_exact(type##Vec *vec, size_t additional); \

#define DEFINE_VECTOR_TYPE(name, type) \
    type##Vec new_##name##vec() { \
        type##Vec vec = vec##name##_with_capacity(8); \
        return vec; \
    } \
    \
    void delete_##name##vec(type##Vec *vec) { \
        free(vec->ptr); \
        vec->ptr = NULL; \
        vec->length = 0; \
        vec->capacity = 0; \
    } \
    \
    type##Vec vec##name##_copy(type##Vec vec) { \
        type##Vec copy = vec##name##_with_capacity(vec.length); \
        copy.length = vec.length; \
        memcpy(copy.ptr, vec.ptr, vec.length * sizeof(type)); \
        return copy; \
    } \
    \
    type##Vec vec##name##_with_capacity(size_t capacity) { \
        type##Vec vec = {0}; \
        vec.ptr = malloc(capacity * sizeof(type)); \
        vec.capacity = capacity; \
        return vec; \
    } \
    \
    void vec##name##_push(type##Vec *vec, type item) { \
        if (vec->length == vec->capacity) { \
            vec##name##_reserve(vec, 1); \
        } \
        vec->ptr[vec->length++] = item; \
    } \
    \
    void vec##name##_append(type##Vec *vec, type *other, size_t other_len) { \
        size_t remaining_capacity = vec->capacity - vec->length; \
        if (remaining_capacity < other_len) { /*expands the vec when it has reached it's maximum capacity*/ \
            vec##name##_reserve(vec, other_len); \
        } \
        \
        memcpy(vec->ptr + vec->length, other, (vec->capacity - vec->length) * sizeof(type)); \
        vec->length += other_len; \
    } \
    \
    void vec##name##_reserve(type##Vec *vec, size_t additional) { \
        size_t new_capacity = VECTOR_MAX(vec->capacity / 2 + 8, additional); \
        vec##name##_reserve_exact(vec, new_capacity); \
    } \
    void vec##name##_reserve_exact(type##Vec *vec, size_t additional) { \
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