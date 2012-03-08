/*
 * Sanity tests.
 */
#include <stdio.h>
#include "mem.h"
#include "mem_impl.h"
#include "freemem.c"
#include "getmem.c"

void print_list();
void basic_free_get(size_t i);

int main() {
  basic_free_get(20);
  return 0;
}

void basic_free_get(size_t i) {
  printf("\n> Testing allocation and free on a single block, allocating %d...\n", (int)get_size_16(i));
  char * a = getmem(i);
  printf("> Free list is:\n");
  print_list();

  printf("\n> Freeing the allocated block...\n");
  freemem((void *)a);

  printf("> Free_list is:\n");
  print_list();
  
  printf("\n> Allocating %d...\n",150);
  char * b = getmem(150);

  printf("> Free_list is:\n");
  print_list();

  printf("\n> Freeing the previously allocated memory...\n");
  freemem((void *)b); 
  printf("> Free_list is:\n");
  print_list();
  /**
  printf("\n> Making additional memory allocations...\n");
  printf("> Allocating 900, 200, 100...:")
  char * c = getmem(900);
  char * d = getmem(200);
  char * e = getmem(100);
  prinft("%p %d", c);**/
  

 

}

void print_list() {
  block * temp = free_list;
  while (temp != NULL) {
    printf("%p %d\n", temp, (int)temp->size);
    temp = temp->next;
  }
}
