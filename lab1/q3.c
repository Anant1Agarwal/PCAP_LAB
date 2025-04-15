#include<stdio.h>
#include <mpi.h>

// simple calculator
int main(int argc, char** argv){
    
    MPI_Init(&argc,&argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int operation=rank;

    printf("we are in rank %d ---->",rank);
    int x=5, y=7;
    switch(operation){
        case 0: //add
            printf("we are adding %d, %d,result: %d\n",x,y,x+y);
            break;
        case 1: //substract
            printf("we are substract %d, %d,result:%d\n",x,y,x-y);
            break;
        case 2: //multiply
            printf("we are multiplying %d, %d,result:%d\n",x,y,x*y);
            break;
        case 3: //divide
            printf("we are dividing %d, %d,result:%.3f\n",x,y,((double)x/y));
            break;
        default: //invalud
            printf("invalid case\n");
            break;
    }

    fflush(stdout);

    MPI_Finalize();
    return 0;

}