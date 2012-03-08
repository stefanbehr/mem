/*
 * filename: getmem.c
 * group id: q
 * members: Joshua Andersen, Stefan Behr
 * project: HW 6, part 1
 */

#include "mem_impl.h"

/*
 * Returns a pointer to a block of memory. 
 *
 * Args:
 *   size --
 *     the size of the memory block in bytes
 */
void * getmem(size_t size) {
  block * request = NULL;
  if (free_list == NULL) {
    free_list = (block *) malloc(CHUNK);
    free_list->size = CHUNK;
    request = partition(free_list, get_size_16(size));
    mem_allocated = CHUNK;
  } 
  else {
    block * prev;
    block * current = free_list;
    while (current != NULL) {
      if (current->size > size) { 
	if (current->size * (PARTITION_THRESHOLD) >= size) { 
	  request = partition(current, get_size_16(size));
	  if (prev != NULL) {
	    size_t addr = (size_t) current + get_size_16(size);
	    prev->next = (block *) addr;
	  }
	}
	else {
	  if (prev != NULL) {
	    prev->next = current->next;
	  }
	  request = current;
	  current->next = NULL;
	}
	break;
      }
      else {
	prev = current;
	current = current->next;
      }
    }
    if (request == NULL) { 
      block * chunk = (block *) malloc(CHUNK);
      mem_allocated += CHUNK;
      chunk->size = CHUNK;
      block * new = partition(chunk, get_size_16(size));
      size_t addr = (size_t) chunk + get_size_16(size);
      prev->next = (block *) addr;
      request = new;
    }
  }
  size_t addr = (size_t) request + 16;
  return (void *) addr;
}

/*
 * Partitions a memory block and returns a void pointer to the memory partition.
 *
 * Args:
 *   memory_block --
 *     the block to partition
 *   size --
 *     the size of the partition
 */
block * partition(block * memory_block, size_t size) {
  block * next = memory_block->next;
  size_t old_size = memory_block->size;
  size_t addr1 = (size_t) memory_block;
  size_t addr2 = (size_t) memory_block + size;
  char is_front_of_list = free_list == memory_block ? '1' : '0';

  memory_block->size = size;
  memory_block = (block *) addr2;
  memory_block->size = old_size - size;
  memory_block->next = next;
  if (is_front_of_list == '1') {
    free_list = memory_block;
  }
  return (block *) addr1;
}

/*
 * Returns the next highest multiple of 16 from size.
 *
 * Args:
 *   size --
 *     size of the memory block
 */
size_t get_size_16(size_t size) {
  size_t next = (size/16);
  return (next + 1) * 16;
}
