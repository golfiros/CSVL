#ifndef __CSVL_VECTOR_H__
#define __CSVL_VECTOR_H__

#include <stddef.h>

typedef struct vector vector_t;

vector_t *vector_new(size_t data_size, size_t capacity);
void vector_delete(vector_t *vect);

size_t vector_length(const vector_t *vect);
size_t vector_capacity(const vector_t *vect);

void *vector_data(const vector_t *vect);

void *vector_get(const vector_t *vect, ptrdiff_t position);
int vector_add(vector_t *vect, const void *value);
int vector_insert(vector_t *vect, ptrdiff_t position, const void *value);
int vector_remove(vector_t *vect, ptrdiff_t position, void *output);

ptrdiff_t vector_find(const vector_t *vect, const void *value);

void vector_sort(vector_t *vect, int (*comp)(const void *, const void *));

#endif
