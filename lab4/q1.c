#include <stdio.h>
#include <mpi.h>

void err_handle(int err_code, int rank){
        if (err_code != MPI_SUCCESS)
        {
            char err_string[1000];
            int length, err_class;
            MPI_Error_class(err_code, &err_class);
            MPI_Error_string(err_code, err_string, &length);
            if (rank > 0)
            {
                fprintf(stderr, "MPI Error for rank: %d\n", rank);
            }
            else{
                fprintf(stderr, "Init method failed\n");
            }
            fprintf(stderr, "MPI Error string: %s\n", err_string);
            fprintf(stderr, "MPI Error class: %d\n", err_class);
            fprintf(stderr, "MPI Error code: %d\n", err_code);
        }
    
    return;
}

int main(int argc, char** argv){
    int err_code;
   err_code= MPI_Init(&argc,&argv);
    err_handle(err_code,-1);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int fact=1;
    int factsum;

      // Set error handler to return instead of abort

      MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    for(int i=1;i<=rank+1;i++){
        fact*=i;
    }
    fprintf(stdout,"factorial in process %d is %d\n",rank, fact);
    fflush(stdout);

    MPI_Comm c = MPI_COMM_NULL;
    // Try to use MPI_Scan with deliberately incorrect parameters to trigger error
    err_code=MPI_Scan(&fact,&factsum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    // err_code = MPI_Scan(&fact, &factsum, 1, MPI_INT, MPI_SUM, c);
    err_handle(err_code,rank);

    if(rank==0){
        fprintf(stdout,"Sum of factorials Final ans : %d\n", factsum);
        fflush(stdout);

    }
    MPI_Finalize();
    return 0;
}