#ifndef __STRUCT_ITERATOR_H__
#define __STRUCT_ITERATOR_H__

#include <stddef.h>

struct iterator {
  size_t data_size;
  void *restrict data;
  int (*next)(void *, void *);
};

#endif
