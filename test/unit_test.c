#include <criterion/criterion.h>

#include <CSVL/vector.h>

Test(sanity_check, trivial) { cr_assert(0 == 0); }

Test(vector, allocate) {
  size_t capacity = 10;
  vector_t *vect = vector_new(capacity, sizeof(int));
  cr_assert(vect, "allocated vector should not be null");
  vector_delete(vect);
}

Test(vector, empty_size) {
  size_t capacity = 10;
  vector_t *vect = vector_new(capacity, sizeof(int));
  cr_assert(vector_capacity(vect) == capacity, "vector capacity should be %zu",
            capacity);
  cr_assert(vector_count(vect) == 0, "vector count should be 0");
  cr_assert(vector_empty(vect), "vector should be empty");
  vector_delete(vect);
}

Test(vector, add) {
  size_t capacity = 10;
  vector_t *vect = vector_new(capacity, sizeof(int));
  for (int i = 0; i < (int)capacity; i++) {
    cr_assert(vector_add(vect, &i), "adding %d to vector should succeed", i);
  }
  cr_assert(vector_count(vect) == capacity, "vector count should be %zu",
            capacity);
  vector_delete(vect);
}

Test(vector, add_beyond) {
  size_t capacity = 10;
  vector_t *vect = vector_new(capacity, sizeof(int));
  for (int i = 0; i < (int)capacity; i++) {
    vector_add(vect, &i);
  }
  for (int i = 0; i < 2 * (int)capacity; i++) {
    cr_assert(vector_add(vect, &i), "adding %d to vector should suceed", i);
  }
  cr_assert(vector_capacity(vect) > capacity, "vector should have expanded");
  cr_assert(vector_count(vect) == 3 * capacity, "vector count should be %zu",
            3 * capacity);
  vector_delete(vect);
}
