#include <stdlib.h>
#include <stdio.h>

#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#define INIT_CAPACITY 8

typedef struct VecHeader{
    size_t size;
    size_t capacity;
} VecHeader;

# define vec(T) T*
# define vec_create(T) __vec_create(sizeof(T), INIT_CAPACITY)
# define vec_size(vec) ((VecHeader*)(vec) - 1)->size
# define vec_free(vec) free((VecHeader*)(vec)-1)

# define vec_append(vec, val)                          \
do{                                                    \
    (vec) = __vec_resize_up((vec), sizeof(vec[0]), 1); \
    VecHeader *__header = (VecHeader*)(vec) - 1;       \
    (vec)[__header->size++] = (val);                   \
} while(0)                                             \

# define vec_pop(vec)                                    \
do{                                                      \
    (vec) = __vec_resize_down((vec), sizeof(vec[0]), 1); \
    VecHeader *__header = (VecHeader*)(vec) - 1;         \
    __header->size--;                                    \
} while(0)                                               \

void* __vec_create(size_t t_size, size_t capacity);
void* __vec_resize_up(void* vec, size_t t_size, size_t n);
void* __vec_resize_down(void* vec, size_t t_size, size_t n);

// IMPLEMENTATION

void* __vec_create(size_t t_size, size_t capacity){
    VecHeader *header = (VecHeader*)malloc(t_size*capacity + sizeof(VecHeader));
    header->size = 0;
    header->capacity = capacity;
    return (void*) (header+1);
}

void* __vec_resize_up(void* vec, size_t t_size, size_t n){
    VecHeader *header = (VecHeader*)(vec) - 1;

    if (!vec) {
        return __vec_create(t_size, INIT_CAPACITY);
    }

    if (header->size + n < header->capacity) return vec;

    header->capacity *= 1.5; 
    header = (VecHeader*) realloc(header, t_size*header->capacity + sizeof(VecHeader));

    if (!header) return NULL;

    return (void*) (header+1);
}

void* __vec_resize_down(void* vec, size_t t_size, size_t n){
    VecHeader *header = (VecHeader*)(vec) - 1;

    if (!vec) {
        return NULL;
    }
    if (header->size - n > header->capacity / 1.5) return vec;

    header->capacity /= 1.5; 
    if (header->capacity < INIT_CAPACITY) header->capacity = INIT_CAPACITY;

    header = (VecHeader*) realloc(header, t_size*header->capacity + sizeof(VecHeader));
    if (!header) return NULL;

    return (void*) (header+1);
}

#endif
