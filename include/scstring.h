#ifndef SCS_H
#define SCS_H 

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define SCS_HANDLE_MALLOC_ERR(Name)                                            \
        do {                                                                   \
                if (Name == NULL) {                                            \
                        fprintf(stderr, "MALLOC ERROR!\n");                    \
                        exit(EXIT_FAILURE);                                    \
                }                                                              \
        } while (0)


typedef struct {
        size_t cap;
        size_t len;
        char *data;
} Scstring;

void Scstring_grow_cap(Scstring *s);
void Scstring_reserve(Scstring *s, size_t new_cap);
void Scstring_set_cap(Scstring *s, size_t new_cap);
void Scstring_free(Scstring *s);
void Scstring_add_null(Scstring *s);
void Scstring_raw_push_char(Scstring *s, char c);
void Scstring_push_char(Scstring *s, char c);
void Scstring_concat(Scstring *s1, Scstring *s2);
void Scstring_concat_with_cstr(Scstring *s, const char *cstr);
void Scstring_insert_char(Scstring *s, size_t idx, const char c);
void Scstring_clear(Scstring *s);

Scstring *Scstring_new(void);
Scstring *Scstring_from(const char *cstr);
Scstring *Scstring_clone(Scstring *s);



#endif
