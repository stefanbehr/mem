/*
 * filename: mem.h
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

/*
 * Public interface memory management. See source for verbose comments.
 *
 * Functions:
 *   freemem --
 *     frees a particular block of previously requested memory
 *   getmem --
 *      returns an a pointer to a requested block of memory
 *   get_mem_stats --
 *      prints statistics on memory usage
 *   print_heap --
 *      prints heap contents
 */

#ifndef MEM_H // start preprocessor guard
#define MEM_H

#include <stdlib.h>
#include <stdio.h>

void * getmem(size_t size);

void get_mem_stats(size_t *total_size, size_t *total_free, size_t *n_free_blocks);

void freemem(void *p);

void print_heap(FILE *f);

#endif // #ifndef MEM_H
