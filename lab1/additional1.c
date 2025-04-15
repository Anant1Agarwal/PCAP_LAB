#include <stdio.h>
#include <mpi.h>

// reverse digits of an array

int ReverseIt(int n){
    int rev=0;

    while (n>0){
        int ld=n%10;
        rev=rev*10+ld;
        n=n/10;
    }

    return rev;

}

int main(int argc, char** argv){

    MPI_Init(&argc,&argv);

    int nums[9]={18,523,301,1234,2,14,108,150,1928};

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    printf("we are in rank in %d and number is %d\t",rank,nums[rank]);
    nums[rank]=ReverseIt(nums[rank]);
    printf("num is changed to %d \n", nums[rank]);

    fflush(stdout);

    MPI_Finalize();
    return 0;

}