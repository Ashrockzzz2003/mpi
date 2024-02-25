#include "stdio.h"
#include "mpi.h"

#define ARRAY_SIZE 8

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

    MPI_Scatter(sendbuf, 1, MPI_INT, &recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received value: %d\n", world_rank, recvbuf);

    MPI_Finalize();
    return 0;
}
