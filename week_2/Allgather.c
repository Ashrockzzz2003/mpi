#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i;
    int sendbuf[10], recvbuf[10 * size];  // Adjust sizes as needed

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize send buffer with rank-specific data
    for (i = 0; i < 10; i++) {
        sendbuf[i] = rank * 10 + i;
    }

    // Perform MPI_Allgather
    MPI_Allgather(sendbuf, 10, MPI_INT, recvbuf, 10, MPI_INT, MPI_COMM_WORLD);

    // Print gathered data on each process
    printf("Process %d:\n", rank);
    for (i = 0; i < 10 * size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
