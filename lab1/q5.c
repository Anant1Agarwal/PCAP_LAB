#include <stdio.h>
#include <mpi.h>
#include <string.h>

int factorial(int n){
    if(n==0){
        return 0;
    }
    
    int res=1;
    for (int i=2;i<=n;i++){
        res*=i;
    }
    return res;
}

int fibonacci(int n){
    if(n==1 || n==0){
        return n;
    }
    return fibonacci(n-1)+fibonacci(n-2);
}

// even prints fibonacci, even prints factorial of rank
int main(int argc, char** argv){
    MPI_Init(&argc,&argv);

    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank%2){
        printf("rank is %d, so fibonacci of rank is %d\n",rank, fibonacci(rank));
    }
    else{
        printf("rank is %d, so factorial of rank is %d\n", rank, factorial(rank));
    }

    fflush(stdout);

    MPI_Finalize();
    return 0;
}