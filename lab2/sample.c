#include <stdio.h>
#include <mpi.h>

// sends a number to another process which recieves it and prints it
int main(int argc, char** argv){

    MPI_Init(&argc,&argv);

    int x, rank;
    int recv;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    MPI_Status stat;

    if(rank==0){
        fprintf(stdout,"Enter Number in master process: ");
        fflush(stdout);
        scanf("%d", &x);
        
        //in this way, sent print statement is always printed first before sending
        // if used before sending, any of the recived or sent statement can be printed 
        fprintf(stdout, "I have sent number %d from process 0 to rank 1\n",x);
        fflush(stdout);
        MPI_Ssend(&x,1, MPI_INT, 1, 999, MPI_COMM_WORLD);
       
    }
    else{
        MPI_Recv(&recv,1, MPI_INT, 0, 999,MPI_COMM_WORLD,&stat);
        fprintf(stdout, "I have recieved number %d from process 0 in rank 1\n", recv);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}
// root@807604e088ff:/workspaces/PCAB_LAB/lab2# mpirun-root -np 2 ./output
// 8 
// Enter Number in master process: I have sent number 8 from process 0 to rank 1
// I have recieved number 8 from process 0 in rank 1