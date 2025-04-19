// %%writefile add_q1.cu
#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>

__global__ void calculateY(double* x, double*y,int m, int c, int n){

    int i=blockDim.x*blockIdx.x+threadIdx.x;

    if(i<n){
       y[i]=m*x[i]+c;
    }
}

int main(){
    int n;
    printf("Enter Number of Elements: ");
    scanf("%d",&n);

    double *x,*y;
    int m, c;


    x=(double *)malloc(n*sizeof(double));
    y=(double *)malloc(n*sizeof(double));

    printf("\n Enter Array X: ");
    
    for(int i=0;i<n;i++){
        scanf("%lf", &x[i]);
    }
    printf("Enter Slope and intercept: ");
    scanf("%d %d", &m, &c)

    double *dy,*dx;
   
    int size=n*sizeof(double);

    cudaMalloc((void **)&dy,size);
    cudaMalloc((void**)&dx,size);
  
    cudaMemcpy(dy, y, size,cudaMemcpyHostToDevice);
    cudaMemcpy(dx, x, size,cudaMemcpyHostToDevice);

    calculateY<<<1,n>>>(dx,dy,m,c,n);

    cudaMemcpy(y,dy,size,cudaMemcpyDeviceToHost);

    printf("\nFinal Array Y=mx+c i.e Y=(%d)*(x)+%d is : ",m,c);
    
    for(int i=0;i<n;i++){
        printf("%d\t",y[i]);
    }

    free(x);
    free(y);
 
    cudaFree(dx);
    cudaFree(dy)

}