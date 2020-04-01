#ifndef CSVFILE_H
#define CSVFILE_H

#include <stdio.h>

FILE*   open_csv_file ();

void    write_csv_file (FILE *fp, int num_threads, long mwips);
void    write_csv_fileheading (FILE *fp);

int     close_csv_file (FILE *fp);

#endif