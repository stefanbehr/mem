/*
 * filename: test_get.c
 * group id: q
 * members: Joshua Andersen, Stefan Behr
 * project: HW 6, part 1
 */

/* Tests for getmem.c */

#include "mem.h"
#include "mem_impl.h"
#include <stdio.h>

void print_list();

int main(int argc, char **argv) {
  
  // test sizes

  int a = 28;
  int b = 100;
  int c = 800;
  int d = 1000; // d > c
  int e = 9700; // e > d

  printf("\nAllocating memory...\n");
  char * test = (char *) getmem(a);
  char * test2 = (char *) getmem(b);
  block * test3 = (block *) getmem(c);
  test3->size = get_size_16(c);


  printf("%p %d\n",test, (int) get_size_16(a));
  printf("%p %d\n", test2, (int) get_size_16(b));
  printf("%p %d\n", test3, (int) get_size_16(c));

  printf("\nPrinting free list...\n");
  print_list();

  printf("\nMoving a new block to the front of the list...\n");
  block * copy = free_list;
  test3->next = copy;
  free_list = test3;
  print_list();

  printf("\nAllocating more memory than the size of the new block...\n");
  char * test4 = (char *) getmem(d);
  printf("%p %d\n", test4, (int) get_size_16(d));

  printf("\nPrinting free list...\n");
  print_list();

  printf("\nAllocating more memory than the size of all blocks...\n");
  char * test5 = (char *) getmem(e);
  printf("%p %d\n", test5, (int) get_size_16(e));

  printf("\nPrinting the free list...\n");
  print_list();
  printf("\n");



  
  return 0;
}

void print_list() {
  block * temp = free_list;
  while (temp != NULL) {
    printf("%p %d\n", temp, (int)temp->size);
    temp = temp->next;
  }
}





