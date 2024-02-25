#include "stdio.h"
#include "mpi.h"

int main(int argc, char *argv[]) {
    MPI_Status status;
    MPI_Request request;
    int world_rank;
    int num_processes;

    char send_buffer[4] = "MPI";
    char receive_buffer[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    // Using MPI_Isend and MPI_Irecv for asynchronous communication
    if (world_rank == 0) {
        printf("Process 0 sending message: %s\n", send_buffer);
        MPI_Isend(send_buffer, 4, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request);
    } else if (world_rank == 1) {
        MPI_Irecv(receive_buffer, 4, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &request);
        printf("Process 1 received message: %s\n", receive_buffer);
    }

    MPI_Barrier(MPI_COMM_WORLD); // Wait for all processes to reach this point

    // Using MPI_Bcast for broadcasting the message from process 0 to all other processes
    MPI_Bcast(send_buffer, 4, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("Process %d received broadcasted message: %s\n", world_rank, send_buffer);

    MPI_Finalize();
}
