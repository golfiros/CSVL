#ifndef __CSVL_VECTOR_H__
#define __CSVL_VECTOR_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct vector vector_t;

vector_t *vector_new(size_t capacity, size_t data_size);
void vector_delete(vector_t *vector);

size_t vector_count(const vector_t *vector);
size_t vector_capacity(const vector_t *vector);
bool vector_empty(const vector_t *vector);

void *vector_data(const vector_t *vector);

void *vector_get(const vector_t *vector, ptrdiff_t position);
bool vector_add(vector_t *vector, const void *value);
bool vector_insert(vector_t *vector, ptrdiff_t position, const void *value);
bool vector_remove(vector_t *vector, ptrdiff_t position, void *output);

ptrdiff_t vector_find(const vector_t *vector, const void *value);

void vector_sort(vector_t *vector, int (*comp)(const void *, const void *));

#endif
