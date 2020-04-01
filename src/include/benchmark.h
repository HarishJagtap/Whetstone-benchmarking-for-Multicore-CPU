#ifndef BENCHMARK_H
#define BENCHMARK_H

#ifdef __linux__ 
    #include <unistd.h>
    #include <pthread.h>
#elif _WIN32
    #include <Windows.h>
#endif

#include <time.h>   // ftime used to measure time in millisecs
#include <math.h>   // for ceil and log2 function

#include "whetstone.h"
#include "csvfile.h"

#define MAX_THREAD_COUNT 1024

void clear_array (void *arr, size_t size, int count);

int get_num_cores ();

/* Takes start and finish times of all threads, get lowest start time, get highest finish time
 * MWIPS score = (loopcount * number of threads) / (10 * (highest finish time in secs - lowest start time in secs)) */
long compute_mwips (int num_threads);

/* Returns 0 if successful or -1 if failed
 * Failure can occur if unable to
 * 1. create threads
 * 2. get number of cores of cpu */ 
int run_benchmark (whetint ploopcount);

#endif