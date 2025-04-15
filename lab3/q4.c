#include <stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);

    char *s1, *s2, *l_s1, *l_s2;
    int l_size;
    
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);


    int n;
    char *res,*local_res;

    if(rank==0){
        fprintf(stdout,"Enter Length of string : ");
        fflush(stdout);
        scanf("%d",&n);

        s1=(char * )malloc((n+1)*sizeof(char));
        s2=(char * )malloc((n+1)*sizeof(char));

        fprintf(stdout,"Enter string 1: ");
        fflush(stdout);
        scanf("%s",s1);

        fprintf(stdout,"Enter string 2: ");
        fflush(stdout);
        scanf("%s",s2);

        res=(char * )malloc((2*n+1)*sizeof(char));
        res[2*n]='\0';
    }


    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    int chunksize=n/size;

    l_s1=(char * )malloc((chunksize+1)*sizeof(char));
    l_s2=(char * )malloc((chunksize+1)*sizeof(char));

    local_res=(char * )malloc((2*chunksize)*sizeof(char));

    MPI_Scatter(s1,chunksize,MPI_CHAR, l_s1,chunksize,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(s2,chunksize,MPI_CHAR, l_s2,chunksize,MPI_CHAR,0,MPI_COMM_WORLD);

    for(int i=0;i<chunksize;i++){
        local_res[2*i]=l_s1[i];
        local_res[2*i+1]=l_s2[i];
    }
    local_res[2*chunksize]='\0';
    fprintf(stdout,"String in process %d is :%s\n", rank, local_res);
    fflush(stdout);


    MPI_Gather(local_res,chunksize*2,MPI_CHAR,res,chunksize*2, MPI_CHAR,0,MPI_COMM_WORLD);

    if(rank==0){
        fprintf(stdout,"Final Concatenated string is :%s\n",res);
        fflush(stdout);
    }


    MPI_Finalize();
    return 0;
}

// root@807604e088ff:/workspaces/PCAB_LAB/lab3# mpirun-root -np 3 ./output
// Enter Length of string : 6
// Enter string 1: string
// Enter string 2: length
// String in process 0 is :slte
// Final Concatenated string is :slternigntgh
// String in process 1 is :rnig
// String in process 2 is :ntgh