#include <criterion/criterion.h>

#include <CSVL/vector.h>

Test(sanity_check, trivial) { cr_assert(0 == 0); }

Test(vector, allocate) {
  size_t capacity = 10;
  vector_t *vect = vector_new(sizeof(int), capacity);
  cr_assert(vect, "allocated vector should not be null");
  vector_delete(vect);
}

Test(vector, empty_size) {
  size_t capacity = 10;
  vector_t *vect = vector_new(sizeof(int), capacity);
  cr_assert(vector_capacity(vect) == capacity, "vector capacity should be %zu",
            capacity);
  cr_assert(vector_count(vect) == 0, "vector count should be 0");
  cr_assert(vector_empty(vect), "vector should be empty");
  vector_delete(vect);
}

Test(vector, add) {
  size_t capacity = 10;
  vector_t *vect = vector_new(sizeof(int), capacity);
  for (int i = 0; i < (int)capacity; i++) {
    cr_assert(vector_add(vect, &i), "adding %d to vector should succeed", i);
  }
  cr_assert(vector_count(vect) == capacity, "vector count should be %zu",
            capacity);
  int *data = vector_data(vect);
  for (int i = 0; i < (int)capacity; i++) {
    cr_assert(data[i] == i, "%d should equal %d", data[i], i);
  }
  vector_delete(vect);
}

Test(vector, add_beyond) {
  size_t capacity = 10;
  vector_t *vect = vector_new(sizeof(int), capacity);
  for (int i = 0; i < (int)capacity; i++) {
    vector_add(vect, &i);
  }
  for (int i = 0; i < 2 * (int)capacity; i++) {
    int j = i + capacity;
    cr_assert(vector_add(vect, &j), "adding %d to vector should suceed", i);
  }
  cr_assert(vector_capacity(vect) > 2 * capacity,
            "vector should have expanded");
  cr_assert(vector_count(vect) == 3 * capacity, "vector count should be %zu",
            3 * capacity);
  int *data = vector_data(vect);
  for (int i = 0; i < 3 * (int)capacity; i++) {
    cr_assert(data[i] == i, "%d should equal %d", data[i], i);
  }
  vector_delete(vect);
}
