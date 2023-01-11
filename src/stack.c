#include <stdlib.h>
#include <string.h>

#include <CSVL/stack.h>

struct stack {
  void *restrict data;
  size_t item_size;
  size_t capacity;
  size_t position;
};

struct stack *stack_new(size_t item_size, size_t capacity) {
  void *data = malloc(item_size * capacity);
  if (!data) {
    return NULL;
  }
  struct stack *stack = malloc(sizeof(struct stack));
  if (!stack) {
    return NULL;
  }
  stack->data = data;
  stack->item_size = item_size;
  stack->capacity = capacity;
  stack->position = 0;
  return stack;
}

void stack_delete(struct stack *stack) {
  free(stack->data);
  free(stack);
}

int stack_empty(stack_t *stack) { return !stack->position; }

static inline int expand(struct stack *stack) {
  void *data =
      realloc(stack->data, (2 * stack->capacity + 1) * stack->item_size);
  if (!data) {
    return 0;
  }
  stack->capacity *= 2;
  stack->capacity += 1;
  stack->data = data;
  return 1;
}

int stack_push(stack_t *stack, const void *restrict value) {
  if (stack->position == stack->capacity) {
    if (!expand(stack)) {
      return 0;
    }
  }
  memcpy((char *)stack->data + stack->item_size * stack->position++, value,
         stack->item_size);
  return 1;
}

static inline void contract(struct stack *stack) {
  void *data = realloc(stack->data, (stack->capacity / 2) * stack->item_size);
  if (!data) {
    return;
  }
  stack->capacity /= 2;
  stack->data = data;
}

int stack_pop(stack_t *stack, void *restrict output) {
  if (!stack->position) {
    return 0;
  }
  if (output) {
    memcpy(output, (char *)stack->data + stack->item_size * --stack->position,
           stack->item_size);
  }
  if (stack->position <= stack->capacity / 4) {
    contract(stack);
  }
  return 1;
}

void *stack_peek(stack_t *stack) {
  if (!stack->position) {
    return NULL;
  }
  return (char *)stack->data + stack->item_size * (stack->position - 1);
}

static int next(void *state, void *output) {
  struct stack *stack = *(struct stack **)state;
  if (!stack->position) {
    return 0;
  }
  memcpy(output, (char *)stack->data + stack->item_size * --stack->position,
         stack->item_size);
  return 1;
}

iterator_t *stack_iterator(struct stack *stack) {
  void *p = stack;
  return iterator_new(sizeof(struct stack *), &p, next);
}
