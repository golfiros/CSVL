#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CSVL/vector.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("to_upper: converts input string to uppercase\n"
           "   usage: %s [string]\n",
           argv[0]);
    return EXIT_FAILURE;
  }
  size_t len = strlen(argv[1]);
  vector_t *string = vector_new(sizeof(char), 0);
  for (size_t i = 0; i < len; i++) {
    vector_append(string, argv[1] + i);
  }
  for_each(char, c, vector_iterator_val(string, 0), {
    if (c >= 'a' && c <= 'z') {
      c = c - 'a' + 'A';
    }
    printf("%c", c);
  });
  printf("\n");
  return EXIT_SUCCESS;
}
