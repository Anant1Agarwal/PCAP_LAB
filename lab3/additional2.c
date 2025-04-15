#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>

int main(int argc, char** argv){
    MPI_Init(&argc,&argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int *arr,*l_arr;
    int arr_size,l_size;

    if(rank==0){
        fprintf(stdout,"Enter Number of Elements :");
        fflush(stdout);
        scanf("%d",&arr_size);
        fprintf(stdout,"Enter Elements :");
        fflush(stdout);

        arr=(int *)malloc(arr_size*sizeof(int));

        for(int i=0;i<arr_size;i++){
            scanf("%d",&arr[i]);
        }

        l_size=arr_size/size;
    }

    MPI_Bcast(&l_size,1,MPI_INT,0,MPI_COMM_WORLD);

    l_arr=(int *)malloc(l_size*sizeof(int));

    MPI_Scatter(arr,l_size,MPI_INT,l_arr,l_size,MPI_INT,0, MPI_COMM_WORLD);

    int even=0;
    int odd=0;

    fprintf(stdout,"Elements in process %d are: ",rank);
    fflush(stdout);
    for(int i=0;i<l_size;i++){
        fprintf(stdout,"%d ",l_arr[i]);
        if(l_arr[i]%2==0){
            even+=1;
            l_arr[i]=1;
        }
        else{
            l_arr[i]=0;
        }
    }
    fprintf(stdout,"\n");
    odd=l_size-1;
    fprintf(stdout,"Number of even elements %d and odd %d elements\n\n",even, odd);

    MPI_Gather(l_arr,l_size,MPI_INT, arr,l_size,MPI_INT,0,MPI_COMM_WORLD);
    int finalEven;
    MPI_Reduce(&even, &finalEven, 1, MPI_INT,MPI_SUM,0, MPI_COMM_WORLD);

    if(rank==0){
        fprintf(stdout,"\nFinal Elements in root process are: ");
        
        for(int i=0;i<arr_size;i++){
            fprintf(stdout,"%d ",arr[i]);
        }
        fprintf(stdout,"\nTotal Even Elements were %d and odd Elements were %d\n",finalEven,arr_size-finalEven);
        fflush(stdout);
        
    }
    MPI_Finalize();
    return 0;
}

// root@807604e088ff:/workspaces/PCAB_LAB/lab3# mpirun-root -np 5 ./output
// Enter Number of Elements :10
// Enter Elements :1 2 3 4 5 6 7 8 9 10
// Elements in process 4 are: 9 10 
// Number of even elements 1 and odd 1 elements

// Elements in process 0 are: 1 2 
// Number of even elements 1 and odd 1 elements


// Final Elements in root process are: 0 1 0 1 0 1 0 1 0 1 
// Total Even Elements were 5 and odd Elements were 5Elements in process 1 are: 3 4 
// Number of even elements 1 and odd 1 elements

// Elements in process 2 are: 5 6 
// Number of even elements 1 and odd 1 elements

// Elements in process 3 are: 7 8 
// Number of even elements 1 and odd 1 elements