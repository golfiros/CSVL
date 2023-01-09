#include <stdlib.h>
#include <string.h>

#include <CSVL/vector.h>

struct vector {
  void *restrict data;
  size_t data_size;
  size_t capacity;
  size_t length;
};

struct vector *vector_new(size_t data_size, size_t capacity) {
  void *data;
  if (!(data = malloc(capacity * data_size))) {
    return NULL;
  }

  struct vector *vect;
  if (!(vect = malloc(sizeof(struct vector)))) {
    return NULL;
  }

  vect->data = data;
  vect->data_size = data_size;
  vect->capacity = capacity;
  vect->length = 0;

  return vect;
}

void vector_delete(struct vector *vect) {
  free(vect->data);
  free(vect);
}

size_t vector_capacity(const struct vector *vect) {
  return vect ? vect->capacity : 0;
}
size_t vector_length(const struct vector *vect) {
  return vect ? vect->length : 0;
}

void *vector_get(const struct vector *vect, ptrdiff_t position) {
  if (!vect) {
    return NULL;
  }
  position += (position < 0) ? vect->length : 0;
  if (position < 0 || position >= (ptrdiff_t)vect->length) {
    return NULL;
  }
  return (char *)vect->data + vect->data_size * position;
}

static inline int expand(struct vector *vect) {
  if (!vect) {
    return 0;
  }
  void *data = realloc(vect->data, (2 * vect->capacity + 1) * vect->data_size);
  if (!data) {
    return 0;
  }
  vect->capacity *= 2;
  vect->capacity += 1;
  vect->data = data;
  return 1;
}

int vector_add(struct vector *vect, const void *restrict value) {
  if (!vect || !value) {
    return 0;
  }
  if (vect->length == vect->capacity) {
    if (!expand(vect)) {
      return 0;
    }
  }
  memcpy((char *)vect->data + vect->data_size * vect->length++, value,
         vect->data_size);
  return 1;
}

int vector_insert(struct vector *vect, ptrdiff_t position,
                  const void *restrict value) {
  if (!vect || !value) {
    return 0;
  }
  position += (position < 0) ? vect->length : 0;
  if (position < 0 || position > (ptrdiff_t)vect->length) {
    return 0;
  }
  if (vect->length == vect->capacity) {
    if (!expand(vect)) {
      return 0;
    }
  }
  memmove((char *)vect->data + (position + 1) * vect->data_size,
          (char *)vect->data + position * vect->data_size,
          (vect->length++ - position) * vect->data_size);
  memcpy((char *)vect->data + vect->data_size * position, value,
         vect->data_size);
  return 1;
}
