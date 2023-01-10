#include <stdlib.h>
#include <string.h>

#include <CSVL/iterator.h>

#include <struct_iterator.h>

struct iterator *iterator_new(size_t data_size, const void *initial_data,
                              int (*next)(void *data, void *output)) {
  void *data = malloc(data_size);
  if (!data) {
    return NULL;
  }
  struct iterator *iter = malloc(sizeof(struct iterator));
  if (!iter) {
    return NULL;
  }
  memcpy(data, initial_data, data_size);

  iter->data_size = data_size;
  iter->data = data;
  iter->next = next;

  return iter;
}

void iterator_delete(struct iterator *iter) {
  free(iter->data);
  free(iter);
}

int iterator_next(struct iterator *iter, void *restrict output) {
  return iter->next(iter->data, output);
}
