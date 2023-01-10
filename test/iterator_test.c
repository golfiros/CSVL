#include <criterion/criterion.h>

const int entries = 100;

int intcmp(const void *p1, const void *p2) { return *(int *)p1 - *(int *)p2; }

#include <CSVL/iterator.h>

int add_one(void *data, void *output) {
  if (*(int *)data >= entries) {
    return 0;
  }
  *(int *)output = (*(int *)data)++;
  return 1;
}

Test(iterator, iterate) {
  int i = 0;
  iterator_t *iter = iterator_new(sizeof(int), &i, add_one);
  cr_assert(iter, "allocated iterator should not be null");
  int x;
  while (iterator_next(iter, &x)) {
    cr_assert(x == i, "expected %d, got %d", i, x);
    i++;
  }
  cr_assert(i == entries, "should have iterated %d, only did %d", entries, i);
  iterator_delete(iter);
}

Test(iterator, foreach) {
  int i = 0;
  for_each(int, x, iterator_new(sizeof(int), &i, add_one), {
    cr_assert(x == i, "expected %d, got %d", i, x);
    i++;
  });
}
