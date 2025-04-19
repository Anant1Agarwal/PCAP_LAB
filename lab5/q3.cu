// %%writefile q3.cu
#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>

__global__ void ConvertToSines(double* a,int n){
    int i=blockDim.x*blockIdx.x+threadIdx.x;

    if(i<n){
       a[i]=sin(a[i]);
    }
}

int main(){
    double*a, *da;
    int n; 
    printf("Enter Number of Elements :");
    scanf("%d",&n);

    int size=n*sizeof(double);
    a=(double*)malloc(size);

    printf("Enter Elements: ");
    for(int i=0;i<n;i++){
        scanf("%lf",&a[i]);
    }

    cudaMalloc((void**)&da,size);
    cudaMemcpy(da,a, size, cudaMemcpyHostToDevice);

    ConvertToSines<<<1,n>>>(da,n);

    cudaMemcpy(a,da,size,cudaMemcpyDeviceToHost);

    printf("\nSines of Elements are: ");
    for(int i=0;i<n;i++){
        printf("%lf\t",a[i]);
    }

    cudaFree(da);
    free(a);
}