#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void octal(int *arr, int *ans, int n){
    int i = (blockDim.x * blockIdx.x) + threadIdx.x;
    if(i < n){
        ans[i] = 0;
        while(arr[i] > 0){
            ans[i] = (arr[i] % 8) + (10 * ans[i]);
            arr[i] /= 8;
        }
        int val = 0;
        while(ans[i] > 0){
            val = (10 * val) + (ans[i] % 10);
            ans[i] /= 10;
        }
        ans[i] = val;
    }
}
__global__ void octal2(int *arr, int *ans, int n) {
    int i = (blockDim.x * blockIdx.x) + threadIdx.x;
    if (i < n) {
        int num = arr[i];
        char temp[16];  // store up to 16 octal digits
        int idx = 0;

        // Handle 0 explicitly
        if (num == 0) {
            temp[idx++] = '0';
        }

        // Convert to octal (in reverse)
        while (num > 0) {
            // 0 is converted to ascii, and is add to num%8 and then total ascii is converted to string
            temp[idx++] = (num % 8) + '0';  // char digit
            num /= 8;
        }

        // Convert reversed char array to correct integer
        int result = 0;
        for (int j = idx - 1; j >= 0; --j) {
            result = result * 10 + (temp[j] - '0');
        }

        ans[i] = result;
    }
}
// example of binary --> similar with octal
// 11          ans[i]=1101----->ans[i]=1011
// 11%2 11/2=5  -->1
// 5%2 5/2=2   -->1
// 2%2 2/2=1   -->0       
// 1%2 1/2=0   -->1

// 1011

int main(int argc, char **argv){
    int *arr, *ans, n;
    printf("enter size of array\n");
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    ans = (int *)malloc(sizeof(int) * n);
    printf("enter array\n");
    for(int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }
    int *darr, *dans;
    cudaMalloc((void **)&darr, n * sizeof(int));
    cudaMalloc((void **)&dans, n * sizeof(int));
    cudaMemcpy(darr, arr, n * sizeof(int), cudaMemcpyHostToDevice);
    octal2<<<1, n>>>(darr, dans, n);
    cudaMemcpy(ans, dans, n * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(dans);
    cudaFree(darr);

    printf("Octal Values of given array is :\t");
    for(int i = 0; i < n; ++i){
        printf("%d\t", ans[i]);
    }
    return 0;
}