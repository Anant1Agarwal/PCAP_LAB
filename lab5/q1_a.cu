// %%writefile q1_a.cu
#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>

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

    // part-2 blocks and threads
    // int blocks = (n + 255) / 256;
    // vecAddKernel<<<blocks, 256>>>(da, db, dc, n);
    // OR
    // vecAddKernel<<< ceil(n/256.0), 256 >>>(da, db, dc, n);
    // OR 
    // 1 block and n threads
    vecAddKernel<<<1,n>>>(da,db,dc,n);
    
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


// Enter Number of Elements: 4

//  Enter Array A: 3 54 3 3

//  Enter Array B: 2 5 6 2
// In Kernel function, i=192 In Kernel function, i=193 In Kernel function, i=194 In Kernel function, i=195 In Kernel function, i=196 In Kernel function, i=197 In Kernel function, i=198 In Kernel function, i=199 In Kernel function, i=200 In Kernel function, i=201 In Kernel function, i=202 In Kernel function, i=203 In Kernel function, i=204 In Kernel function, i=205 In Kernel function, i=206 In Kernel function, i=207 In Kernel function, i=208 In Kernel function, i=209 In Kernel function, i=210 In Kernel function, i=211 In Kernel function, i=212 In Kernel function, i=213 In Kernel function, i=214 In Kernel function, i=215 In Kernel function, i=216 In Kernel function, i=217 In Kernel function, i=218 In Kernel function, i=219 In Kernel function, i=220 In Kernel function, i=221 In Kernel function, i=222 In Kernel function, i=223 In Kernel function, i=96 In Kernel function, i=97 In Kernel function, i=98 In Kernel function, i=99 In Kernel function, i=100 In Kernel function, i=101 In Kernel function, i=102 In Kernel function, i=103 In Kernel function, i=104 In Kernel function, i=105 In Kernel function, i=106 In Kernel function, i=107 In Kernel function, i=108 In Kernel function, i=109 In Kernel function, i=110 In Kernel function, i=111 In Kernel function, i=112 In Kernel function, i=113 In Kernel function, i=114 In Kernel function, i=115 In Kernel function, i=116 In Kernel function, i=117 In Kernel function, i=118 In Kernel function, i=119 In Kernel function, i=120 In Kernel function, i=121 In Kernel function, i=122 In Kernel function, i=123 In Kernel function, i=124 In Kernel function, i=125 In Kernel function, i=126 In Kernel function, i=127 In Kernel function, i=0 In Kernel function, i=1 In Kernel function, i=2 In Kernel function, i=3 In Kernel function, i=4 In Kernel function, i=5 In Kernel function, i=6 In Kernel function, i=7 In Kernel function, i=8 In Kernel function, i=9 In Kernel function, i=10 In Kernel function, i=11 In Kernel function, i=12 In Kernel function, i=13 In Kernel function, i=14 In Kernel function, i=15 In Kernel function, i=16 In Kernel function, i=17 In Kernel function, i=18 In Kernel function, i=19 In Kernel function, i=20 In Kernel function, i=21 In Kernel function, i=22 In Kernel function, i=23 In Kernel function, i=24 In Kernel function, i=25 In Kernel function, i=26 In Kernel function, i=27 In Kernel function, i=28 In Kernel function, i=29 In Kernel function, i=30 In Kernel function, i=31 In Kernel function, i=224 In Kernel function, i=225 In Kernel function, i=226 In Kernel function, i=227 In Kernel function, i=228 In Kernel function, i=229 In Kernel function, i=230 In Kernel function, i=231 In Kernel function, i=232 In Kernel function, i=233 In Kernel function, i=234 In Kernel function, i=235 In Kernel function, i=236 In Kernel function, i=237 In Kernel function, i=238 In Kernel function, i=239 In Kernel function, i=240 In Kernel function, i=241 In Kernel function, i=242 In Kernel function, i=243 In Kernel function, i=244 In Kernel function, i=245 In Kernel function, i=246 In Kernel function, i=247 In Kernel function, i=248 In Kernel function, i=249 In Kernel function, i=250 In Kernel function, i=251 In Kernel function, i=252 In Kernel function, i=253 In Kernel function, i=254 In Kernel function, i=255 In Kernel function, i=128 In Kernel function, i=129 In Kernel function, i=130 In Kernel function, i=131 In Kernel function, i=132 In Kernel function, i=133 In Kernel function, i=134 In Kernel function, i=135 In Kernel function, i=136 In Kernel function, i=137 In Kernel function, i=138 In Kernel function, i=139 In Kernel function, i=140 In Kernel function, i=141 In Kernel function, i=142 In Kernel function, i=143 In Kernel function, i=144 In Kernel function, i=145 In Kernel function, i=146 In Kernel function, i=147 In Kernel function, i=148 In Kernel function, i=149 In Kernel function, i=150 In Kernel function, i=151 In Kernel function, i=152 In Kernel function, i=153 In Kernel function, i=154 In Kernel function, i=155 In Kernel function, i=156 In Kernel function, i=157 In Kernel function, i=158 In Kernel function, i=159 In Kernel function, i=160 In Kernel function, i=161 In Kernel function, i=162 In Kernel function, i=163 In Kernel function, i=164 In Kernel function, i=165 In Kernel function, i=166 In Kernel function, i=167 In Kernel function, i=168 In Kernel function, i=169 In Kernel function, i=170 In Kernel function, i=171 In Kernel function, i=172 In Kernel function, i=173 In Kernel function, i=174 In Kernel function, i=175 In Kernel function, i=176 In Kernel function, i=177 In Kernel function, i=178 In Kernel function, i=179 In Kernel function, i=180 In Kernel function, i=181 In Kernel function, i=182 In Kernel function, i=183 In Kernel function, i=184 In Kernel function, i=185 In Kernel function, i=186 In Kernel function, i=187 In Kernel function, i=188 In Kernel function, i=189 In Kernel function, i=190 In Kernel function, i=191 In Kernel function, i=32 In Kernel function, i=33 In Kernel function, i=34 In Kernel function, i=35 In Kernel function, i=36 In Kernel function, i=37 In Kernel function, i=38 In Kernel function, i=39 In Kernel function, i=40 In Kernel function, i=41 In Kernel function, i=42 In Kernel function, i=43 In Kernel function, i=44 In Kernel function, i=45 In Kernel function, i=46 In Kernel function, i=47 In Kernel function, i=48 In Kernel function, i=49 In Kernel function, i=50 In Kernel function, i=51 In Kernel function, i=52 In Kernel function, i=53 In Kernel function, i=54 In Kernel function, i=55 In Kernel function, i=56 In Kernel function, i=57 In Kernel function, i=58 In Kernel function, i=59 In Kernel function, i=60 In Kernel function, i=61 In Kernel function, i=62 In Kernel function, i=63 In Kernel function, i=64 In Kernel function, i=65 In Kernel function, i=66 In Kernel function, i=67 In Kernel function, i=68 In Kernel function, i=69 In Kernel function, i=70 In Kernel function, i=71 In Kernel function, i=72 In Kernel function, i=73 In Kernel function, i=74 In Kernel function, i=75 In Kernel function, i=76 In Kernel function, i=77 In Kernel function, i=78 In Kernel function, i=79 In Kernel function, i=80 In Kernel function, i=81 In Kernel function, i=82 In Kernel function, i=83 In Kernel function, i=84 In Kernel function, i=85 In Kernel function, i=86 In Kernel function, i=87 In Kernel function, i=88 In Kernel function, i=89 In Kernel function, i=90 In Kernel function, i=91 In Kernel function, i=92 In Kernel function, i=93 In Kernel function, i=94 In Kernel function, i=95 
// Final Array after adding both is : 5	59	9	5	
