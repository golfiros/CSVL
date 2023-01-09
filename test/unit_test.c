#include <criterion/criterion.h>

#include <CSVL/vector.h>

Test(vector, allocate) {
  vector_t *vect = vector_new(0, 0);
  cr_assert(vect, "allocated vector should not be null");
  vector_delete(vect);

  size_t capacity = 100;
  vect = vector_new(sizeof(int), capacity);

  cr_assert(vect, "allocated vector should not be null");
  cr_assert(vector_capacity(vect) == capacity, "vector capacity should be %zu",
            capacity);

  cr_assert(vector_length(vect) == 0, "vector length should be 0");
  vector_delete(vect);
}

Test(vector, add) {
  size_t capacity = 100;
  vector_t *vect = vector_new(sizeof(int), capacity);

  cr_assert(!vector_add(vect, NULL), "should not be able to add NULL");

  for (int i = 0; i < (int)capacity; i++) {
    cr_assert(vector_add(vect, &i), "adding %d to vector should succeed", i);
  }

  cr_assert(vector_length(vect) == capacity, "vector length should be %zu",
            capacity);

  for (int i = 0; i < 2 * (int)capacity; i++) {
    int j = i + capacity;
    cr_assert(vector_add(vect, &j), "adding %d to vector should suceed", i);
  }

  cr_assert(vector_capacity(vect) >= 3 * capacity,
            "vector should have expanded");
  cr_assert(vector_length(vect) == 3 * capacity, "vector count should be %zu",
            3 * capacity);

  vector_delete(vect);
}

Test(vector, get) {
  vector_t *vect = vector_new(sizeof(int), 0);

  int entries = 100;
  for (int i = 0; i < entries; i++) {
    vector_add(vect, &i);
  }

  for (int i = 0; i < entries; i++) {
    cr_assert(*(int *)vector_get(vect, i) == i,
              "vector element %d should be %d", *(int *)vector_get(vect, i), i);
  }

  for (int i = -1; i >= -entries; i--) {
    cr_assert(*(int *)vector_get(vect, i) == entries + i,
              "vector element %d should be %d", *(int *)vector_get(vect, i),
              entries - i);
  }

  cr_assert(!vector_get(vect, entries), "vector element %d should be NULL",
            entries);
  for (int i = entries + 1; i < 2 * entries; i++) {
    cr_assert(!vector_get(vect, i), "vector element %d should be null", i);
    cr_assert(!vector_get(vect, -i), "vector element %d should be null", -i);
  }

  vector_delete(vect);
}

Test(vector, insert) {
  vector_t *vect = vector_new(sizeof(int), 0);

  int entries = 100;
  for (int i = 0; i < entries; i++) {
    vector_add(vect, &i);
  }

  int val = 200;
  cr_assert(!vector_insert(vect, 0, NULL), "should not be able to add null");
  cr_assert(!vector_insert(vect, 2 * entries, &val),
            "should not be able to insert out of bounds");
  cr_assert(!vector_insert(vect, -2 * entries, &val),
            "should not be able to insert out of bounds");

  cr_assert(vector_insert(vect, entries / 2, &val),
            "should be able to insert at position %d", entries / 2);
  cr_assert(*(int *)vector_get(vect, entries / 2) == val,
            "entry %d should be %d", entries / 2, val);
  val += 1;
  cr_assert(vector_insert(vect, -entries / 2, &val),
            "should be able to insert at position %d", -entries / 2);
  cr_assert(*(int *)vector_get(vect, -(entries / 2 + 1)) == val,
            "entry %d should be %d", -(entries / 2 + 1), val);

  cr_assert(vector_length(vect) == (size_t)entries + 2,
            "vector length should be %d", entries + 2);

  vector_delete(vect);
}
