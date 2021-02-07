#pragma once
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef TRY_CUDA
inline void try_cuda(cudaError err, const char* exp, const char* func, int line, const char* file) {
    if (err == cudaSuccess) return;
    fprintf(stderr,
        "%s: %s\n"
        "  in expression %s\n"
        "  at %s:%d in %s\n",
        cudaGetErrorName(err), cudaGetErrorString(err),
        exp,
        func, line, file);
    exit(err);
}

// Prints an error message and exits, if CUDA expression fails.
// TRY_CUDA( cudaDeviceSynchronize() );
#define TRY_CUDA(exp) try_cuda(exp, #exp, __func__, __LINE__, __FILE__)
#endif

#ifndef TRY
// Prints an error message and exits, if CUDA expression fails.
// TRY( cudaDeviceSynchronize() );
#define TRY(exp) TRY_CUDA(exp)
#endif


#ifndef DEFINE_CUDA
// Defines short names for the following variables:
// - threadIdx.x
// - threadIdx.y
// - blockIdx.x
// - blockIdx.y
// - blockDim.x
// - blockDim.y
// - gridDim.x
// - gridDim.y
#define DEFINE_CUDA(tx, ty, bx, by, BX, BY, GX, GY) \
  int tx = threadIdx.x; \
  int ty = threadIdx.y; \
  int bx = blockIdx.x; \
  int by = blockIdx.y; \
  int BX = blockDim.x; \
  int BY = blockDim.y; \
  int GX = gridDim.x;  \
  int GY = gridDim.y;
#endif

#ifndef DEFINE
// Defines short names for the following variables:
// - threadIdx.x
// - threadIdx.y
// - blockIdx.x
// - blockIdx.y
// - blockDim.x
// - blockDim.y
// - gridDim.x
// - gridDim.y
#define DEFINE(tx, ty, bx, by, BX, BY, GX, GY) \
  DEFINE_CUDA(tx, ty, bx, by, BX, BY, GX, GY)
#endif


#ifndef __SYNCTHREADS
void __syncthreads();
#define __SYNCTHREADS() __syncthreads()
#endif

#ifndef __global__
#define __global__
#endif

#ifndef __shared__
#define __shared__
#endif


#ifndef UNUSED
#define UNUSED(e) do { (void)(e); } while (0)
#endif


#ifndef SUM_ARRAY
float sum_array(float* x, int N) {
    float a = 0;
    for (int i = 0; i < N; i++)
        a += x[i];
    return a;
}

// Finds sum of array elements.
// SUM_ARRAY({1, 2, 3}, 2) = 6
#define SUM_ARRAY(x, N) sum_array(x, N)
#endif


#ifndef PRINTVEC
inline void printvec(float *x, int N) {
    printf("{");
    for (int i=0; i<N-1; i++)
        printf("%.1f, ", x[i]);
    if (N>0) printf("%.1f", x[N-1]);
    printf("}");
}

// Prints a vector.
// PRINTVEC(x, 3) = {1, 2, 3}
#define PRINTVEC(x, N) printvec(x, N)
#endif


#ifndef SUM_SQUARES
inline int sum_squares(int x) {
    return x * (x + 1) * (2 * x + 1) / 6;
}

// Computes sum of squares of natural numbers.
// SUM_SQUARES(3) = 1^2 + 2^2 + 3^2 = 14
#define SUM_SQUARES(x) sum_squares(x)
#endif


#ifndef GET2D
// Gets value at given row, column of 2D array
#define GET2D(x, r, c, C) (x)[(r)*(C) + (c)]
#endif


#ifndef CEILDIV
inline int ceildiv(int x, int y) {
    return (x + y - 1) / y;
}

// Computes rounded-up integer division.
// CEILDIV(6, 3) = 2
// CEILDIV(7, 3) = 3
#define CEILDIV(x, y) ceildiv(x, y)
#endif


#ifndef MAX
// Finds maximum value.
// MAX(2, 3) = 3
#define MAX(x, y) ((x) > (y)? (x) : (y))
#endif

#ifndef MIN
// Finds minimum value.
// MIN(2, 3) = 2
#define MIN(x, y) ((x) < (y)? (x) : (y))
#endif


#ifndef UINT
typedef unsigned int uint;
#define UINT uint
#endif

#ifndef UINT8
typedef unsigned char uint8;
#define UINT8 uint8
#endif


#ifndef PRINT2D
inline void print2d(float *x, int R, int C) {
  printf("{\n");
  for (int r=0; r<R; r++) {
    for (int c=0; c<C; c++)
      printf("%.1f, ", GET2D(x, r, c, C));
    printf("\n");
  }
  printf("}\n");
}

// Prints a 2d-array.
// PRINT2D(x, 4, 4)
#define PRINT2D(x, R, C) \
  print2d(x, R, C)
#endif
