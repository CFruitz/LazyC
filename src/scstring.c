#include "scstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Simple C String

/* 
typedef struct {
        size_t cap;
        size_t len;
        char *data;
} SCS;
*/

//IMPORTANT

void SCS_grow_cap(SCS *s) {
        s->cap *= 2;
        char *temp = realloc(s->data, s->cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
}

void SCS_reserve(SCS *s, size_t new_cap) {
        if (new_cap <= s->cap) return;
        char *temp = realloc(s->data, new_cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
        s->cap = new_cap;
}


void SCS_set_cap(SCS *s, size_t new_cap) {
        char *temp = realloc(s->data, new_cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
        s->cap  = new_cap;
}

void SCS_free(SCS *s) {
        free(s->data);
        free(s);
}

void SCS_add_null(SCS *s) {
        s->data[s->len] = '\0';
}

void SCS_raw_push_char(SCS *s, char c) {
        s->data[s->len] = c;
        s->len++;
}

void SCS_push_char(SCS *s, char c) {
        if (s->len + 1 >= s->cap) {
                SCS_grow_cap(s);
        }
        s->data[s->len] = c;
        s->len++;
        SCS_add_null(s);
}

void SCS_concat(SCS *s1, SCS *s2) {
        SCS_reserve(s1, s1->len + s2->len + 1);
        for (size_t i = 0; i < s2->len; i++) {
                SCS_raw_push_char(s1, s2->data[i]);
        }
        SCS_add_null(s1);
}

void SCS_concat_with_str(SCS *s, const char *cstr) {
        SCS_reserve(s, s->len + strlen(cstr) + 1);
        size_t i = 0;
        while (*(cstr + i) != '\0') {
                SCS_raw_push_char(s, *(cstr + i));
                i++;
        }
        SCS_add_null(s);
}

void SCS_insert_char(SCS *s, size_t idx, const char c) {
        SCS_reserve(s, s->len + 1);
        if (idx > s->len) idx = s->len;
        memmove(s->data + idx + 1, s->data + idx, s->len - idx + 1);
        s->data[idx] = c;
        s->len++;
        SCS_add_null(s);
}

void SCS_insert_str(SCS *s, size_t idx, const char *src) {
    SCS_reserve(s, s->len + strlen(src));
    memmove(s->data + idx + strlen(src), s->data + idx, strlen(s->data + idx) + 1);
    memcpy(s->data + idx, src, strlen(src));
    s->len += strlen(src);
    SCS_add_null(s);
}

void SCS_remove_char(SCS *s, size_t idx) {
    if (idx > s->len) idx = s->len;
    memmove(s->data + idx,s->data + idx + 1, s->len - idx);
    s->len--;
    SCS_add_null(s);
}


void SCS_clear(SCS *s) {
        s->len = 0;
        SCS_add_null(s);
}

//Utils

int SCS_find(SCS *s, const char *target) {
    size_t target_len = strlen(target);
    if (target_len > s->len) return -1;
    for (size_t i = 0; i <= s->len - target_len; i++) {
        if (memcmp(s->data + i, target, target_len) == 0) return (int)i;
    }
    return -1;
}

int SCS_replace(SCS *s, const char *target, const char *rep) {
    int pos = SCS_find(s, target);
    if (pos != -1) {
        SCS_reserve(s, s->len + strlen(rep));
        
        memmove(s->data + pos + strlen(rep),
            s->data + pos + strlen(target),
            strlen(s->data + pos + strlen(target)) + 1
            );
            
        memmove(s->data + pos, rep, strlen(rep));
        s->len = s->len + strlen(rep) - strlen(target);
        return 0;
    }
    return -1;
}

int SCS_replace_all(SCS *s, const char *target, const char *rep, size_t max) {
    size_t i = 1;
    while (SCS_replace(s, target, rep) == 0 && i < max) {
        i++;
    }
    if (i > 1) {
        return 0;
    } else {
        return -1;
    }
}

int SCS_trim_prefix(SCS *s, const char target) {
    int count = 0;
    while (*(s->data + count) == target) count++;
    memmove(s->data, s->data + count, strlen(s->data + count) + 1);
    s->len -= count;
    return (count > 0) ? 0 : -1;
}

int SCS_trim_suffix(SCS *s, const char target) {
    if (s->len == 0) return -1;
    int count = s->len - 1;
    while (count >= 0 && *(s->data + count) == target) count--;
    int trimmed = s->len - count - 1;
    s->len -= trimmed;
    SCS_add_null(s);
    return (s->len - count > 0) ? 0 : -1;
}

int SCS_startswith(SCS *s, const char *target) {
    if (strlen(target) > s->len) return -1;
    return (memcmp(s->data, target, strlen(target)) == 0) ? 0 : -1;
}

int SCS_endswith(SCS *s, const char *target) {
    if (strlen(target) > s->len) return -1;
    return (memcmp(s->data + s->len - strlen(target), target, strlen(target)) == 0) ? 0 : -1 ;
}

//User Basic
SCS *SCS_new(void) {
        SCS *str = malloc(sizeof(SCS));
        SCS_HANDLE_MALLOC_ERR(str);
        str->len = 0;
        str->cap = 4;
        str->data = malloc(sizeof(char) * str->cap);
        SCS_HANDLE_MALLOC_ERR(str->data);
        SCS_add_null(str);
        return str;
}


SCS *SCS_from(const char *cstr) {
        SCS *str = SCS_new();
        SCS_concat_with_str(str, cstr);
        return str;
}

SCS *SCS_clone(SCS *s) {
        SCS *str = SCS_new();
        SCS_concat(str, s);
        return str;
}

