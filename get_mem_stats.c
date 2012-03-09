/*
 * filename: get_mem_stats.c
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

#include "mem_impl.h"

/*
 * Stores statistics about the state of the memory manager.
 *
 * 
 * Args:
 *   total_size --
 *     location for recording total amount of storage in bytes acquired by the 
 *     memory manager so far to use in satisfying allocation requests
 *   total_free --
 *     location for recording the total amount of storage in bytes that is 
 *     currently stored on the free list, includes space occupied by header 
 *     information or free block links
 *   n_free_blocks --
 *     location for recording the total number of individual blocks currently 
 *     stored on the free list
 */
void get_mem_stats(size_t *total_size, size_t *total_free, size_t *n_free_blocks) {
  *total_size = mem_allocated; // global var in mem_impl.h
  *total_free = 0;
  *n_free_blocks = 0;
  if (free_list != NULL) {
    block *current = free_list;
    while (current != NULL) {
      *total_free += current->size;
      *n_free_blocks += 1;
      current = current->next;
    }
  }
}
