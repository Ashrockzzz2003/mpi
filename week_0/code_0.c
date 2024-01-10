// To compile in MacOS:
// Compile: mpicc -o code_0 code_0.c
// Run: mpirun -np 4 ./code_0
// the 4 is the number of processes to run

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
    printf("Hello, world!  I am %d of %d and the version is %s\n", rank, size, version);
    MPI_Finalize();

    return 0;
}