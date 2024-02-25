#include "stdio.h"
#include "mpi.h"

#define ARRAY_SIZE 4

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int sendbuf[ARRAY_SIZE];
    int recvbuf;

    if (world_rank == 0) {
        // Initialize the send buffer in the root process
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            sendbuf[i] = i * i;
        }
    }

    // Scatter the array from root process to all other processes
    MPI_Scatter(sendbuf, 1, MPI_INT, &recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Modify the received value
    recvbuf *= world_rank;

    // Gather the modified values back to the root process
    int gatherbuf[ARRAY_SIZE];
    MPI_Gather(&recvbuf, 1, MPI_INT, gatherbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Root process received values: ");
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            printf("%d ", gatherbuf[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
