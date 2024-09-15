#include <mpi.h>


int main(int argc, char **argv) {
    char msg[40];
    int myrank;
    MPI_STATUS status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0) {
        strcpy(msg, "Hello, there!");
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
    } else if (myrank == 1) {
        MPI_Recv(msg, 40, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("Received: %s\n", msg);
        printf("Status: \n");
        printf("Source: %d\n", status.MPI_SOURCE);
        printf("Tag: %d\n", status.MPI_TAG);
        printf("Error: %d\n", status.MPI_ERROR);
    }
    MPI_Finalize();
}