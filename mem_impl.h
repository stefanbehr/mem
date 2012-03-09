/*
 * filename: mem_impl.h
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

#ifndef MEM_IMPL_H // start preprocessor guard
#define MEM_IMPL_H
#define CHUNK 10000
#define BLOCK_HEADER_SIZE 16
#define PARTITION_THRESHOLD .75
#include <stdio.h>
#include "mem.h"

typedef struct block {
  size_t size; 
  struct block * next;
} block;

block * free_list;

size_t get_size_16(size_t size);

size_t mem_allocated;

void get_mem_stats(size_t *total_size, size_t *total_free, size_t *n_free_blocks);



block * partition(block * memory_block, size_t size);

#endif // #ifndef MEM_IMPL_H
