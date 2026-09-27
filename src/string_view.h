#ifndef __STRING_VIEW_H__

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define sv_fmt "%.*s"
#define sv_arg(sv) (sv).count, (sv).data

typedef struct{
    const char* data; 
    size_t count;
} string_view;

string_view sv_from_cstr(const char* string);
string_view sv_chop_by_delim(string_view* sv, char delim);
void sv_lchop(string_view* sv, size_t n);
void sv_rchop(string_view* sv, size_t n);
void sv_ltrim(string_view* sv);
void sv_rtrim(string_view* sv);
void sv_trim(string_view* sv);
void sv_cpy_to_cstr(char* dest, string_view* sv);

string_view sv_from_cstr(const char* string){
    return (string_view){
        .data = string,
        .count = strlen(string)
    };
}
void sv_lchop(string_view* sv, size_t n){
    if (n > sv->count) n = sv->count;
    sv->count -= n;
    sv->data += n;
}

void sv_rchop(string_view* sv, size_t n){
    sv->count -= n;
}

string_view sv_chop_by_delim(string_view* sv, char delim){
    size_t i = 0;

    while (i < sv->count && sv->data[i] != delim){
        i+=1;
    }
    
    if (i < sv->count){
        string_view nsv = {
            .data = sv->data,
            .count = i
        };
        sv_lchop(sv, i+1);
        return nsv;
    }

    string_view nsv = *sv;
    sv_lchop(sv, sv->count);
    return nsv;
    
}

void sv_ltrim(string_view* sv){
    while (sv->count > 0 && isspace(sv->data[0])) {
        sv_lchop(sv, 1);
    }
}

void sv_rtrim(string_view* sv){
    while (sv->count > 0 && isspace(sv->data[sv->count-1])) {
        sv_rchop(sv, 1);
    }
}

void sv_trim(string_view* sv){
    sv_rtrim(sv);
    sv_ltrim(sv);
}

void sv_cpy_to_cstr(char* dest, string_view* sv){
    strncpy(dest, sv->data, sv->count);
}

void sv_concat_cstr(string_view* sv1, char* str){
   int len = 0; 
}

#endif // !__STRING_VIEW_H__
