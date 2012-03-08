/*
 * filename: print_heap.c
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

#include "mem_impl.h"

/*
 * Prints a formatted list to file f of blocks on the free list, giving 
 * at least the address and length of one block per line of output.
 *
 * Args:
 *  f --
 *    pointer to file to which output is to be written
 */
void print_heap(FILE *f) {

  block * temp = free_list;
  if (free_list->next != NULL) {
    free_list->next = NULL;
  }
  while (temp != NULL) {; // need to ensure in getmem last element always points to null
    fprintf(f, "%p %x\n",temp, (int)temp->size);
    temp = temp->next;
  }
}
