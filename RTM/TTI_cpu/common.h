//---------------------- Headers ----------------------
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

//---------------------- MACRO ----------------------
#define MIN(i, j) ((i) < (j) ? (i) : (j))

#define PARALLEL_1D(var, start, end, step) for(int var = start; var < end; var += step) {

#define END_PARALLEL_1D( ) }

#define PARALLEL_2D(varI, varJ, startI, startJ, endI, endJ, stepI, stepJ) for(int varJ = startJ; varJ < endJ; varJ += stepJ) { \
    for(int varI = startI; varI < endI; varI += stepI)  { 

#define END_PARALLEL_2D( ) }}

#define PARALLEL_3D(varI, varJ, varK, startI, startJ, startK, endI, endJ, endK, stepI, stepJ, stepK) for(int varK = startK; varK < endK; varK += stepK) { \
    for(int varJ = startJ; varJ < endJ; varJ += stepJ)  { \
      for(int varI = startI; varI < endI; varI += stepI) {

#define END_PARALLEL_3D( ) }}}

#define ceil(a, b) (((a) + (b) - 1) / (b))
#define min(x, y) ((x) < (y) ? (x) : (y))
#define INDEX(i, j, k, nx, ny) ((i) + (j)*(nx) + (k)*(nx)*(ny))
//---------------------- Defines ----------------------
#define BLOCK_SIZE 8

#define a0 -2.84722222222f
#define a1 1.60f
#define a2 -0.20f
#define a3 0.0253968f
#define a4 -0.00178571428f

#define a10 0.0f
#define a11 0.80f
#define a12 -0.20f
#define a13 0.038095238f
#define a14 -0.00357142857f

#define TOT_TIME 2.0

//---------------------- Structure ----------------------
struct RTMIG_THRD {
    int size;
    int rank;
    int n_threads;
    int i_thread;

    int nPad;
    int nxf;
    int nyf;
    int nz_node;
    int nz_node_last;

    int bx1;
    int bx2;
    int by1;
    int by2;
    int bz1;
    int bz2;

    float Fda_dx;
    float Fda_dy;
    float angle;

    float * v;
    float * delta;
    float * e;
    float * dip_x;
    float * dip_y;

    float * u1;
    float * u2;
    float * u3;
    float * q1;
    float * q2;
    float * q3;

    float * z_fdcoef_1st;
    float * z_fdcoef;

    float * uxx;
    float * uzz;

};

typedef struct BrickInfo{
	int nx;
	int ny;
	int nz;
	int nPad;

	int nbx;
	int nby;
	int nbz;
	int gz_x;
	int gz_y;
	int gz_z;
	int stride_x;
	int stride_y;
	int stride_z;
	int nb;
} BrickInfo;

//---------------------- Templates ----------------------
template<typename T>
double time_func(T func) {
  int it = 1;
  func(); // Warm up
  double st = omp_get_wtime();
  double ed = st;
  while (ed < st + TOT_TIME) {
    for (int i = 0; i < it; ++i)
      func();
    it <<= 1;
    ed = omp_get_wtime();
  }
  return (ed - st) / (it - 1);

}


template<int BX, int BY, int BZ>
void create_brickinfo(BrickInfo* info, int nx, int ny, int nz, int nPad) {
    assert(nx % BX == 0);
    assert(ny % BY == 0);
    assert(nz % BZ == 0);
    info->nx = nx; info->ny = ny; info->nz = nz; info->nPad = nPad;
	info->nbx = nx / BX; info->nby = ny / BY; info->nbz = nz / BZ;
	info->gz_x = ceil(nPad / BX); info->gz_y = ceil(nPad / BY); info->gz_z = ceil(nPad / BZ);
    info->stride_x = info->nbx + 2*info->gz_x;
    info->stride_y = info->nby + 2*info->gz_y;
    info->stride_z = info->nbz + 2*info->gz_z;
    info->nb = info->stride_x*info->stride_y*info->stride_z;
}

template<int BX, int BY, int BZ>
void bricklize(float* dst, float* src, BrickInfo* info, bool extend_z) {
    int offset_x = info->gz_x * BX - info->nPad;
    int offset_y = info->gz_y * BY - info->nPad;
    int offset_z = extend_z ? info->gz_z * BZ - info->nPad : 0;
    int nxf = info->nx + 2*info->nPad;
    int nyf = info->ny + 2*info->nPad;
    int nz = extend_z ? info->nz + 2*info->nPad : info->nz;
    int stride_x = info->stride_x;
    int stride_y = info->stride_y;
    int stride_z = info->stride_z;
    for (size_t k = 0; k < nz; k++) {
        for (size_t j = 0; j < nyf; j++) {
            for (size_t i = 0; i < nxf; i++) {
                size_t x = i + offset_x;
                size_t y = j + offset_y;
                size_t z = k + offset_z;

                size_t brick_idx = INDEX(x/BX, y/BY, z/BZ, stride_x, stride_y)*BX*BY*BZ + INDEX(x%BX, y%BY, z%BZ, BX, BY);
                size_t grid_idx = INDEX(i, j, k, nxf, nyf);
                dst[brick_idx] = src[grid_idx];
            }
        }
    }
}

template<int BX, int BY, int BZ>
void debricklize(float* dst, float* src, BrickInfo* info, bool extend_z) {
    int offset_x = info->gz_x * BX - info->nPad;
    int offset_y = info->gz_y * BY - info->nPad;
    int offset_z = extend_z ? info->gz_z * BZ - info->nPad : 0;
    int nxf = info->nx + 2*info->nPad;
    int nyf = info->ny + 2*info->nPad;
    int nz = extend_z ? info->nz + 2*info->nPad : info->nz;
    int stride_x = info->stride_x;
    int stride_y = info->stride_y;
    int stride_z = info->stride_z;
    for (size_t k = 0; k < nz; k++) {
        for (size_t j = 0; j < nyf; j++) {
            for (size_t i = 0; i < nxf; i++) {
                size_t x = i + offset_x;
                size_t y = j + offset_y;
                size_t z = k + offset_z;
                int brick_idx = INDEX(x/BX, y/BY, z/BZ, stride_x, stride_y)*BX*BY*BZ + INDEX(x%BX, y%BY, z%BZ, BX, BY);
                size_t grid_idx = INDEX(i, j, k, nxf, nyf);
                dst[grid_idx] = src[brick_idx];
				//
				//
				//
            }
        }
    }
}

template<int BX, int BY, int BZ>
void model_bricklize(float* brick_model, float** model, int n_model, BrickInfo* info) {
    int offset_x = info->gz_x * BX - info->nPad;
    int offset_y = info->gz_y * BY - info->nPad;
    int offset_z = 0;
    int nxf = info->nx + 2*info->nPad;
    int nyf = info->ny + 2*info->nPad;
    int nz = info->nz;
    int stride_x = info->stride_x;
    int stride_y = info->stride_y;
    int stride_z = info->stride_z;
    for (int idx = 0; idx < n_model; idx++) {
        for (size_t k = 0; k < nz; k++) {
            for (size_t j = 0; j < nyf; j++) {
                for (size_t i = 0; i < nxf; i++) {
                    size_t x = i + offset_x;
                    size_t y = j + offset_y;
                    size_t z = k + offset_z;
                    size_t brick_idx = INDEX(x/BX, y/BY, z/BZ, stride_x, stride_y)*BX*BY*BZ*n_model +INDEX(x%BX, y%BY, z%BZ + idx*BZ, BX, BY);
                    size_t grid_idx = INDEX(i, j, k, nxf, nyf);
                    brick_model[brick_idx] = model[idx][grid_idx];
                }
            }
        }
    }
}

template<int BX, int BY, int BZ>
void model_debricklize(float** model, float* brick_model, int n_model, BrickInfo* info) {
    int offset_x = info->gz_x * BX - info->nPad;
    int offset_y = info->gz_y * BY - info->nPad;
    int offset_z = 0;
    int nxf = info->nx + 2*info->nPad;
    int nyf = info->ny + 2*info->nPad;
    int nz = info->nz;
    int stride_x = info->stride_x;
    int stride_y = info->stride_y;
    int stride_z = info->stride_z;
    for (int idx = 0; idx < n_model; idx++) {
        for (size_t k = 0; k < nzf; k++) {
            for (size_t j = 0; j < nyf; j++) {
                for (size_t i = 0; i < nxf; i++) {
                    size_t x = i + offset_x;
                    size_t y = j + offset_y;
                    size_t z = k + offset_z;
                    size_t brick_idx = INDEX(x/BX, y/BY, z/BZ, stride_x, stride_y)*BX*BY*BZ*n_model + INDEX(x%BX, y%BY, z%BZ + idx*BZ, BX, BY);
                    size_t grid_idx = INDEX(i, j, k, nxf, nyf);
                    model[idx][grid_idx] = brick_model[brick_idx];
                }
            }
        }
    }
}

//---------------------- Functions ----------------------
void *rtm3_update_3d_tti_pthread(void *Rtmig_thrd0);
void rtm3_initalize(void *Rtmig_thrd0);
void rtm3_finalized(void *Rtmig_thrd0);
#if defined(__ARM_FEATURE_SME)
void rtm3_update_3d_tti_omp(void *Rtmig_thrd0)__arm_streaming;
#else
void rtm3_update_3d_tti_omp(void *Rtmig_thrd0);
#endif

#ifdef USE_MPI
void exchange_halo(void *Rtmig_thrd0);
#endif

