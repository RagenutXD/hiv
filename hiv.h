#include <stdlib.h>
#include <stdio.h>




typedef struct HivVecHeader{
    size_t size;
    size_t capacity;
} HivVecHeader;

#define HIV_VEC_INIT_CAPACITY 8
#define hiv_vec(T) T*
#define hiv_vec_create(T) __hiv_vec_create(sizeof(T), HIV_VEC_INIT_CAPACITY)
#define hiv_vec_size(hiv_vec) ((HivVecHeader*)(hiv_vec) - 1)->size
#define hiv_vec_free(hiv_vec) free((HivVecHeader*)(hiv_vec)-1)

#define hiv_vec_append(hiv_vec, val)                          \
do{                                                    \
    (hiv_vec) = __hiv_vec_resize_up((hiv_vec), sizeof(hiv_vec[0]), 1); \
    HivVecHeader *__header = (HivVecHeader*)(hiv_vec) - 1;       \
    (hiv_vec)[__header->size++] = (val);                   \
} while(0)                                             \

#define hiv_vec_pop(hiv_vec)                                    \
do{                                                      \
    (hiv_vec) = __hiv_vec_resize_down((hiv_vec), sizeof(hiv_vec[0]), 1); \
    HivVecHeader *__header = (HivVecHeader*)(hiv_vec) - 1;         \
    __header->size--;                                    \
} while(0)                                               \


// TODO: change the everything to hiv

void* __hiv_vec_create(size_t t_size, size_t capacity);
void* __hiv_vec_resize_up(void* vec, size_t t_size, size_t n);
void* __hiv_vec_resize_down(void* vec, size_t t_size, size_t n);

// IMPLEMENTATION

void* __hiv_vec_create(size_t t_size, size_t capacity){
    HivVecHeader *header = (HivVecHeader*)malloc(t_size*capacity + sizeof(HivVecHeader));
    header->size = 0;
    header->capacity = capacity;
    return (void*) (header+1);
}

void* __hiv_vec_resize_up(void* vec, size_t t_size, size_t n){
    HivVecHeader *header = (HivVecHeader*)(vec) - 1;

    if (!vec) {
        return __hiv_vec_create(t_size, HIV_VEC_INIT_CAPACITY);
    }

    if (header->size + n < header->capacity) return vec;

    header->capacity *= 1.5; 
    header = (HivVecHeader*) realloc(header, t_size*header->capacity + sizeof(HivVecHeader));

    if (!header) return NULL;

    return (void*) (header+1);
}

void* __hiv_vec_resize_down(void* vec, size_t t_size, size_t n){
    HivVecHeader *header = (HivVecHeader*)(vec) - 1;

    if (!vec) {
        return NULL;
    }
    if (header->size - n > header->capacity / 1.5) return vec;

    header->capacity /= 1.5; 
    if (header->capacity < HIV_VEC_INIT_CAPACITY) header->capacity = HIV_VEC_INIT_CAPACITY;

    header = (HivVecHeader*) realloc(header, t_size*header->capacity + sizeof(HivVecHeader));
    if (!header) return NULL;

    return (void*) (header+1);
}


#ifdef HIV_STRIP_PREFIX

#define VecHeader HivVecHeader
#define VEC_INIT_CAPCITY HIV_VEC_INIT_CAPACITY 
# define vec        hiv_vec
# define vec_append hiv_vec_append
# define vec_pop    hiv_vec_pop
# define vec_create hiv_vec_create
# define vec_size   hiv_vec_size
# define vec_free   hiv_vec_free

#endif
