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
} SCS;

void SCS_grow_cap(SCS *s);
void SCS_reserve(SCS *s, size_t new_cap);
void SCS_set_cap(SCS *s, size_t new_cap);
void SCS_free(SCS *s);
void SCS_add_null(SCS *s);
void SCS_raw_push_char(SCS *s, char c);
void SCS_push_char(SCS *s, char c);
void SCS_concat(SCS *s1, SCS *s2);
void SCS_concat_with_str(SCS *s, const char *cstr);
void SCS_insert_char(SCS *s, size_t idx, const char c);
void SCS_insert_str(SCS *s, size_t idx, const char *c);
void SCS_remove_char(SCS *s, size_t idx);
void SCS_clear(SCS *s);

int SCS_find(SCS *s, const char *target);
int SCS_replace(SCS *s, const char *target, const char *rep);
int SCS_replace_all(SCS *s, const char *target, const char *rep, size_t max);
int SCS_trim_prefix(SCS *s, const char target);
int SCS_trim_suffix(SCS *s, const char target);
int SCS_startswith(SCS *s, const char *target);
int SCS_endswith(SCS *s, const char *target);



SCS *SCS_new(void);
SCS *SCS_from(const char *cstr);
SCS *SCS_clone(SCS *s);



#endif
