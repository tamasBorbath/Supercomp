#include <stdlib.h>

#include "distribution.h"


void parallel_init(int myrank, int nprocs, int nintci, int nintcf, int *local_nintci, int *local_nintcf)
{

    int i_quotient, i_remainder;
	/** Domain Decomposition ***/

    i_quotient  = (nintcf-nintci+1) / nprocs;
    i_remainder = (nintcf-nintci+1) % nprocs;

    *local_nintci = myrank       * i_quotient + min(myrank     , i_remainder) + 1;
    *local_nintcf = (myrank + 1) * i_quotient + min(myrank + 1 , i_remainder);

}
