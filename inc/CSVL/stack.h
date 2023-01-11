#ifndef __CSVL_STACK_H__
#define __CSVL_STACK_H__

#include <stddef.h>

typedef struct stack stack_t;

stack_t *stack_new(size_t item_size, size_t capacity);
void stack_delete(stack_t *stack);

int stack_empty(stack_t *stack);

int stack_push(stack_t *stack, const void *restrict value);
int stack_pop(stack_t *stack, void *restrict output);

void *stack_peek(stack_t *stack);

#include <CSVL/iterator.h>

iterator_t *stack_iterator(stack_t *stack);

#endif
