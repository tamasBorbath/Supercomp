#include <stdlib.h>

#include "distribution.h"


int min (a,b)
{
    if (a>b) { return b;}
    else {return a;}
}


void parallel_init(int myrank, int nprocs, int nintci, int nintcf, int *local_nintci, int *local_nintcf,double **local_global_index)
{

    int i_quotient, i_remainder;
    
	/** Domain Decomposition ***/

    i_quotient  = (nintcf-nintci+1) / nprocs;
    i_remainder = (nintcf-nintci+1) % nprocs;

    *local_nintci = myrank       * i_quotient + min(myrank     , i_remainder) + 1;
    *local_nintcf = (myrank + 1) * i_quotient + min(myrank + 1 , i_remainder);

    if ( ( *local_global_index = (double *) malloc(( *local_nintcf - *local_nintci ) * sizeof(double) ) )
        == NULL ) 
    {
        printf( "malloc failed to allocate distr array" );
        exit(1);
    }

    for ( int i = 0; i < *local_nintcf - *local_nintci ; i++ )
    {
        *local_global_index[i] = *local_nintci + i;
    }

}
