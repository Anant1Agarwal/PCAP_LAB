#include <stdio.h>
#include <mpi.h>
#include<string.h>

// first process sends a word to the second process and second process toggles each word and sends it back to the first proces
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    char str[100];

    //not required as both processes have different local spaces for str, so recv is not required again but i made it again just so we could distinguish the variables.
    char recv[100];
    MPI_Status stat;
    
    if(rank==0){
        fprintf(stdout,"Enter String in the master Process: ");
        fflush(stdout);
        // scanf("%s", str);
        // gets(str);  //does not work
        fgets(str,100, stdin);

        int n=strlen(str)+1; //one added for null value

        // first send the number of chars and then the string
        fprintf(stdout,"\nSending string %s from process 0\n\n", str);
        fflush(stdout);

        MPI_Ssend(&n,1,MPI_INT, 1,999,MPI_COMM_WORLD);
        MPI_Ssend(&str,n,MPI_CHAR,1,888, MPI_COMM_WORLD);

        MPI_Recv(&recv, n, MPI_CHAR,1, 777, MPI_COMM_WORLD, &stat);
        fprintf(stdout,"-------Received toggled string------\n\n");
        fprintf(stdout, "Toggled string is %s\n", recv);
        fflush(stdout);

    }
    else{
        //again not required
        int numrecv;
        char str_recv[100];

        MPI_Recv(&numrecv,1, MPI_INT, 0,999,MPI_COMM_WORLD,&stat);
        MPI_Recv(str_recv,numrecv,MPI_CHAR,0,888,MPI_COMM_WORLD,&stat);

        fprintf(stdout,"string received in process 1\n");
        fprintf(stdout,"----Toggling string----\n");

        for(int i=0;i<numrecv;i++){
            if(str_recv[i]==' '){
                continue;
            }
            if(str_recv[i]>=97){
                str_recv[i]-=32;
            }
            else{
                str_recv[i]+=32;
            }
        }

        fprintf(stdout, "Sending the Toggled string back to process 0\n\n");
        fflush(stdout);
        MPI_Ssend(str_recv,numrecv,MPI_CHAR,0, 777,MPI_COMM_WORLD );

    }

    MPI_Finalize();
    return 0;
}

// Enter String in the master Process: Hello From San FransCisco

// Sending string Hello From San FransCisco
// from process 0

// string received in process 1
// ----Toggling string----
// Sending the Toggled string back to process 0

// -------Received toggled string------

// Toggled string is hELLO fROM sAN fRANScISCO* 