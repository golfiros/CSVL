#ifndef __CSVL_VECTOR_H__
#define __CSVL_VECTOR_H__

#include <stddef.h>

typedef struct vector vector_t;

vector_t *vector_new(size_t item_size, size_t capacity);
void vector_delete(vector_t *vect);

size_t vector_length(const vector_t *vect);
size_t vector_capacity(const vector_t *vect);

void *vector_get(const vector_t *vect, ptrdiff_t position);
int vector_append(vector_t *vect, const void *restrict value);
int vector_insert(vector_t *vect, ptrdiff_t position,
                  const void *restrict value);
void vector_remove(vector_t *vect, ptrdiff_t position, void *restrict output);

size_t vector_find(const vector_t *vect, const void *value);

void vector_sort(vector_t *vect, int (*comp)(const void *, const void *));

#include <CSVL/iterator.h>

iterator_t *vector_iterator_val(vector_t *vect, int reverse);
iterator_t *vector_iterator_ref(vector_t *vect, int reverse);

#endif
