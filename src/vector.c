#include <stdlib.h>
#include <string.h>

#include <CSVL/vector.h>

struct vector {
  void *restrict data;
  size_t item_size;
  size_t capacity;
  size_t length;
};

struct vector *vector_new(size_t item_size, size_t capacity) {
  void *data;
  if (!(data = malloc(capacity * item_size))) {
    return NULL;
  }

  struct vector *vect;
  if (!(vect = malloc(sizeof(struct vector)))) {
    return NULL;
  }

  vect->data = data;
  vect->item_size = item_size;
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
  return (char *)vect->data + vect->item_size * position;
}

static inline int expand(struct vector *vect) {
  void *data = realloc(vect->data, (2 * vect->capacity + 1) * vect->item_size);
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
  memcpy((char *)vect->data + vect->item_size * vect->length++, value,
         vect->item_size);
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
  memmove((char *)vect->data + (position + 1) * vect->item_size,
          (char *)vect->data + position * vect->item_size,
          (vect->length++ - position) * vect->item_size);
  memcpy((char *)vect->data + vect->item_size * position, value,
         vect->item_size);
  return 1;
}

void contract(struct vector *vect) {
  void *data = realloc(vect->data, (vect->capacity / 2) * vect->item_size);
  if (!data) {
    return;
  }
  vect->capacity /= 2;
  vect->data = data;
}

int vector_remove(struct vector *vect, ptrdiff_t position,
                  void *restrict output) {
  if (!vect) {
    return 0;
  }
  position += (position < 0) ? vect->length : 0;
  if (position < 0 || position >= (ptrdiff_t)vect->length) {
    return 0;
  }
  if (output) {
    memcpy(output, (char *)vect->data + vect->item_size * position,
           vect->item_size);
  }
  memmove((char *)vect->data + position * vect->item_size,
          (char *)vect->data + (position + 1) * vect->item_size,
          (--vect->length - position) * vect->item_size);
  if (vect->length <= vect->capacity / 4) {

    contract(vect);
  }
  return 1;
}

size_t vector_find(const struct vector *vect, const void *value) {
  if (!vect) {
    return 0;
  }
  if (!value) {
    return vect->length;
  }
  size_t position;
  for (position = 0; memcmp((char *)vect->data + position * vect->item_size,
                            value, vect->item_size) &&
                     position < vect->length;
       position++)
    ;
  return position;
}
