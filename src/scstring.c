#include "scs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Simple C String

/* 
typedef struct {
        size_t cap;
        size_t len;
        char *data;
} Scstring;;
*/

//IMPORTANTT

void Scstring_grow_cap(Scstring *s) {
        s->cap *= 2;
        char *temp = realloc(s->data, s->cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
}

void Scstring_reserve(Scstring *s, size_t new_cap) {
        if (new_cap <= s->cap) return;
        char *temp = realloc(s->data, new_cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
        s->cap = new_cap;
}


void Scstring_set_cap(Scstring *s, size_t new_cap) {
        char *temp = realloc(s->data, new_cap);
        if (temp == NULL) {
                fprintf(stderr, "REALLOC ERROR!\n");
                exit(EXIT_FAILURE);
        }
        s->data = temp;
        s->cap  = new_cap;
}

void Scstring_free(Scstring *s) {
        free(s->data);
        free(s);
}

void Scstring_add_null(Scstring *s) {
        s->data[s->len] = '\0';
}

void Scstring_raw_push_char(Scstring *s, char c) {
        s->data[s->len] = c;
        s->len++;
}

void Scstring_push_char(Scstring *s, char c) {
        if (s->len + 1 >= s->cap) {
                Scstring_grow_cap(s);
        }
        s->data[s->len] = c;
        s->len++;
        Scstring_add_null(s);
}

void Scstring_concat(Scstring *s1, Scstring *s2) {
        Scstring_reserve(s1, s1->len + s2->len + 1);
        for (size_t i = 0; i < s2->len; i++) {
                Scstring_raw_push_char(s1, s2->data[i]);
        }
        Scstring_add_null(s1);
}

void Scstring_concat_with_cstr(Scstring *s, const char *cstr) {
        Scstring_reserve(s, s->len + strlen(cstr) + 1);
        size_t i = 0;
        while (*(cstr + i) != '\0') {
                Scstring_raw_push_char(s, *(cstr + i));
                i++;
        }
        Scstring_add_null(s);
}

void Scstring_insert_char(Scstring *s, size_t idx, const char c) {
        Scstring_reserve(s, s->len + 1);
        if (idx > s->len) idx = s->len;
        memmove(s->data + idx + 1, s->data + idx, s->len - idx + 1);
        s->data[idx] = c;
        s->len++;
        Scstring_add_null(s);
}

void Scstring_clear(Scstring *s) {
        s->len = 0;
        Scstring_add_null(s);
}

//User Basic
Scstring *Scstring_new(void) {
        Scstring *str = malloc(sizeof(Scstring));
        SCS_HANDLE_MALLOC_ERR(str);
        str->len = 0;
        str->cap = 4;
        str->data = malloc(sizeof(char) * str->cap);
        SCS_HANDLE_MALLOC_ERR(str->data);
        Scstring_add_null(str);
        return str;
}


Scstring *Scstring_from(const char *cstr) {
        Scstring *str = Scstring_new();
        Scstring_concat_with_cstr(str, cstr);
        return str;
}

Scstring *Scstring_clone(Scstring *s) {
        Scstring *str = Scstring_new();
        Scstring_concat(str, s);
        return str;
}

