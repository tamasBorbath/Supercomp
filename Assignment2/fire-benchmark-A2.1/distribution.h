#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_

#include <stdio.h>

void parallel_init(int myrank, int nprocs, int nintci, int nintcf, int *local_nintci, int *local_nintcf, double **local_global_index);

#endif 