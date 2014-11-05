/**
 * Initialization step - parse the input file, compute data distribution, initialize LOCAL computational arrays
 *
 * @date 22-Oct-2012, 03-Nov-2014
 * @author V. Petkov, A. Berariu
 */

#include <stdlib.h>

#include "util_read_files.h"
#include "initialization.h"
#include "string.h"
#include "stdio.h"

/* @param input_key: 1 - tjunc
 2 - drall
 3 - pent
 4 - cojack
 * @param part_key: 1 - classic
 2 - dual
 3 - nodal
 * @param read_key: 1 - oneread
 2 - allread
 */
void getFlags(int* input_key, char* file_in, int* part_key, char* part_type, int* read_key, char* read_type) {
	// getting value for file_in
	if (strcmp(file_in, "tjunc.bin") == 0)
		*input_key = 1;
	else if (strcmp(file_in, "drall.bin") == 0)
		*input_key = 2;
	else if (strcmp(file_in, "pent.bin") == 0)
		*input_key = 3;
	else if (strcmp(file_in, "cojack.bin") == 0)
		*input_key = 4;
	else {
		printf("\nWrong input file name specified\nOptions are: tjunc.bin, drall.bin, pent.bin, cojack.bin\n");
		exit(1);
	}
	// getting value for part_type
	if (strcmp(part_type, "classic") == 0)
		*part_key = 1;
	else if (strcmp(part_type, "dual") == 0)
		*part_key = 2;
	else if (strcmp(part_type, "nodal") == 0)
		*part_key = 3;
	else {
		printf("\nWrong partitioning type specified\nOptions are: classic, dual, nodal\n");
		exit(1);
	}
	// getting value for read_type
	if (strcmp(read_type, "oneread") == 0)
		*read_key = 1;
	else if (strcmp(read_type, "allread") == 0)
		*read_key = 2;
	else {
		printf("\nWrong partitioning type specified\nOptions are: classic, dual, nodal\n");
		exit(1);
	}
}

int initialization(char* file_in, char* part_type, char* read_type, int nprocs, int myrank, int* nintci, int* nintcf, int* nextci,
		int* nextcf, int*** lcc, double** bs, double** be, double** bn, double** bw, double** bl, double** bh, double** bp, double** su,
		int* points_count, int*** points, int** elems, double** var, double** cgup, double** oc, double** cnorm, int** local_global_index) {
	// ======== Setting up flags for test functions =========
	int input_key = 0;
	int part_key = 0;
	int read_key = 0;
	getFlags(&input_key, file_in, &part_key, part_type, &read_key, read_type);
	printf("input: %d partitioning: %d read: %d\n", input_key, part_key, read_key);
	// ======== Setting up flags for test functions =========
	/********** START INITIALIZATION **********/
	int i = 0;
	// read-in the input file
	int f_status = read_binary_geo(file_in, &*nintci, &*nintcf, &*nextci, &*nextcf, &*lcc, &*bs, &*be, &*bn, &*bw, &*bl, &*bh, &*bp, &*su,
			&*points_count, &*points, &*elems);

	if (f_status != 0)
		return f_status;

	*var = (double*) calloc(sizeof(double), (*nextcf + 1));
	*cgup = (double*) calloc(sizeof(double), (*nextcf + 1));
	*cnorm = (double*) calloc(sizeof(double), (*nintcf + 1));

	// initialize the arrays
	for (i = 0; i <= 10; i++) {
		(*cnorm)[i] = 1.0;
	}

	for (i = (*nintci); i <= (*nintcf); i++) {
		(*var)[i] = 0.0;
	}

	for (i = (*nintci); i <= (*nintcf); i++) {
		(*cgup)[i] = 1.0 / ((*bp)[i]);
	}

	for (i = (*nextci); i <= (*nextcf); i++) {
		(*var)[i] = 0.0;
		(*cgup)[i] = 0.0;
		(*bs)[i] = 0.0;
		(*be)[i] = 0.0;
		(*bn)[i] = 0.0;
		(*bw)[i] = 0.0;
		(*bh)[i] = 0.0;
		(*bl)[i] = 0.0;
	}
	// =============Doing the test function calls=================
//	int write_pstats_exectime(int input_key, int part_key, int read_key, int my_rank, long long time_usec);
	return 0;
}

