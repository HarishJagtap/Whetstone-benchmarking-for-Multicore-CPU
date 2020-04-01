#include "csvfile.h"

FILE* open_csv_file ()
{
    return fopen("result/whetstone.csv","w");
}

void write_csv_file (FILE *fp, int num_threads, long mwips)
{
    fprintf (fp, "%d,%ld\n", num_threads, mwips);
}

void write_csv_fileheading (FILE *fp)
{
    fprintf (fp, "No. of threads,MWIPS\n");
}

int close_csv_file (FILE *fp)
{
    return fclose(fp);
}