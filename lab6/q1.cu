
# include <stdio.h>
# include<stdlib.h>
#include <cuda.h>

__global__ void convolution_1D_basic_kernel(int *inp, int *out,int *mask, int mask_width, int width){ 

    int i= blockDim.x* blockIdx.x+threadIdx.x;

    int inp_startPoint=i-(mask_width/2);

    int Conv_value=0;

    for(int j=0;j<mask_width;j++){
        if((inp_startPoint+j>=0) && (inp_startPoint+j)<=width){
            Conv_value+=inp[inp_startPoint+j]*mask[j];
        }
    }   

    out[i]=Conv_value;
}


int main(){
    int *inp, *out,*mask;
    int n;
    int mask_width;
    printf("Enter Number of Elements: ");
    scanf("%d",&n);

    int size=n*sizeof(int);

    inp=(int *)malloc(size);
    out=(int * )malloc(size);
    
    printf("Enter Input Elements: ");
    for(int i=0;i<n;i++){
        scanf("%d",&inp[i]);
    }

    printf("Enter a odd size mask width: ");
    scanf("%d", &mask_width);



    mask=(int*) malloc(mask_width*sizeof(int));

    printf("Enter Mask Elements: ");
    for(int i=0;i<mask_width;i++){
        scanf("%d",&mask[i]);
    }

    int *din,*dout,*dmask;

    cudaMalloc((void **)&din, size);
    cudaMalloc((void **)&dout, size);

    cudaMalloc((void**)&dmask,mask_width*sizeof(int) );

    

    cudaMemcpy(din,inp, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dout, out, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dmask, mask, mask_width*sizeof(int) ,cudaMemcpyHostToDevice);

    // call
    convolution_1D_basic_kernel<<<1, n>>>(din, dout, dmask,mask_width,n);


    cudaMemcpy(out,dout,size,cudaMemcpyDeviceToHost);
    printf("Final Array after convolution is :");
    for(int i=0;i<n;i++){
        printf("%d\t",out[i]);
    }

    cudaFree(din);
    cudaFree(dout);
    cudaFree(dmask);
    free(inp);
    free(out);
    free(mask);

}