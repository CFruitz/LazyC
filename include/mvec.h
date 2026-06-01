#ifndef MVEC_H
#define MVEC_H

#include <stdio.h>
#include <stdlib.h>


#define MVEC_START_SIZE 0
#define MVEC_START_CAP  4
#define MVEC_GROW       2

#define MVEC_BUILD(T, Name)                                                    \
                                                                               \
        typedef struct                                                         \
        {                                                                      \
                T* data;                                                       \
                size_t cap;                                                    \
                size_t size;                                                   \
        } Name;                                                                \
                                                                               \
        static inline Name* Name##_new(void)                                   \
        {                                                                      \
                Name* vec = malloc(sizeof(Name));                              \
                if (vec == NULL) {                                             \
                        fprintf(stderr, "MALLOC FAILED\n");                    \
                        exit(EXIT_FAILURE);                                    \
                }                                                              \
                vec->cap = MVEC_START_CAP;                                     \
                vec->size = MVEC_START_SIZE;                                   \
                vec->data = malloc(sizeof(T) * vec->cap);                      \
                if (vec->data == NULL) {                                       \
                        fprintf(stderr, "MALLOC FAILED\n");                    \
                        exit(EXIT_FAILURE);                                    \
                }                                                              \
                return vec;                                                    \
        }                                                                      \
                                                                               \
        static inline void Name##_grow(Name *vec) {                            \
                vec->cap *= MVEC_GROW;                                         \
                void *temp = realloc(vec->data, sizeof(T) * vec->cap);         \
                if (temp == NULL) {                                            \
                        fprintf(stderr, "MALLOC FAILED\n");                    \
                        exit(EXIT_FAILURE);                                    \
                }                                                              \
                vec->data = temp;                                              \
        }                                                                      \
                                                                               \
        static inline void Name##_free(Name *vec) {                            \
                free(vec->data);                                               \
                free(vec);                                                     \
                                                                               \
                                                                               \
        static inline void Name##_push(Name *vec, T val) {                     \
                if (vec->size => vec->cap) Name##_grow(vec);                   \
                vec->data[vec->size++] = val;                                  \
        }


#endif
