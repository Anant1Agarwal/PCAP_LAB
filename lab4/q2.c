#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>


int main(int argc, char** argv){
    MPI_Init(&argc,&argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int *mat=(int *)malloc(9*sizeof(int));
    int ele;
    int *l_mat=(int *)malloc(3*sizeof(int));

    if(rank==0){
        fprintf(stdout,"Enter 9 elements in matrix: ");
        fflush(stdout);
        for (int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf("%d",&mat[(3*i)+j]);
            }
        }

        fprintf(stdout,"\nEnter element to be searched: ");
        fflush(stdout);
        scanf("%d",&ele);
        
    }

    MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(mat,3, MPI_INT,l_mat,3,MPI_INT,0,MPI_COMM_WORLD );

    int oc=0;
    for(int i=0;i<3;i++){
        if(l_mat[i]==ele){
            oc+=1;
        }
    }
    int finalans;
    MPI_Reduce(&oc,&finalans,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0){
        fprintf(stdout,"\n element %d occured %d times\n", ele, finalans);
        fflush(stdout);
    }
    

    MPI_Finalize();
    return 0;
}


// root@807604e088ff:/workspaces/PCAB_LAB/lab4# mpirun-root -np 3 ./output
// Enter 9 elements in matrix: 1 7 6 6 2 6 0 6 2

// Enter element to be searched: 6

//  element 6 occured 4 times