#include <criterion/criterion.h>

#include <CSVL/stack.h>

const int entries = 100;

Test(stack, push_peek_pop) {
  stack_t *stack = stack_new(0, 0);
  cr_assert(stack, "allocated stack should not be null");
  stack_delete(stack);
  stack = stack_new(sizeof(int), 0);
  cr_assert(stack_empty(stack), "stack should start empty");
  for (int i = 0; i < entries; i++) {
    cr_assert(stack_push(stack, &i), "should be able to push %d", i);
  }
  for (int i = entries - 1; i >= 0; i--) {
    cr_assert(i == *(int *)stack_peek(stack),
              "top of stack should be %d, got %d", i,
              *(int *)stack_peek(stack));
    int x;
    cr_assert(stack_pop(stack, &x), "should be able to pop %d", i);
    cr_assert(x == i, "expected %d got %d", i, x);
  }
  cr_assert(!stack_pop(stack, NULL), "stack should be empty");
  cr_assert(!stack_peek(stack), "stack should be empty");
  cr_assert(stack_empty(stack), "stack should be empty");
}

Test(stack, iterator) {
  stack_t *stack = stack_new(sizeof(int), 0);
  cr_assert(stack_empty(stack), "stack should start empty");
  for (int i = 0; i < entries; i++) {
    stack_push(stack, &i);
  }
  int x = 99;
  for_each(int, i, stack_iterator(stack), cr_assert(x-- == i););
  cr_assert(stack_empty(stack), "stack should be empty");
  stack_delete(stack);
}
