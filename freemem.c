/*
 * filename: freemem.c
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

#include <stdio.h>

#include "mem_impl.h"

/*
 * Frees a block of storage at location p (puts it back in the pool of available 
 * storage), unless p is NULL, in which case nothing happens and freemem
 * returns immediately.
 * 
 * Args:
 *   p --
 *     a pointer to the block of storage we wish to free
 */
void freemem(void *p) {
  if (p == NULL) {
    return;
  }
  block *free_block = (block *) (p - BLOCK_HEADER_SIZE);
  free_block->next = NULL;
  if (free_list == NULL) {
    free_list = free_block;
  } else {
    block *prev =  NULL;
    block *current = free_list;
    while (current != NULL) {
      if (free_block < current) {
	free_block->next = current;
	if (prev != NULL) {
	  // insert free block between previous and current blocks
	  prev->next = free_block;
	} else {
	  // insert free block at beginning of free list
	  free_list = free_block;
	}
	break;
      } else {
	prev = current;
	current = current->next;
      }
    }
    // post: current is either NULL (free_block goes to end of free list),
    // or not, and we broke out of loop (prev may be NULL)
    if (current == NULL) {
      // insert free block at end of free list
      prev->next = free_block;
    }
    // merge adjacent blocks in free list if exist and contiguous:
    if (current != NULL) {
      void *end_of_free_block = (void *) free_block + free_block->size;
      if (end_of_free_block == (void *) current) {
	// merge free block w/block to right
	free_block->size = free_block->size + current->size;
	free_block->next = current->next;
      }
    }
    if (prev != NULL) {
      void *end_of_prev_block = (void *) prev + prev->size;
      if (end_of_prev_block == (void *) free_block) {
	// merge free block w/block to left
	prev->size = prev->size + free_block->size;
	prev->next = free_block->next;
      }
    }
  }
}
