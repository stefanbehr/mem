/*
 * Sanity tests.
 */
#include <stdio.h>
#include "mem.h"
#include "mem_impl.h"
#include "freemem.c"
#include "getmem.c"

void print_list();
void print_list_header();
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
  
  printf("\n> Making the following memory allocations...\n");
  char * c = getmem(900);
  char * d = getmem(200);
  char * e = getmem(100);
  printf("%p %d\n", c, (int)get_size_16(900));
  printf("%p %d\n", d, (int)get_size_16(200));
  printf("%p %d\n", e, (int)get_size_16(100));
  
  printf("\n> Freeing previous allocations, one at a time in reverse order...\n");
  freemem((void*)e);
  print_list_header();
  print_list();
  freemem((void*)d);
  print_list_header();
  print_list();
  freemem((void*)c);
  print_list_header();
  print_list();

  printf("\n> Making the following memory allocations...\n");
  char * f = getmem(400);
  char * g = getmem(200);
  char * h = getmem(300);
  printf("%p %d\n", c, (int)get_size_16(400));
  printf("%p %d\n", d, (int)get_size_16(200));
  printf("%p %d\n", e, (int)get_size_16(300));
  


  printf("\n> Freeing the first allocated block,\n");
  printf("> then the third allocated block, \n");
  printf("> and then the second allocated block...\n");
  freemem((void*)f);
  print_list_header();
  print_list();
  freemem((void*)g);
  print_list_header();
  print_list();
  freemem((void*)h);
  print_list_header();
  print_list();
  printf("\n");

}

void print_list_header() {
  printf("> Free_list is:\n");
}


void print_list() {
  block * temp = free_list;
  while (temp != NULL) {
    printf("%p %d\n", temp, (int)temp->size);
    temp = temp->next;
  }
}
