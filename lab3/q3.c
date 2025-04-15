#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);

    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char *str;
    char *store;

    int str_size;
    int store_size;

    if(rank==0){
        fprintf(stdout, "\nEnter Length of String which is divisible by %d :",size);
        fflush(stdout);

        scanf("%d",&str_size);
        
        if(str_size%size!=0){
            
            fprintf(stdout,"String length cant be evenly distributed!");
            fflush(stdout);
            MPI_Finalize();
            return 0;
        }


        fprintf(stdout,"Enter string: ");
        fflush(stdout);
        str=(char *)malloc(str_size*sizeof(char));
        // fgets(str,1000,stdin);
        scanf("%s",str);
        fprintf(stdout,"len of original string is %d\n",(int)strlen(str));
        fprintf(stdout,"original string: %s\n\n",str);
        fflush(stdout);
        store_size=str_size/size;
    }


    MPI_Bcast(&store_size,1,MPI_INT,0,MPI_COMM_WORLD);
    store=(char *)malloc(store_size*sizeof(char));
    
    MPI_Scatter(str, store_size, MPI_CHAR, store, store_size, MPI_CHAR,0, MPI_COMM_WORLD);

    // int cntNonV=countNONvowels(store);
    int vows=0;
    for(int i=0;i<store_size;i++){
        if(store[i]=='a' ||store[i]=='e' || store[i]=='i' || store[i]=='o' || store[i]=='u' || store[i]=='A' || store[i]=='E' || store[i]=='I' || store[i]=='O' || store[i]=='U'  ){
            vows+=1;
        }
    }
    int cntNonV=store_size-vows;

    fprintf(stdout,"String in process %d is : %s\n",rank, store);
    fprintf(stdout,"Number of Non vowels is %d\n\n",cntNonV);
    fflush(stdout);

    int ans;
    MPI_Reduce(&cntNonV,&ans,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0){
        fprintf(stdout,"\nTotal number of Non vowels in Root Process is %d\n", ans);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}


// Enter Length of String which is divisible by 5 :20
// Enter string: ananthelloaeiouanant 
// len of original string is 20
// original string: ananthelloaeiouanant

// String in process 0 is : anan��
// Number of Non vowels is 2


// Total number of Non vowels in Root Process is 9
// String in process 1 is : thel��
// Number of Non vowels is 3

// String in process 2 is : loae��
// Number of Non vowels is 1

// String in process 3 is : ioua��
// Number of Non vowels is 0

// String in process 4 is : nant��
// Number of Non vowels is 3