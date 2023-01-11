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

size_t vector_capacity(const struct vector *vect) { return vect->capacity; }
size_t vector_length(const struct vector *vect) { return vect->length; }

void *vector_get(const struct vector *vect, ptrdiff_t position) {
  position += (position < 0) ? vect->length : 0;
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

int vector_append(struct vector *vect, const void *restrict value) {
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
  position += (position < 0) ? vect->length : 0;
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

static inline void contract(struct vector *vect) {
  void *data = realloc(vect->data, (vect->capacity / 2) * vect->item_size);
  if (!data) {
    return;
  }
  vect->capacity /= 2;
  vect->data = data;
}

void vector_remove(struct vector *vect, ptrdiff_t position,
                   void *restrict output) {
  position += (position < 0) ? vect->length : 0;
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
}

size_t vector_find(const struct vector *vect, const void *value) {
  size_t position;
  for (position = 0; memcmp((char *)vect->data + position * vect->item_size,
                            value, vect->item_size) &&
                     position < vect->length;
       position++)
    ;
  return position;
}

void vector_sort(vector_t *vect, int (*comp)(const void *, const void *)) {
  qsort(vect->data, vect->length, vect->item_size, comp);
}

struct vector_state {
  size_t position;
  struct vector vect;
};

static int next_val(void *state, void *output) {
  struct vector_state *p = state;
  if (p->position == p->vect.length) {
    return 0;
  }
  memcpy(output, (char *)p->vect.data + p->vect.item_size * p->position++,
         p->vect.item_size);
  return 1;
}
static int prev_val(void *state, void *output) {
  struct vector_state *p = state;
  if (p->position == 0) {
    return 0;
  }
  memcpy(output, (char *)p->vect.data + p->vect.item_size * --p->position,
         p->vect.item_size);
  return 1;
}
static int next_ref(void *state, void *output) {
  struct vector_state *p = state;
  if (p->position == p->vect.length) {
    return 0;
  }
  void *q = (char *)p->vect.data + p->vect.item_size * p->position++;
  memcpy(output, &q, sizeof(void *));
  return 1;
}
static int prev_ref(void *state, void *output) {
  struct vector_state *p = state;
  if (p->position == 0) {
    return 0;
  }
  void *q = (char *)p->vect.data + p->vect.item_size * --p->position;
  memcpy(output, &q, sizeof(void *));
  return 1;
}

struct iterator *vector_iterator_val(vector_t *vect, int reverse) {
  struct vector_state state;
  state.position = reverse ? vect->length : 0;
  state.vect = *vect;
  return reverse ? iterator_new(sizeof(struct vector_state), &state, prev_val)
                 : iterator_new(sizeof(struct vector_state), &state, next_val);
}

struct iterator *vector_iterator_ref(vector_t *vect, int reverse) {
  struct vector_state state;
  state.position = reverse ? vect->length : 0;
  state.vect = *vect;
  return reverse ? iterator_new(sizeof(struct vector_state), &state, prev_ref)
                 : iterator_new(sizeof(struct vector_state), &state, next_ref);
}
