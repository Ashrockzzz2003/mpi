#include "stdio.h"
#include "mpi.h"

int main(int argc, char *argv[]) {
    int world_rank;
    int num_processes;

    char send_buffer[4] = "MPI";
    char receive_buffer[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    if (world_rank == 0) {
        printf("Process 0 sending message: %s\n", send_buffer);
        MPI_Send(send_buffer, 4, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Recv(receive_buffer, 4, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message: %s\n", receive_buffer);
    }

    MPI_Finalize();
}