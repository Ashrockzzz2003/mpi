#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i;
    int sendbuf, recvbuf; // Adjust data type and size as needed

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize send buffer with rank-specific data
    sendbuf = rank;
    // Print rank-specific data
    printf("Process %d: %d\n", rank, sendbuf);

    // Example operations:
    MPI_Op op = MPI_SUM; // Replace with desired operation (e.g., MPI_MAX, MPI_MIN)

    // Perform MPI_Reduce
    MPI_Reduce(&sendbuf, &recvbuf, 1, MPI_INT, op, 0, MPI_COMM_WORLD);

    // Print reduced value on root process (rank 0)
    if (rank == 0) {
        printf("Reduced value: %d\n", recvbuf);
    }

    MPI_Finalize();
    return 0;
}
