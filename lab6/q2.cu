# include <stdio.h>
# include<stdlib.h>
# include <cuda.h>

__global__ void ParallelSelectionSort(int *inp, int *out,int n){ 

    int tid= (blockDim.x*blockIdx.x) + threadIdx.x;

    if(tid<n){
        int data=inp[tid];
        int pos=0;

        for(int i=0;i<n;i++){
            //finding right position for element 
            //2nd conditon is for equaltiy, if that element is meant to be at tid position, it should come at tid position
            if((inp[i]<data) || (inp[i]==data && i<tid)){
                pos+=1;
            }
        }
        out[pos]=data;
    }

}

int main(){
    int *inp, *out;
    int n;
    printf("Enter Number of Elements: ");
    scanf("%d",&n);

    int size=n*sizeof(int);

    inp=(int *)malloc(size);
    out=(int * )malloc(size);
    
    printf("Enter Elements to be sorted: ");
    for(int i=0;i<n;i++){
        scanf("%d",&inp[i]);
    }

    int *din,*dout;

    cudaMalloc((void **)&din, size);
    cudaMalloc((void **)&dout, size)

    cudaMemcpy(din,inp, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dout, out, size, cudaMemcpyHostToDevice);


    dim3 dimGrid(ceil(n/256.0),1,1);
    dim3 dimBlock(256,1,1);
    // call
    ParallelSelectionSort<<<dimGrid,dimBlock>>>(din,dout, n);

    cudaMemcpy(out,dout,size,cudaMemcpyDeviceToHost);
    printf("Final Array after Sorting is :");
    for(int i=0;i<n;i++){
        printf("%d\t",out[i]);
    }

    cudaFree(din);
    cudaFree(dout);

    free(inp);
    free(out);

}
