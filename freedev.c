/* Tests for freemem.c */

#include "mem_impl.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BLOCKS 9
#define FREEING "> Freeing block %d of %d:\n"
#define BORDER "\n"

void print_free_list();
void print_block(block *);
void * fspace(block *);
void free_and_print(block *, int);

int main(int argc, char **argv) {

  void *chunk = malloc(1100);

  int block_sizes[NUM_BLOCKS] = {80, 450, 200, 100, 56, 44, 20, 50, 100};
  block * blocks[NUM_BLOCKS];

  // initialize blocks

  printf("\nInitializing blocks...\n");
  int i;
  void *place_in_chunk = chunk;
  for (i = 0; i < NUM_BLOCKS; i++) {
    blocks[i] = (block *) place_in_chunk;
    blocks[i]->size = block_sizes[i];
    blocks[i]->next = NULL;
    printf("%p\t%d\n", place_in_chunk, block_sizes[i]);
    place_in_chunk += block_sizes[i];
  }
  printf("\n");

  printf("> CASE 1: free block onto empty free list\n");
  int bi = NUM_BLOCKS/3; // index into blocks list
  free_and_print(blocks[bi], bi);

  printf("> CASE 2: free block to start of non-empty free list (NO MERGE)\n");
  bi -= 2;
  free_and_print(blocks[bi], bi);

  printf("> CASE 3: free block to end of non-empty free list (NO MERGE)\n");
  bi += 6;
  free_and_print(blocks[bi], bi);

  printf("> CASE 4: free block between two other freed blocks with which\n");
  printf("> it's not contiguous (NO MERGE)\n");
  bi -= 2;
  free_and_print(blocks[bi], bi);

  printf("> CASE 5: free block to end of non-empty free list (MERGE w/left)\n");
  bi += 3;
  free_and_print(blocks[bi], bi);

  printf("> CASE 6: free block to start of n-e free list (MERGE w/right)\n");
  bi -= 8;
  free_and_print(blocks[bi], bi);

  printf("> CASES 7, 8, 9: free blocks each go between two blocks with\n"); 
  printf("> which they're contiguous (MERGE w/left & right)\n");
  while (bi < 6) {
    bi += 2;
    free_and_print(blocks[bi], bi);
  }

  return 0;
}

void print_block(block *b) {
  printf("%p %ld\tnext: %p\tend: %4p\n", b, b->size, b->next, (void *) b + b->size);
}

void print_free_list() {
  printf("\n> Printing free list...\n");
  if (free_list == NULL) {
    printf("NULL\n\n");
  } else {
    block *current = free_list;
    while (current != NULL) {
      print_block(current);
      current = current->next;
    }
  }
}

// converts block pointer to pointer to block's free space
void * fspace(block *b) {
  return (void *) b + BLOCK_HEADER_SIZE;
}

void free_and_print(block *b, int pos) {
  //printf("\n");
  printf(FREEING, pos, NUM_BLOCKS);
  print_block(b);
  freemem(fspace(b));
  print_free_list();
  printf("\n");
}
