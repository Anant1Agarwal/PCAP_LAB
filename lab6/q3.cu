// %%writefile q3.cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void evenPhase(int *arr, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int i;
    if (tid % 2 == 0){
        i = tid;
    }
    else{
        i = tid + 1;
    }

    if (i < n - 1)
    {
        if (arr[i] > arr[i + 1])
        {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

__global__ void oddPhase(int *arr, int n)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int i;
    if (tid % 2 != 0){
        i = tid;
    }
    else{
        i = tid + 1;
    }
    if (i < n - 1)
    {
        if (arr[i] > arr[i + 1])
        {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

void oddEvenSort(int *arr, int n)
{
    int *d_arr;
    cudaMalloc(&d_arr, n * sizeof(int));
    cudaMemcpy(d_arr, arr, n * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    for (int i = 0; i < n; i++)
    {
        evenPhase<<<gridSize, blockSize>>>(d_arr, n);
        cudaDeviceSynchronize();
        oddPhase<<<gridSize, blockSize>>>(d_arr, n);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_arr);
}

int main()
{
    int *inp;
    int n;
    printf("Enter Number of Elements: ");
    scanf("%d",&n);

    int size=n*sizeof(int);

    inp=(int *)malloc(size);
    
    printf("Enter Elements to be sorted: ");
    for(int i=0;i<n;i++){
        scanf("%d",&inp[i]);
    }

    oddEvenSort(inp, n);
    printf("\n");
    printf("Sorted Array is: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", inp[i]);
    }

    return 0;
}