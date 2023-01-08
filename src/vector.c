#include <stdlib.h>
#include <string.h>

#include <CSVL/vector.h>

struct vector {
  void *data;
  size_t data_size;
  size_t capacity;
  size_t count;
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
  vect->count = 0;

  return vect;
}

void vector_delete(vector_t *vect) {
  free(vect->data);
  free(vect);
}

size_t vector_capacity(const vector_t *vect) { return vect->capacity; }
size_t vector_count(const vector_t *vect) { return vect->count; }
bool vector_empty(const vector_t *vect) { return !vect->count; }

void *vector_data(const struct vector *vect) { return vect->data; }

bool vector_add(vector_t *vect, const void *value) {
  if (vect->count == vect->capacity) {
    void *data =
        realloc(vect->data, (2 * vect->capacity + 1) * vect->data_size);
    if (!data) {
      return false;
    }
    vect->capacity *= 2;
    vect->capacity += 1;
    vect->data = data;
  }
  memcpy((char *)vect->data + vect->data_size * vect->count++, value,
         vect->data_size);
  return true;
}
