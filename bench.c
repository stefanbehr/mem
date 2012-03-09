/*
 * filename: bench.c
 * group id: q
 * members: Stefan Behr, Joshua Andersen
 * project: HW 6, part 1
 */

#include "mem.h"
#include <time.h>
#include <stdlib.h>
#include "mem_impl.h"

#define NTRIALS 10000
#define PCTGET 50
#define PCTLARGE 10
#define SMALL_LIMIT 200
#define LARGE_LIMIT 20000
#define NUM_PARAMS 6

void print_bench_stats(size_t, size_t, size_t, clock_t);

void free_block_by_index(int index, void **list);
void print_bench_stats(size_t, size_t, size_t, clock_t);

int make_random_comparison(double seed, double probability);

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
 *     greater than small_limit, defaults to 10
 *   small_limit --
 *     largest size in bytes of a "small block", defaults to 200
 *   large_limit --
 *     largest size in bytes of a "large block", defaults to 20000
 *   random_seed --
 *     initial seed value for the random number generator
 */
int main(int argc, char **argv) {

  // command-line parsing
  int params[] = {NTRIALS, PCTGET, PCTLARGE, SMALL_LIMIT, LARGE_LIMIT, (int) time(NULL)};
  
  int current_param = 1;
  while (current_param < argc && (current_param - 1) < NUM_PARAMS) {
    params[current_param - 1] = atoi(argv[current_param]);
    current_param++;
  }
  
  double pctget = (double) params[1] / 100;
  double pctlarge = (double) params[2] / 100;

  int ntrials = params[0];
  int small_limit = params[3];
  int large_limit = params[4];
  int random_seed = params[5];

  // ------------------PSEUDO PARSING BELOW------------------------
  /*
  double pctget = .7;
  double pctlarge = .5;

  int ntrials = 50;
  int small_limit = 20;
  int large_limit = 500;
  int random_seed = (int)time(NULL);
  */
  // ------------------PSEUDO PARSING ABOVE------------------------
  
  // memory statistics vars
  size_t total_size = 0;
  size_t total_free = 0;
  size_t n_free_blocks = 0;

  int max_get = ntrials;
  void *get_list[max_get];

  int count = (int)(.1 * ntrials);
  int get_list_size = 0;
  int i;

  clock_t tick_start = clock(); // start time
  clock_t elapsed;

  for (i=0; i < ntrials; i++) {
    int free = 0;
    srand(random_seed+i);
    int r = rand();

    if ((double)r/(double)RAND_MAX < pctget) { // to free or not to free
      free = 1;
    }

    if (free && get_list_size > 0 ) { // free a random block
      r = rand() % get_list_size;
      free_block_by_index(r, get_list);
      get_list_size--;
      get_list[r] = get_list[get_list_size]; // transplant last element to gap
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
      get_list[get_list_size] = getmem((size_t) random_size);
      get_list_size++;
    }

    if (i == count) {
      get_mem_stats(&total_size, &total_free, &n_free_blocks);
      elapsed = clock() - tick_start;
      print_bench_stats(total_size, total_free, n_free_blocks, elapsed);
      count += count;
    }
  }
  return 0;
}

/*
 * Frees a memory block on the get_list at the specified index. 
 */
void free_block_by_index(int index, void **list) {
  freemem(list[index]);
}

/*
 * Prints formatted benchmark statistics.
 * 
 * Args:
 *   total_size --
 *     total amount of storage in bytes acquired so far by the memory manager 
 *     from the underlying system to be used in satisfying allocation requests
 *   total_free --
 *     total storage in bytes currently stored on the free list, including space 
 *     occupied by header info
 *   n_free_blocks -- 
 *     total number of individual blocks currently on free list
 *   elapsed --
 *     CPU time (in clock ticks) elapsed in running of bench program
 */
void print_bench_stats(size_t total_size, size_t total_free, size_t n_free_blocks, clock_t elapsed) {
  size_t avg_free_block = total_free / n_free_blocks;
  printf("CPU time elapsed: %ld\tTotal storage: %ld\tFree block count: %ld\tAvg free block size: %ld\n", \
	 elapsed, total_size, n_free_blocks, avg_free_block);
}
