#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    printf("Hello from rank %d out of %d processors\n", world_rank, world_size);

    MPI_Finalize();
    return 0;
}

// echo 'export OMPI_ALLOW_RUN_AS_ROOT=1' >> ~/.bashrc
// echo 'export OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1' >> ~/.bashrc
// echo 'alias mpirun-root="mpirun --allow-run-as-root --oversubscribe"' >> ~/.bashrc
// root@2ab591d3d73c:/workspaces/PCAB_LAB# source ~/.bashrc
// mpicc hello_mpi.c -o hello_mpi
// mpirun-root -np 4 ./hello_mpi
