#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"

int main() {
  block *i = (block*)malloc(sizeof(block));
  void *j = (void *) i + 16;
  printf("%p %p\n", i, j);
  return 0;
}
