/*
 * filename: bench.c
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

#include "mem.h"
#include "mem_impl.h"
#include <time.h>

void print_benchmark_statistics();

void free_block_by_index(int);

/*
 * Command line benchmark for the memory manager. Randomly calls getmem, freemem
 * and stores the results.
 *
 * Args:
 *   ntrials --
 *     total number of call to perform, defaults to 10000
 *   pctget --
 *     percent of the total calls that should be getmem, defaults to 50
 *   pctlarge --
 *     percent of getmem calls that should request "large blocks" with a size
 *     greater than small_limit
 *   small_limit --
 *     largest size in bytes of a "small block", defaults to 200
 *   large_limit --
 *     largest size in bytes of a "large block", defaults to 20000
 *   random_seed --
 *     initial seed value for the random number generator
 */
int main(int argc, char **argv) {
  
  // ------------------PSEUDO PARSING BELOW------------------------
  double pctget = .7;
  double pctlarge = .5;

  int ntrials = 100;
  int small_limit = 20;
  int large_limit = 500;
  int random_seed = (int)time(NULL);
  // ------------------PSEUDO PARSING ABOVE------------------------
  
  block * get_list;
  block * last = NULL;
  get_list = last;

  int count = (int)(.1 * ntrials);
  int get_list_size = 0;
  int i;

  time_t t;
  time(&t);
    
  for (i=0; i < ntrials; i++) {
    int free = 0;
    srand(random_seed+i);
    int r = rand();
    if ((double)rand()/(double)RAND_MAX < pctget) {
      free = 1;
    }
    
    if (free && get_list != NULL) { // free a random block
      r = (double)rand()/(double)RAND_MAX;
      r = (int)(r * get_list_size);
      free_block_by_index(r);
    }
    else if (!free) { // get a block
      srand(random_seed + i);
      int random_size;
      int is_large = (double)rand()/(double)RAND_MAX < pctlarge;
      if (is_large) { // get a big block
	srand(random_seed + i*i);
	random_size = (rand() % large_limit) + small_limit;
      }
      else { // get a small block
	random_size = (rand() % small_limit) + 1;
      }
      block * new = getmem(random_size);
      if (last == NULL) { 
	last = new;
      }
      else { 
	last->next = new;
      }
      get_list_size++;
    }
  }
  if (i == count) { 
    print_benchmark_statistics();
    count += count;
  }
  return 0;
}

/*
 * Frees a memory block on the get_list at the specified index. 
 */
void free_block_by_index(int index) {
  block * temp;
  int i = 0;
  for (i = 0; i <= index; i++) {
    temp = temp->next;
  }
  size_t addr = (size_t)temp + 16;
  freemem((void *)addr);
}

/*
 * INCOMPLETE
 */
void print_benchmark_statistics() {};

