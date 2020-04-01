#include <stdlib.h>
#include <sys/timeb.h>

#include "benchmark.h"

// controls the duration of benchmark
// This value is read by all threads
whetint loopcount;

// Each thread runs whetstone benchmark, the start time and finish time is stored in an element of array
struct timeb startsec[MAX_THREAD_COUNT];
struct timeb finishsec[MAX_THREAD_COUNT];

int get_num_cores ()
{
    int num_cores = 0;

    #ifdef __linux__ 
    num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    #elif _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    num_cores = sysinfo.dwNumberOfProcessors;
    #endif

    return num_cores;
}

#ifdef __linux__
void * thread_function (void *arg)
{
    // Each thread running in a test, has to uniquely index the startsec, finishsec array to stores time
    int index = *((int *) arg);

    struct timeb tstartsec, tfinishsec;

    // Get start time
    ftime(&tstartsec);

    // Run benchmark
    whetstone (loopcount);

    // Get finish time
    ftime(&tfinishsec);

    startsec[index]     = tstartsec;
    finishsec[index]    = tfinishsec;

    return 0;
}
#elif _WIN32
DWORD WINAPI thread_function (LPVOID lpParam) 
{
    // Each thread running in a test, has to uniquely index the startsec, finishsec array to stores time
    int index = *((int *) lpParam);

    struct timeb tstartsec, tfinishsec;

    // Get start time
    ftime(&tstartsec);

    // Run benchmark
    whetstone (loopcount);

    // Get finish time
    ftime(&tfinishsec);

    startsec[index]     = tstartsec;
    finishsec[index]    = tfinishsec;

    return 0;
}
#endif

// Set all elements of array to zero
void clear_array (void *arr, size_t size, int count)
{
    for (int i = 0; i < count; i++) {

        for (int j = 0; j < size; j++)
            *(((char *) arr) + size * i + j) = 0;
    }
}

// Convert timeb structure to milliseconds
long timeb_to_msec (struct timeb time)
{
    return (time.time * 1000 + time.millitm);
}

long compute_mwips(int num_threads)
{
    struct timeb startsec_min   = startsec[0];
    struct timeb finishsec_max  = finishsec[0];

    // Get the lowest start time and highest finish time
    for (int i = 1; i < num_threads; i++) {

        if (timeb_to_msec(startsec_min) > timeb_to_msec(startsec[i]))
            startsec_min = startsec[i];

        if (timeb_to_msec(finishsec_max) < timeb_to_msec(finishsec[i]))
            finishsec_max = finishsec[i];
    }

    // Compute MWIPS score for a test
    long mwips = (loopcount * num_threads * 100) / (timeb_to_msec(finishsec_max) - timeb_to_msec(startsec_min));

    #ifdef DEBUG
    printf ("Time taken: %ld millisecs\n", timeb_to_msec(finishsec_max) - timeb_to_msec(startsec_min));
    #endif

    return mwips;
}

/* Runs 'x^2' no of tests on a 'x' core cpu
 * Ex: Runs 16 no of tests on a 4 core cpu
 * 
 * Each test runs a certain no of threads, and each thread runs the benchmark,
 *  a collective MWIPS score is calculated for a test
 * 
 * Tests run on a 'x' core cpu are
 * 1. Test with 1 thread
 * 2. Test with 2 threads
 * 3. Test with 4 threads, Test with 4*2=8 threads,  8*2=16 threads, until x*x threads
 * 
 * Result is stored in csv format file, with columns as (No. of threads, MWIPS score) */

int run_benchmark (whetint ploopcount)
{
    int num_cores   = get_num_cores();
    FILE *csvfile   = open_csv_file();
    int num_tests   = num_cores * num_cores;

    loopcount = ploopcount;

    printf("No of cpu cores: %d\n", num_cores);
    printf("Will execute %d tests\n", (int)ceil(log2(num_tests)) + 1); 

    write_csv_fileheading(csvfile);

    if (num_cores <= 0) {

        close_csv_file(csvfile);
        return -1;
    }

    printf ("Starting benchmark\n");

    // Run the 'x*x' no of tests for a 'x' core cpu
    for (int i = 1; i <= num_tests;) {

        printf ("Executing %d threads...%.1f%% done\n", i, (i * 50) / (float)num_tests);

        clear_array((void *) startsec, sizeof(long), MAX_THREAD_COUNT);
        clear_array((void *) finishsec, sizeof(long), MAX_THREAD_COUNT);

        #ifdef __linux__
        pthread_t * thread_id = (pthread_t *) malloc(sizeof(pthread_t) * i);
        #elif _WIN32
        HANDLE * thread_id = (HANDLE *) malloc(sizeof(HANDLE) * i);
        #endif

        int * index = (int *) malloc(sizeof(int) * i);
        
        // Create i threads

        #ifdef DEBUG
        printf ("Creating Threads\n");
        #endif

        for (int j = 0; j < i; j++) {

            index[j] = j;

            #ifdef __linux__
            if (pthread_create(&thread_id[j], NULL, thread_function, &index[j]) != 0) {

                close_csv_file(csvfile);
                return -1;
            }
            #elif _WIN32
            thread_id[j] = CreateThread(NULL, 0, thread_function, &index[j], 0, NULL);

            if (thread_id[j] == NULL) {

                close_csv_file(csvfile);
                return -1;
            }
            #endif
        }

        #ifdef DEBUG
        printf ("Waiting for threads\n");
        #endif

        #ifdef _WIN32
        WaitForMultipleObjects(i, thread_id, TRUE, INFINITE);
        #endif

        for (int j = 0; j < i; j++) {

            #ifdef __linux__
            if (pthread_join(thread_id[j], NULL) != 0) {

                close_csv_file(csvfile);
                return -1;
            }
            #elif _WIN32
            CloseHandle(thread_id[j]);
            #endif
        }

        free(thread_id);
        free(index);

        #ifdef DEBUG
        printf ("Computing MWIPS\n");
        #endif

        // Calculate MWIPS score and write to csv file
        long mwips = compute_mwips(i);

        write_csv_file(csvfile, i, mwips);

        /* Ex:  For a 6 core cpu, tests with 1, 2, 4, 8, 16, 32 threads are run
         *      the final test with 64 threads is NOT run, instead test with 36 (6^2) threads is run */
        if (i != num_tests && i * 2 > num_tests) {

            i = num_tests;
        }
        else {

            i *= 2;
        }

        #ifdef DEBUG
        printf ("Done\n");
        #endif
    }

    close_csv_file(csvfile);

    printf ("Finished Benchmark\n");

    return 0;
}