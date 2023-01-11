#include <criterion/criterion.h>

const int entries = 100;

int intcmp(const void *p1, const void *p2) { return *(int *)p1 - *(int *)p2; }

#include <CSVL/vector.h>

Test(vector, allocate) {
  vector_t *vect = vector_new(0, 0);
  cr_assert(vect, "allocated vector should not be null");
  vector_delete(vect);

  size_t capacity = entries;
  vect = vector_new(sizeof(int), capacity);

  cr_assert(vect, "allocated vector should not be null");
  cr_assert(vector_capacity(vect) == capacity, "vector capacity should be %zu",
            capacity);

  cr_assert(vector_length(vect) == 0, "vector length should be 0");
  vector_delete(vect);
}

Test(vector, add) {
  size_t capacity = entries;
  vector_t *vect = vector_new(sizeof(int), capacity);

  for (int i = 0; i < (int)capacity; i++) {
    cr_assert(vector_append(vect, &i), "adding %d to vector should succeed", i);
  }

  cr_assert(vector_length(vect) == capacity, "vector length should be %zu",
            capacity);

  for (int i = 0; i < 2 * (int)capacity; i++) {
    int j = i + capacity;
    cr_assert(vector_append(vect, &j), "adding %d to vector should suceed", i);
  }

  cr_assert(vector_capacity(vect) >= 3 * capacity,
            "vector should have expanded");
  cr_assert(vector_length(vect) == 3 * capacity, "vector count should be %zu",
            3 * capacity);

  vector_delete(vect);
}

Test(vector, get) {
  vector_t *vect = vector_new(sizeof(int), 0);

  for (int i = 0; i < entries; i++) {
    vector_append(vect, &i);
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

  vector_delete(vect);
}

Test(vector, insert) {
  vector_t *vect = vector_new(sizeof(int), 0);

  for (int i = 0; i < entries; i++) {
    vector_append(vect, &i);
  }

  int val = 200;

  cr_assert(vector_insert(vect, entries / 2, &val),
            "should be able to insert at position %d", entries / 2);
  cr_assert(*(int *)vector_get(vect, entries / 2) == val,
            "entry %d should be %d, got %d", entries / 2, val,
            *(int *)vector_get(vect, entries / 2));

  for (int i = 0; i < entries / 2; i++) {
    cr_assert(*(int *)vector_get(vect, i) == i, "entry %d should be %d, got %d",
              i, i, *(int *)vector_get(vect, i));
  }
  for (int i = entries / 2 + 1; i < entries + 1; i++) {
    cr_assert(*(int *)vector_get(vect, i) == i - 1,
              "entry %d should be %d, got %d", i, i - 1,
              *(int *)vector_get(vect, i));
  }

  val += 1;
  cr_assert(vector_insert(vect, -entries / 2, &val),
            "should be able to insert at position %d", -entries / 2);
  cr_assert(*(int *)vector_get(vect, -(entries / 2 + 1)) == val,
            "entry %d should be %d, got %d", -(entries / 2 + 1), val,
            *(int *)vector_get(vect, -(entries / 2 + 1)));

  cr_assert(vector_length(vect) == (size_t)entries + 2,
            "vector length should be %d", entries + 2);

  vector_delete(vect);
}

Test(vector, remove) {
  vector_t *vect = vector_new(sizeof(int), 0);

  for (int i = 0; i < entries; i++) {
    vector_append(vect, &i);
  }

  vector_remove(vect, 0, NULL);
  cr_assert(vector_length(vect) == (size_t)entries - 1,
            "vector length should be %d", entries - 1);

  for (int i = 1; i < entries; i++) {
    cr_assert(*(int *)vector_get(vect, i - 1) == i,
              "entry %d should be %d, got %d", i - 1, i,
              *(int *)vector_get(vect, i - 1));
  }

  int val = 0;
  vector_insert(vect, 0, &val);

  vector_remove(vect, entries / 2, &val);
  cr_assert(val == entries / 2, "output should be %d, got %d", entries / 2,
            val);
  for (int i = 0; i < entries / 2; i++) {
    cr_assert(*(int *)vector_get(vect, i) == i, "entry %d should be %d, got %d",
              i, i, *(int *)vector_get(vect, i));
  }
  for (int i = entries / 2; i < entries - 1; i++) {
    cr_assert(*(int *)vector_get(vect, i) == i + 1,
              "entry %d should be %d, got %d", i, i + 1,
              *(int *)vector_get(vect, i));
  }

  vector_remove(vect, -entries / 2, &val);

  cr_assert(vector_length(vect) == (size_t)entries - 2,
            "vector length should be %d, got %zu", entries - 2,
            vector_length(vect));

  for (; vector_length(vect);) {
    vector_remove(vect, 0, NULL);
  }
  cr_expect(vector_capacity(vect) < (size_t)entries,
            "vector should have shrunk, got %zu", vector_capacity(vect));

  vector_delete(vect);
}

Test(vector, find) {
  int val = 0;
  vector_t *vect = vector_new(sizeof(int), 0);
  for (int i = 0; i < entries; i++) {
    vector_append(vect, &i);
  }

  cr_assert(vector_find(vect, &entries) == vector_length(vect),
            "should not be able to find non-existing element");

  val = entries / 2;
  cr_assert(vector_find(vect, &val) == (size_t)entries / 2,
            "should have found existing element %d", val);
  vector_delete(vect);
}

Test(vector, sort) {
  vector_t *vect = vector_new(sizeof(int), 0);
  for (int i = entries - 1; i >= 0; i--) {
    vector_append(vect, &i);
  }
  vector_sort(vect, intcmp);
  for (int i = 0; i < entries; i++) {
    cr_assert(*(int *)vector_get(vect, i) == i, "entry %d should be %d", i, i);
  }

  vector_delete(vect);
}

Test(vector, iterator) {
  vector_t *vect = vector_new(sizeof(int), 0);
  for (int i = 0; i < entries; i++) {
    vector_append(vect, &i);
  }
  int i = 0;
  for_each(int *, x, vector_iterator_ref(vect, 0), {
    cr_assert(*x == i, "expected %d got %d", i, *x);
    *x = ++i;
  });
  for_each(int, x, vector_iterator_val(vect, 1), {
    cr_assert(x == i, "expected %d got %d", i, x);
    i--;
  });
  vector_delete(vect);
}
