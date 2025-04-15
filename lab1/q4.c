#include <stdio.h>
#include <mpi.h>
#include <string.h>

// toggles characters of a string
int main(int argc, char** argv){

    MPI_Init(&argc,&argv);

    char s[5]="ANant";

    // printf("%d",(int)strlen(s));

    int rank;
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (rank<strlen(s)){
        if(s[rank]>=97){
            s[rank]-=32;   
        }
        else{
            s[rank]+=32;
        }
    }else{
        printf("No change--> index out of bound\n");
    }

    printf("Current rank %d and string is changed to %s\n",rank,s);

    fflush(stdout);

    MPI_Finalize();
    return 0;

}