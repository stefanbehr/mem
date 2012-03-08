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
 *     total amount of storage in bytes acquired by the memory manager so far to
 *     use in satisfying allocation requests
 *   total_free --
 *     the total amount of storage in bytes that is currently stored on the free
 *     list, includes space occupied by header information or free block links
 *   n_free_blocks --
 *     the total number of individual blocks currently stored on the free list
 */
void get_mem_stats(size_t *total_size, size_t *total_free, size_t *n_free_blocks) {

}
