#include <stdio.h>
#include <stdlib.h>     // For strtol (convert string to long int)
#include <string.h>

#include "benchmark.h"

#ifdef __linux__ 
#define OS_SUCCESS
#elif _WIN32
#define OS_SUCCESS
#endif

char * help_string = "This is a benchmarking tool for multicore cpu, uses whetstone benchmarking.\n"
"The program generates csv file which contains (no of threads vs mwips (benchmark score)).\n\n"
"Usage:  -H or --help for this help text.\n"
"        -lc [number] (Ex: -lc 20) for setting the loopcount or duration of benchmark.\n"
"               If unspecified, default of 10000 is taken.\n"
"               Use a lower number if duration is too long.\n\n";

int main (int argc, char **argv)
{
    #ifndef OS_SUCCESS
    printf("Program does not support this operating system...exiting\n");
    return 0;
    #endif

    // Default value of loopcount
    long int loopcount = 10000;

    /* Support two types of command line arguments
     * 1. -H or --help to show help text and exit
     * 2. -lc [number] to set the loopcount variable to vary benchmark duration */

    if (argc == 2) {

        if (strncmp(argv[1], "-H", 2) == 0 ||
            strncmp(argv[1], "--help", 6) == 0) {

            printf("\n%s", help_string);
            return 0;
        }
        else {

            printf("\nWrong Usage: try -H for help\n");
            return 0;
        }
    }

    if (argc == 3) {

        if (strncmp(argv[1], "-lc", 3) == 0) {

            long int num = strtol(argv[2], NULL, 10);

            if (num <= 0) {

                printf("\nValue should be positive integer...exiting\n");
                return 0;
            }
            else {

                loopcount = num;
            }
        }
        else {

            printf("\nWrong Usage: try -H for help\n");
            return 0;
        }
    }

    // Run the benchmark

    if (run_benchmark((whetint) loopcount) !=0 ) {

        printf("\nBenchmark failed...exiting\n");
        return 0;
    }

    // Plot the graph using gnuplot

    #ifdef __linux__ 
    system("./plot_graph_lin.sh");
    #elif _WIN32
    system("plot_graph_win.bat");
    #endif

    return 0;
}