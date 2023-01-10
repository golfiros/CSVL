#ifndef __CSVL_ITERATOR_H__
#define __CSVL_ITERATOR_H__

#include <stddef.h>

typedef struct iterator iterator_t;

iterator_t *iterator_new(size_t data_size, const void *initial_data,
                         int (*next)(void *data, void *output));

void iterator_delete(iterator_t *iter);

int iterator_next(iterator_t *iter, void *restrict output);

#define CONCAT_(pre, suf) pre##suf
#define CONCAT(pre, suf) CONCAT_(pre, suf)
#define UNIQUE(name) CONCAT(name##_, __LINE__)

#define for_each(type, name, iter, body)                                       \
  do {                                                                         \
    type(name);                                                                \
    iterator_t *UNIQUE(_local_iter_##name) = (iter);                           \
    if (!UNIQUE(_local_iter_##name))                                           \
      break;                                                                   \
    while (iterator_next(UNIQUE(_local_iter_##name), &(name))) {               \
      body                                                                     \
    }                                                                          \
    iterator_delete(UNIQUE(_local_iter_##name));                               \
  } while (0)

#endif
