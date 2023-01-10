#include <stdio.h>
#include <stdlib.h>

#include <CSVL/iterator.h>

int fibonacci_next(void *data, void *out) {
  unsigned int *p = data;
  *(unsigned int *)out = p[0] + p[1];
  p[0] = p[1];
  p[1] = *(unsigned int *)out;
  return 1;
}

int main(int argc, char **argv) {
  unsigned int total;
  if (argc != 2 || !sscanf(argv[1], "%u", &total)) {
    printf("fibonacci: prints the first few Fibonacci numbers\n"
           "    usage: %s [n]\n",
           argv[0]);
    return EXIT_FAILURE;
  }
  unsigned int init[2] = {1, 0};
  unsigned int n = 0;
  for_each(unsigned int, x, iterator_new(sizeof(init), init, fibonacci_next), {
    if (n++ == total) {
      break;
    }
    printf("%u ", x);
  });
  printf("\n");
  return EXIT_SUCCESS;
}
