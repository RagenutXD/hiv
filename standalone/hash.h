#ifndef __HASH_H__
#define __HASH_H__

#include <stdlib.h>
#include <string.h>

#define hash(val, hm_size) _Generic((val),                 \
        char*: __hashs,     int: __hashi,          \
        float: __hashf,                            \
      default: __hashs)(val, hm_size)


size_t __hashs(char* str, size_t hm_size);
size_t __hashi(int num, size_t hm_size);
size_t __hashf(float num, size_t hm_size);


size_t __hashs(char* str, size_t hm_size){
    size_t idx = 0;
    size_t length = strlen(str);
    for(size_t i = 0; i < length; i++){
        idx += (size_t)(str[i]);
    }
    idx = idx % hm_size;
    return idx;
}

size_t __hashi(int num, size_t hm_size){
    return 0;
}

size_t __hashf(float num, size_t hm_size){
    return 0;
}

#endif // !__HASH_H__
