#include "stdio.h"
#include "mpi.h"

#define ARRAY_SIZE 4

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int sendbuf = world_rank * 2;
    int recvbuf[ARRAY_SIZE];

    MPI_Gather(&sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Root process received values: ");
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            printf("%d ", recvbuf[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
