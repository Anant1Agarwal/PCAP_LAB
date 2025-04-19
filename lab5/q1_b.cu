// %%writefile q1_b.cu

#include <stdlib.h>
#include <stdio.h>
#include <cuda.h>

__global__ void vecAddKernel(int *A, int *B, int *C,int n){
    int i=blockDim.x*blockIdx.x+threadIdx.x;

    printf("In Kernel function, i=%d ",i);
    if(i<n){
        C[i]=A[i]+B[i];
    }
}

int main(){
    int n;
    printf("Enter Number of Elements: ");
    scanf("%d",&n);

    int *a,*b,*c;

    a=(int *)malloc(n*sizeof(int));
    b=(int *)malloc(n*sizeof(int));
    c=(int *)malloc(n*sizeof(int));

    printf("\n Enter Array A: ");
    
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
    }

    printf("\n Enter Array B: ");
    
    for(int i=0;i<n;i++){
        scanf("%d", &b[i]);
    }

    int *da, *db, *dc;

    int size=n*sizeof(int);

    //part-1
    cudaMalloc((void **)&da,size);
    cudaMalloc((void **)&db,size);
    cudaMalloc((void **)&dc,size);

    cudaMemcpy(da, a, size,cudaMemcpyHostToDevice);
    cudaMemcpy(db, b, size,cudaMemcpyHostToDevice);

    // 1 block and n threads
    // vecAddKernel<<<1,n>>>(da,db,dc,n);

    //n blocks and 1 thread
    vecAddKernel<<<n,1>>>(da,db,dc,n);

    
    // Error check
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("CUDA error: %s\n", cudaGetErrorString(err));
    }

    // part-3 transfer to C

    cudaMemcpy(c,dc,size,cudaMemcpyDeviceToHost);

    printf("\nFinal Array after adding both is : ");
    
    for(int i=0;i<n;i++){
        printf("%d\t",c[i]);
    }

    free(a);
    free(b);
    free(c);
    cudaFree(da);
    cudaFree(db);
    cudaFree(dc);
}

// / !nvcc q1.cu -o output.out

// / !./output.out
