#include "common.h"
#include <arm_sve.h>
#include <sched.h>
#if defined(__ARM_FEATURE_SME)
#include <arm_sme.h>
#define SME_ON() \
    __asm__ volatile( \
        "msr    SVCRSMZA, #1\n" \
        "isb\n" \
        : \
        : \
        :"memory" \
    );

#define SME_OFF() \
    __asm__ volatile( \
        "msr    SVCRSMZA, #0\n" \
        "isb\n" \
        : \
        : \
        :"memory" \
    );
#endif

typedef struct LocalVar{
    float* c[3];
    float* l[3];
    float* r[3];
}LocalVar;

typedef struct Grid{
    float* u1;
    float* u2;
    float* u3;
    float* q1;
    float* q2;
    float* q3;
    float* model;
    float* z_fdcoef_1st;
    float* z_fdcoef;
    LocalVar* local_uz;
    LocalVar* local_qz;
}Grid;

#define TileX 256
#define TileY 16
#define TileZ 64
#define RADIUS 4
#define VX 16
#define VY 16
#define VZ 4
#define BX 16
#define BY 4
#define BZ 4
const char * func_name = "bricklized rtm on 920f using SME, fine grained";
BrickInfo info;
Grid grid;

void z_fdcoef_reorder(float* z_fdcoef_out, float* z_fdcoef_in, int nz) {
    for(int bk = 0; bk < nz; bk += BZ) {
        float* coef_in_loc = z_fdcoef_in + bk*(1 + 2*RADIUS);
        float* coef_out_loc = z_fdcoef_out + (bk / BZ)*(BX + 2*RADIUS)*BX;
        for(int iz = 0; iz < BZ; iz++) {
            for(int ix = 0; ix < (1 + 2*RADIUS); ix++) {
                coef_out_loc[(iz + ix)*BX + iz] = coef_in_loc[iz*(1 + 2*RADIUS) + ix];
            }
        }
    }
}


constexpr size_t PZ_SIZE = 4 * BX * BY * BZ + 2 * VX * VY * VZ;
constexpr size_t PY_SIZE = 3 * VX * VY * VZ;
constexpr size_t PZT_SIZE = 3 * VX * VY * VZ;
constexpr size_t PT_SIZE = 3 * VX * VY * VZ;
constexpr size_t VECTOR_SIZE = VX * VY * VZ;
constexpr size_t BRICK_SIZE = BX * BY * BZ;
constexpr size_t BUF_SIZE = PZ_SIZE + PY_SIZE + PZT_SIZE + PT_SIZE + 6 * VECTOR_SIZE;
void rtm3_initalize(void* Rtmig_thrd0) {
    struct RTMIG_THRD* Rtmig_thrd = (struct RTMIG_THRD*)Rtmig_thrd0;
    const int rank = Rtmig_thrd->rank;
    const int size = Rtmig_thrd->size;
    const int nxf = Rtmig_thrd->nxf;
    const int nyf = Rtmig_thrd->nyf;
    const int nPad = Rtmig_thrd->nPad;
    const int nx = nxf - 2 * nPad;
    const int ny = nyf - 2 * nPad;
    const int nz = (rank == size - 1) ? Rtmig_thrd->nz_node_last : Rtmig_thrd->nz_node;
    //initalize brick info
    create_brickinfo<BX, BY, BZ>(&info, nx, ny, nz, nPad);
    //alloc grid
    grid.u1 = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb);
    grid.u2 = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb);
    grid.u3 = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb);
    grid.q1 = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb);
    grid.q2 = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb);
    grid.q3 = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb);
    grid.model = (float*)aligned_alloc(64, sizeof(float) * BX * BY * BZ * info.nb*5);
    grid.z_fdcoef_1st = (float*)aligned_alloc(64, sizeof(float) * info.nbz * (BX + 2 * RADIUS) * BX);
    grid.z_fdcoef = (float*)aligned_alloc(64, sizeof(float) * info.nbz * (BX + 2 * RADIUS) * BX);
    //zero grid
    memset(grid.u1, 0, sizeof(float) * BX * BY * BZ * info.nb);
    memset(grid.u2, 0, sizeof(float) * BX * BY * BZ * info.nb);
    memset(grid.u3, 0, sizeof(float) * BX * BY * BZ * info.nb);
    memset(grid.q1, 0, sizeof(float) * BX * BY * BZ * info.nb);
    memset(grid.q2, 0, sizeof(float) * BX * BY * BZ * info.nb);
    memset(grid.q3, 0, sizeof(float) * BX * BY * BZ * info.nb);
    memset(grid.model, 0, sizeof(float) * BX * BY * BZ * info.nb*5);
    memset(grid.z_fdcoef_1st, 0, sizeof(float) * info.nbz * (BX + 2 * RADIUS) * BX);
    memset(grid.z_fdcoef, 0, sizeof(float) * info.nbz * (BX + 2 * RADIUS) * BX);
    //bricklize
    bricklize<BX, BY, BZ>(grid.u1, Rtmig_thrd->u1, &info, true);
    bricklize<BX, BY, BZ>(grid.u2, Rtmig_thrd->u2, &info, true);
    bricklize<BX, BY, BZ>(grid.q1, Rtmig_thrd->q1, &info, true);
    bricklize<BX, BY, BZ>(grid.q2, Rtmig_thrd->q2, &info, true);
    float* model_ptrs[] = {Rtmig_thrd->v, Rtmig_thrd->delta, Rtmig_thrd->e, Rtmig_thrd->dip_x, Rtmig_thrd->dip_y};
    model_bricklize<BX, BY, BZ>(grid.model, model_ptrs, 5, &info);
    z_fdcoef_reorder(grid.z_fdcoef_1st, Rtmig_thrd->z_fdcoef_1st, nz);
    z_fdcoef_reorder(grid.z_fdcoef, Rtmig_thrd->z_fdcoef, nz);
    //alloc aux grid
    assert(BY >= nPad);
    assert(BX >= nPad);
    int max_num_threads = omp_get_max_threads();
    Rtmig_thrd->uxx = (float*)aligned_alloc(64, sizeof(float) * BUF_SIZE * max_num_threads);
    Rtmig_thrd->uzz = (float*)aligned_alloc(64, sizeof(float) * BUF_SIZE * max_num_threads);
    grid.local_uz = (LocalVar*)malloc(sizeof(LocalVar) * max_num_threads);
    grid.local_qz = (LocalVar*)malloc(sizeof(LocalVar) * max_num_threads);
    for (int tid = 0; tid < max_num_threads; tid++) {
        for (int i = 0; i < 2; i++) {
            grid.local_uz[tid].c[i] = Rtmig_thrd->uxx + BUF_SIZE * tid + i * VECTOR_SIZE;
            grid.local_uz[tid].l[i] = Rtmig_thrd->uxx + BUF_SIZE * tid + 2 * VECTOR_SIZE + i * BRICK_SIZE;
            grid.local_uz[tid].r[i] = Rtmig_thrd->uxx + BUF_SIZE * tid + 2 * VECTOR_SIZE + 2 * BRICK_SIZE + i * BRICK_SIZE;
            
            grid.local_qz[tid].c[i] = Rtmig_thrd->uzz + BUF_SIZE * tid + i * VECTOR_SIZE;
            grid.local_qz[tid].l[i] = Rtmig_thrd->uzz + BUF_SIZE * tid + 2 * VECTOR_SIZE + i * BRICK_SIZE;
            grid.local_qz[tid].r[i] = Rtmig_thrd->uzz + BUF_SIZE * tid + 2 * VECTOR_SIZE + 2 * BRICK_SIZE + i * BRICK_SIZE;
        }
    }
}

void rtm3_finalized(void* Rtmig_thrd0) {
    struct RTMIG_THRD* Rtmig_thrd = (struct RTMIG_THRD *)Rtmig_thrd0;
    debricklize<BX, BY, BZ>(Rtmig_thrd->u3, grid.u3, &info, true);
    debricklize<BX, BY, BZ>(Rtmig_thrd->q3, grid.q3, &info, true);
    free(grid.u1);
    free(grid.u2);
    free(grid.u3);
    free(grid.q1);
    free(grid.q2);
    free(grid.q3);
    free(grid.model);
    free(grid.local_uz);
    free(grid.local_qz);
}


#ifdef USE_MPI
#include <mpi.h>
void exchange_halo(void* Rtmig_thrd0) {
    struct RTMIG_THRD* Rtmig_thrd = (struct RTMIG_THRD *)Rtmig_thrd0;
    const int rank = Rtmig_thrd->rank;
    const int comm_size = Rtmig_thrd->size;
    const int stride_x = info.stride_x;
    const int stride_y = info.stride_y;
    const int stride_z = info.stride_z;
    const int nbz = info.nbz;
    const int gz_z = info.gz_z;

    float* u2 = grid.u2;
    float* q2 = grid.q2;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Status status;
    int neighbors[2];
    neighbors[0] = rank == 0 ? MPI_PROC_NULL : rank - 1;
    neighbors[1] = rank == comm_size - 1 ? MPI_PROC_NULL : rank + 1;
    MPI_Sendrecv(u2 + (size_t)stride_x*stride_y*gz_z*BRICK_SIZE, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[0], 0,
                 u2 + (size_t)(gz_z + nbz)*stride_x*stride_y*BRICK_SIZE, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[1], 0, MPI_COMM_WORLD, &status);
    MPI_Sendrecv(q2 + (size_t)stride_x*stride_y*gz_z*BRICK_SIZE, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[0], 1,
                 q2 + (size_t)(gz_z + nbz)*stride_x*stride_y*BRICK_SIZE, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[1], 1, MPI_COMM_WORLD, &status);
    MPI_Sendrecv(u2 + (size_t)stride_x*stride_y*nbz*BRICK_SIZE, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[1], 2,
                 u2, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[0], 2, MPI_COMM_WORLD, &status);
    MPI_Sendrecv(q2 + (size_t)stride_x*stride_y*nbz*BRICK_SIZE, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[1], 3,
                 q2, stride_x*stride_y*gz_z*BRICK_SIZE, MPI_FLOAT, neighbors[0], 3, MPI_COMM_WORLD, &status);
}
#endif

void brick_transpose(float* p0, float* p1, int sy, int dy)__arm_streaming;
void stencil_x_step_BrickBrick_16164_radius4(float *ptr_m1, float *ptr_0, float *ptr_1, float *ptr_dst, int ker_size_x, int vec_size_y, int vec_size_z, int sy, int sz, int dy, int dz, float *xc)__arm_streaming;
void stencil_y_step_BrickBrick_16164_radius4(float *ptr_m1, float *ptr_0, float *ptr_1, float *ptr_dst, int ker_size_x, int vec_size_y, int vec_size_z, int sy, int sz, int dy, int dz, float *yc)__arm_streaming;
void stencil_z_step_BrickBrick_1644_radius4(float *ptr_src, float *ptr_dst, int ker_size_x, int vec_size_y, int vec_size_z, int sy, int sz, int dy, int dz, float *zc)__arm_streaming;

#define PREVIOUS(i, N) (((i) + ((N)-1))%(N))
#define NEXT(i, N) (((i) + 1)%(N))
#define CURRENT(i, N) ((i)%(N))
void rtm3_update_3d_tti_omp(void* Rtmig_thrd0)__arm_streaming
{
    SME_ON()
    struct RTMIG_THRD* Rtmig_thrd = (struct RTMIG_THRD *) Rtmig_thrd0;
    int nbx = info.nbx;
    int nby = info.nby;
    int nbz = info.nbz;
    int nPad = info.nPad;
    int gz_x = info.gz_x;
    int gz_y = info.gz_y;
    int gz_z = info.gz_z;
    int stride_x = info.stride_x;
    int stride_y = info.stride_y;
    int stride_z = info.stride_z;

    const int stncilsiz = 9;
    const float* __restrict__ ZC1 = grid.z_fdcoef_1st;
    const float* __restrict__ ZC2 = grid.z_fdcoef;

    const float dx = Rtmig_thrd->Fda_dx;
    const float b2 = cos(Rtmig_thrd->angle * M_PI / 180.0);

    const float sigma = 0.66667f;

    const float dy1i = 1.0f / Rtmig_thrd->Fda_dy;
    const float dx1i = 1.0f / Rtmig_thrd->Fda_dx;
    const float dy2i = dy1i * dy1i;
    const float dx2i = dx1i * dx1i;

    const float yc1[] = {
        0,
        a11 * dy1i,
        a12 * dy1i,
        a13 * dy1i,
        a14 * dy1i
    };

    const float xc1[] = {
        0,
        a11 * dx1i,
        a12 * dx1i,
        a13 * dx1i,
        a14 * dx1i
    };

    const float yc2[] = {
        a0 * dy2i,
        a1 * dy2i,
        a2 * dy2i,
        a3 * dy2i,
        a4 * dy2i
    };

    const float xc2[] = {
        a0 * dx2i,
        a1 * dx2i,
        a2 * dx2i,
        a3 * dx2i,
        a4 * dx2i
    };

    const float yc1_kernel[] = { -yc1[4], -yc1[3], -yc1[2], -yc1[1], 0, yc1[1], yc1[2], yc1[3], yc1[4] };
    const float xc1_kernel[] = { -xc1[4], -xc1[3], -xc1[2], -xc1[1], 0, xc1[1], xc1[2], xc1[3], xc1[4] };
    const float yc2_kernel[] = { yc2[4], yc2[3], yc2[2], yc2[1], yc2[0], yc2[1], yc2[2], yc2[3], yc2[4] };
    const float xc2_kernel[] = { xc2[4], xc2[3], xc2[2], xc2[1], xc2[0], xc2[1], xc2[2], xc2[3], xc2[4] };

    typedef float (*BrickArr)[stride_y][stride_x][BRICK_SIZE];
    typedef float (*BrickModel)[stride_y][stride_x][5][BRICK_SIZE];
    const BrickModel Model = (BrickModel)grid.model;

    const BrickArr U1 = (BrickArr)grid.u1;
    const BrickArr U2 = (BrickArr)grid.u2;
    BrickArr U3 = (BrickArr)grid.u3;

    const BrickArr Q1 = (BrickArr)grid.q1;
    const BrickArr Q2 = (BrickArr)grid.q2;
    BrickArr Q3 = (BrickArr)grid.q3;


    int bx1 = gz_x;     int bx2 = gz_x + nbx;
    int by1 = gz_y;     int by2 = gz_y + nby;
    int bz1 = gz_z;     int bz2 = gz_z + nbz;
    #pragma omp parallel for collapse(3) schedule(static, 1)
    PARALLEL_3D(ti, tj, tk, bx1, by1, bz1, bx2, by2, bz2, TileX / BX, TileY / BY, TileZ / BZ)
        int tile_size_x = MIN(TileX / BX, bx2 - ti);
        int tile_size_y = MIN(TileY / BY, by2 - tj);
        int tile_size_z = MIN(TileZ / BZ, bz2 - tk);
        int thread_id = omp_get_thread_num();
        float* uz_buf = Rtmig_thrd->uxx + thread_id*BUF_SIZE;
        float* qz_buf = Rtmig_thrd->uzz + thread_id*BUF_SIZE;
        LocalVar uz = grid.local_uz[thread_id];
        LocalVar qz = grid.local_qz[thread_id];
        float* uy_buf = uz_buf + PZ_SIZE;
        float* qy_buf = qz_buf + PZ_SIZE;
        float (* __restrict__ uy)[VECTOR_SIZE] = (float (*)[VECTOR_SIZE])(uy_buf);
        float (* __restrict__ qy)[VECTOR_SIZE] = (float (*)[VECTOR_SIZE])(qy_buf);
        float* uzt_buf = uy_buf + PY_SIZE;
        float* qzt_buf = qy_buf + PY_SIZE;
        float (* __restrict__ uzt)[VECTOR_SIZE] = (float (*)[VECTOR_SIZE])(uzt_buf);
        float (* __restrict__ qzt)[VECTOR_SIZE] = (float (*)[VECTOR_SIZE])(qzt_buf);
        float* ut_buf = uzt_buf + PZT_SIZE;
        float* qt_buf = qzt_buf + PZT_SIZE;
        float (* __restrict__ ut)[VECTOR_SIZE] = (float (*)[VECTOR_SIZE])(ut_buf);
        float (* __restrict__ qt)[VECTOR_SIZE] = (float (*)[VECTOR_SIZE])(qt_buf);
        float* ud_buf = ut_buf + PT_SIZE;
        float* qd_buf = qt_buf + PT_SIZE;
        float *uzy = ud_buf + 0*VECTOR_SIZE;
        float *uzx = ud_buf + 1*VECTOR_SIZE;
        float *uyx = ud_buf + 2*VECTOR_SIZE;
        float *ux2 = ud_buf + 3*VECTOR_SIZE;
        float *uy2 = ud_buf + 4*VECTOR_SIZE;
        float *uz2 = ud_buf + 5*VECTOR_SIZE;

        float *qzy = qd_buf + 0*VECTOR_SIZE;
        float *qzx = qd_buf + 1*VECTOR_SIZE;
        float *qyx = qd_buf + 2*VECTOR_SIZE;
        float *qx2 = qd_buf + 3*VECTOR_SIZE;
        float *qy2 = qd_buf + 4*VECTOR_SIZE;
        float *qz2 = qd_buf + 5*VECTOR_SIZE;

        PARALLEL_2D(k, j, tk, tj, tk + tile_size_z, tj + tile_size_y, VZ / BZ, VY / BY)
            const BrickModel model = (BrickModel)&Model[k-bz1][j][ti];

            const BrickArr u1 = (BrickArr)&U1[k][j][ti];
            const BrickArr u2 = (BrickArr)&U2[k][j][ti];
            BrickArr u3 = (BrickArr)&U3[k][j][ti];

            const BrickArr q1 = (BrickArr)&Q1[k][j][ti];
            const BrickArr q2 = (BrickArr)&Q2[k][j][ti];
            BrickArr q3 = (BrickArr)&Q3[k][j][ti];

            const float* __restrict__ zc2 = ZC2 + (k - gz_z) * (BX + 2 * RADIUS) * BX;
            const float* __restrict__ zc1 = ZC1 + (k - gz_z) * (BX + 2 * RADIUS) * BX;

            //start up, compute py and pz
            for (int iuq = 0; iuq < 2; ++iuq) {
                const auto p2 = (iuq == 0) ? u2 : q2;
                auto pz = (iuq == 0) ? uz : qz;
                auto pzt = (iuq == 0) ? uzt : qzt;
                auto py = (iuq == 0) ? uy : qy;
                auto pt = (iuq == 0) ? ut : qt;

                PARALLEL_1D(vi, -1, 1, 1)

                    //compute pz_l
                    stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][-1][vi][0]), pz.l[CURRENT(vi + 2, 2)],
                                                    VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc1));
                    for (int iy = 0; iy < VY / BY; iy += 1)
                        stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][iy][vi][0]), &pz.c[CURRENT(vi + 2, 2)][iy * BRICK_SIZE],
                                                    VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc1));
                    //and transpose pz to pz_t
                    brick_transpose(pz.c[CURRENT(vi + 2, 2)], &pzt[CURRENT(vi + 3, 3)][0], BRICK_SIZE, BRICK_SIZE);
                    //compute pz_r
                    stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][VY / BY][vi][0]), pz.r[CURRENT(vi + 2, 2)],
                                                    VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc1));

                    //compute py
                    stencil_y_step_BrickBrick_16164_radius4(const_cast<float*>(&p2[0][-1][vi][0]), const_cast<float*>(&p2[0][0][vi][0]), const_cast<float*>(&p2[0][VY / BY][vi][0]), &py[CURRENT(vi + 3, 3)][0],
                                                        VX, VY, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(yc1_kernel));
                    // directly transpose py
                    brick_transpose(&py[CURRENT(vi + 3, 3)][0], &py[CURRENT(vi + 3, 3)][0], BRICK_SIZE, BRICK_SIZE);
                    brick_transpose(&p2[0][0][vi][0], &pt[CURRENT(vi + 3, 3)][0], stride_x*BRICK_SIZE, BRICK_SIZE);
                END_PARALLEL_1D()

            }

            for (int vi = 0; vi < tile_size_x; vi++) {
                for (int iuq = 0; iuq < 2; ++iuq) {
                    const auto p2 = (iuq == 0) ? u2 : q2;
                    auto pz = (iuq == 0) ? uz : qz;
                    auto pzt = (iuq == 0) ? uzt : qzt;
                    auto py = (iuq == 0) ? uy : qy;
                    auto pt = (iuq == 0) ? ut : qt;
                    auto pzy = (iuq == 0) ? uzy : qzy;
                    auto pzx = (iuq == 0) ? uzx : qzx;
                    auto pyx = (iuq == 0) ? uyx : qyx;
                    auto px2 = (iuq == 0) ? ux2 : qx2;
                    auto py2 = (iuq == 0) ? uy2 : qy2;
                    auto pz2 = (iuq == 0) ? uz2 : qz2;

                    //compute pz in advance
                        //compute pz_l
                    stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][-1][vi + 1][0]), pz.l[NEXT(vi, 2)], 
                                                        VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc1));
                    for (int iy = 0; iy < VX / BY; iy += 1)
                        stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][iy][vi + 1][0]), &pz.c[NEXT(vi, 2)][iy*BRICK_SIZE],
                                                        VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc1));
                        //and transpose pz to pz_t
                    brick_transpose(pz.c[NEXT(vi, 2)], &pzt[NEXT(vi, 3)][0], BRICK_SIZE, BRICK_SIZE);
                    stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][VY / BY][vi + 1][0]), pz.r[NEXT(vi, 2)],
                                                        VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc1));
                    
                    //compute pzx and pzy
                    stencil_x_step_BrickBrick_16164_radius4(&pzt[PREVIOUS(vi, 3)][3*BRICK_SIZE], &pzt[CURRENT(vi, 3)][0], &pzt[NEXT(vi, 3)][0], pzx,
                                                            VX, VY, VZ, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(xc1_kernel));

                    stencil_y_step_BrickBrick_16164_radius4(pz.l[CURRENT(vi, 2)], pz.c[CURRENT(vi, 2)], pz.r[CURRENT(vi, 2)], pzy,
                                                            VX, VY, VZ, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(yc1_kernel));
                    
                    //
                    //
                    //
                    //
                    //
                    //
                    //
                    //
                    //compute py in advance
                    stencil_y_step_BrickBrick_16164_radius4(const_cast<float*>(&p2[0][-1][vi + 1][0]), const_cast<float*>(&p2[0][0][vi + 1][0]), const_cast<float*>(&p2[0][VY / BY][vi + 1][0]), &py[NEXT(vi, 3)][0],
                                                        VX, VY, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(yc1_kernel));
                    
                                                        //
                    //
                    //
                    //
                    //
                    //
                    //
                    //                    
                    //
                    //
                    //
                    //
                    //
                    //
                    //directly transpose py
                    brick_transpose(&py[NEXT(vi, 3)][0], &py[NEXT(vi, 3)][0], BRICK_SIZE, BRICK_SIZE);
                    //
                    //
                    //
                    //compute pyx
                    stencil_x_step_BrickBrick_16164_radius4(&py[PREVIOUS(vi, 3)][3*BRICK_SIZE], &py[CURRENT(vi, 3)][0], &py[NEXT(vi, 3)][0], pyx,
                                                            VX, VY, VZ, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(xc1_kernel));

                    //
                    //
                    //

                    //compute px2, py2, pz2
                    //transpose p2 at first
                    brick_transpose(&p2[0][0][vi + 1][0], &pt[NEXT(vi, 3)][0], stride_x*BRICK_SIZE, BRICK_SIZE);

                    stencil_x_step_BrickBrick_16164_radius4(&pt[PREVIOUS(vi, 3)][3*BRICK_SIZE], &pt[CURRENT(vi, 3)][0], &pt[NEXT(vi, 3)][0], px2,
                                                            VX, VY, VZ, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(xc2_kernel));

                    stencil_y_step_BrickBrick_16164_radius4(const_cast<float*>(&p2[0][-1][vi][0]), const_cast<float*>(&p2[0][0][vi][0]), const_cast<float*>(&p2[0][VY / BY][vi][0]), py2,
                                                            VX, VY, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(yc2_kernel));

                    for(int iy = 0; iy < VY / BY; iy += 1)
                        stencil_z_step_BrickBrick_1644_radius4(const_cast<float*>(&p2[0][iy][vi][0]), &pz2[iy*BRICK_SIZE],
                                                        VX, RADIUS, VZ, stride_x*BRICK_SIZE, stride_x*stride_y*BRICK_SIZE, BRICK_SIZE, BRICK_SIZE, const_cast<float*>(zc2));
                    
                }
                PARALLEL_1D(iy, 0, VY / BY, 1)
                float* v = &model[0][iy][vi][0][0];
                float* d = &model[0][iy][vi][1][0];
                float* e = &model[0][iy][vi][2][0];
                float* xd = &model[0][iy][vi][3][0];
                float* yd = &model[0][iy][vi][4][0];
#pragma ivdep
#pragma vector nontemporal (u3, q3)
                    PARALLEL_1D(b, 0, BRICK_SIZE, 1)
                        const float xdip = xd[b];
                        const float ydip = yd[b];
                        const float xdip2 = xdip * xdip;
                        const float ydip2 = ydip * ydip;
                        const float xdip_2 = -2.0f * xdip;
                        const float ydip_2 = -2.0f * ydip;
                        const float xydip_2 = 2.0f * xdip * ydip;
                        const float xydip_i = 1.0f / (1.0f + xdip2 + ydip2);

                        float h1u = (ux2[iy*BRICK_SIZE + b] * xdip2 + uy2[iy*BRICK_SIZE + b] * ydip2 + uz2[iy*BRICK_SIZE + b]
                                        + uyx[iy*BRICK_SIZE + b] * xydip_2 + uzy[iy*BRICK_SIZE + b] * ydip_2 + uzx[iy*BRICK_SIZE + b] * xdip_2) * xydip_i;
                        float h2u = ux2[iy*BRICK_SIZE + b] + uy2[iy*BRICK_SIZE + b] + uz2[iy*BRICK_SIZE + b] - h1u;

                        float h1q = (qx2[iy*BRICK_SIZE + b] * xdip2 + qy2[iy*BRICK_SIZE + b] * ydip2 + qz2[iy*BRICK_SIZE + b]
                                        + qyx[iy*BRICK_SIZE + b] * xydip_2 + qzy[iy*BRICK_SIZE + b] * ydip_2 + qzx[iy*BRICK_SIZE + b] * xdip_2) * xydip_i;
                        float h2q = qx2[iy*BRICK_SIZE + b] + qy2[iy*BRICK_SIZE + b] + qz2[iy*BRICK_SIZE + b] - h1q;

                        const float iv = v[b];
                        const float ie = e[b];
                        const float id = d[b];

                        float isigma = sigma * (ie - id);
                        u3[0][iy][vi][b] = u2[0][iy][vi][b] + u2[0][iy][vi][b] - u1[0][iy][vi][b] + iv * (ie * h2u + h1q + isigma * (h1u - h1q));
                        q3[0][iy][vi][b] = q2[0][iy][vi][b] + q2[0][iy][vi][b] - q1[0][iy][vi][b] + iv * (id * h2u + h1q + isigma * (h2q - h2u));
                        //
                        //
                        //
                        //
                        //
                        //
                        //
                    END_PARALLEL_1D()
                END_PARALLEL_1D()
            }
        END_PARALLEL_2D()
    END_PARALLEL_3D()
    SME_OFF()
}


void brick_transpose(float* p0, float* p1, int sy, int dy)__arm_streaming {
    svbool_t mask_x_0 = svwhilelt_b32(0, 16);
    svbool_t p32_all = svdup_b32(true);
    svld1_hor_za32(0, 0, mask_x_0, &p0[0 + 0]);
    svld1_hor_za32(0, 1, mask_x_0, &p0[0 + (1*16)]);
    svld1_hor_za32(0, 2, mask_x_0, &p0[0 + (2*16)]);
    svld1_hor_za32(0, 3, mask_x_0, &p0[0 + (3*16)]);
    svld1_hor_za32(0, 4, mask_x_0, &p0[0 + (1*sy)]);
    svld1_hor_za32(0, 5, mask_x_0, &p0[0 + (1*sy+1*16)]);
    svld1_hor_za32(0, 6, mask_x_0, &p0[0 + (1*sy+2*16)]);
    svld1_hor_za32(0, 7, mask_x_0, &p0[0 + (1*sy+3*16)]);
    svld1_hor_za32(0, 8, mask_x_0, &p0[0 + (2*sy)]);
    svld1_hor_za32(0, 9, mask_x_0, &p0[0 + (2*sy+1*16)]);   
    svld1_hor_za32(0, 10, mask_x_0, &p0[0 + (2*sy+2*16)]);
    svld1_hor_za32(0, 11, mask_x_0, &p0[0 + (2*sy+3*16)]);
    svld1_hor_za32(0, 12, mask_x_0, &p0[0 + (3*sy)]);
    svld1_hor_za32(0, 13, mask_x_0, &p0[0 + (3*sy+1*16)]);
    svld1_hor_za32(0, 14, mask_x_0, &p0[0 + (3*sy+2*16)]);
    svld1_hor_za32(0, 15, mask_x_0, &p0[0 + (3*sy+3*16)]);
    svld1_hor_za32(1, 0, mask_x_0, &p0[0 + (1*16*4)]);
    svld1_hor_za32(1, 1, mask_x_0, &p0[0 + (1*16+1*16*4)]);
    svld1_hor_za32(1, 2, mask_x_0, &p0[0 + (2*16+1*16*4)]);
    svld1_hor_za32(1, 3, mask_x_0, &p0[0 + (3*16+1*16*4)]);
    svld1_hor_za32(1, 4, mask_x_0, &p0[0 + (1*sy+1*16*4)]);
    svld1_hor_za32(1, 5, mask_x_0, &p0[0 + (1*sy+1*16+1*16*4)]);
    svld1_hor_za32(1, 6, mask_x_0, &p0[0 + (1*sy+2*16+1*16*4)]);
    svld1_hor_za32(1, 7, mask_x_0, &p0[0 + (1*sy+3*16+1*16*4)]);
    svld1_hor_za32(1, 8, mask_x_0, &p0[0 + (2*sy+1*16*4)]);
    svld1_hor_za32(1, 9, mask_x_0, &p0[0 + (2*sy+1*16+1*16*4)]);   
    svld1_hor_za32(1, 10, mask_x_0, &p0[0 + (2*sy+2*16+1*16*4)]);
    svld1_hor_za32(1, 11, mask_x_0, &p0[0 + (2*sy+3*16+1*16*4)]);
    svld1_hor_za32(1, 12, mask_x_0, &p0[0 + (3*sy+1*16*4)]);
    svld1_hor_za32(1, 13, mask_x_0, &p0[0 + (3*sy+1*16+1*16*4)]);
    svld1_hor_za32(1, 14, mask_x_0, &p0[0 + (3*sy+2*16+1*16*4)]);
    svld1_hor_za32(1, 15, mask_x_0, &p0[0 + (3*sy+3*16+1*16*4)]);
    svld1_hor_za32(2, 0, mask_x_0, &p0[0 + (2*16*4)]);
    svld1_hor_za32(2, 1, mask_x_0, &p0[0 + (1*16+2*16*4)]);
    svld1_hor_za32(2, 2, mask_x_0, &p0[0 + (2*16+2*16*4)]);
    svld1_hor_za32(2, 3, mask_x_0, &p0[0 + (3*16+2*16*4)]);
    svld1_hor_za32(2, 4, mask_x_0, &p0[0 + (1*sy+2*16*4)]);
    svld1_hor_za32(2, 5, mask_x_0, &p0[0 + (1*sy+1*16+2*16*4)]);
    svld1_hor_za32(2, 6, mask_x_0, &p0[0 + (1*sy+2*16+2*16*4)]);
    svld1_hor_za32(2, 7, mask_x_0, &p0[0 + (1*sy+3*16+2*16*4)]);
    svld1_hor_za32(2, 8, mask_x_0, &p0[0 + (2*sy+2*16*4)]);
    svld1_hor_za32(2, 9, mask_x_0, &p0[0 + (2*sy+1*16+2*16*4)]);   
    svld1_hor_za32(2, 10, mask_x_0, &p0[0 + (2*sy+2*16+2*16*4)]);
    svld1_hor_za32(2, 11, mask_x_0, &p0[0 + (2*sy+3*16+2*16*4)]);
    svld1_hor_za32(2, 12, mask_x_0, &p0[0 + (3*sy+2*16*4)]);
    svld1_hor_za32(2, 13, mask_x_0, &p0[0 + (3*sy+1*16+2*16*4)]);
    svld1_hor_za32(2, 14, mask_x_0, &p0[0 + (3*sy+2*16+2*16*4)]);
    svld1_hor_za32(2, 15, mask_x_0, &p0[0 + (3*sy+3*16+2*16*4)]);
    svld1_hor_za32(3, 0, mask_x_0, &p0[0 + (3*16*4)]);
    svld1_hor_za32(3, 1, mask_x_0, &p0[0 + (1*16+3*16*4)]);
    svld1_hor_za32(3, 2, mask_x_0, &p0[0 + (2*16+3*16*4)]);
    svld1_hor_za32(3, 3, mask_x_0, &p0[0 + (3*16+3*16*4)]);
    svld1_hor_za32(3, 4, mask_x_0, &p0[0 + (1*sy+3*16*4)]);
    svld1_hor_za32(3, 5, mask_x_0, &p0[0 + (1*sy+1*16+3*16*4)]);
    svld1_hor_za32(3, 6, mask_x_0, &p0[0 + (1*sy+2*16+3*16*4)]);
    svld1_hor_za32(3, 7, mask_x_0, &p0[0 + (1*sy+3*16+3*16*4)]);
    svld1_hor_za32(3, 8, mask_x_0, &p0[0 + (2*sy+3*16*4)]);
    svld1_hor_za32(3, 9, mask_x_0, &p0[0 + (2*sy+1*16+3*16*4)]);   
    svld1_hor_za32(3, 10, mask_x_0, &p0[0 + (2*sy+2*16+3*16*4)]);
    svld1_hor_za32(3, 11, mask_x_0, &p0[0 + (2*sy+3*16+3*16*4)]);
    svld1_hor_za32(3, 12, mask_x_0, &p0[0 + (3*sy+3*16*4)]);
    svld1_hor_za32(3, 13, mask_x_0, &p0[0 + (3*sy+1*16+3*16*4)]);
    svld1_hor_za32(3, 14, mask_x_0, &p0[0 + (3*sy+2*16+3*16*4)]);
    svld1_hor_za32(3, 15, mask_x_0, &p0[0 + (3*sy+3*16+3*16*4)]);
    //transpose and store back to grid
    svst1_ver_za32(0, 0, p32_all, &p1[0 + 0]);
    svst1_ver_za32(0, 1, p32_all, &p1[0 + (1*16)]);
    svst1_ver_za32(0, 2, p32_all, &p1[0 + (2*16)]);
    svst1_ver_za32(0, 3, p32_all, &p1[0 + (3*16)]);
    svst1_ver_za32(0, 4, p32_all, &p1[0 + (1*dy)]);
    svst1_ver_za32(0, 5, p32_all, &p1[0 + (1*dy+1*16)]);
    svst1_ver_za32(0, 6, p32_all, &p1[0 + (1*dy+2*16)]);
    svst1_ver_za32(0, 7, p32_all, &p1[0 + (1*dy+3*16)]);
    svst1_ver_za32(0, 8, p32_all, &p1[0 + (2*dy)]);
    svst1_ver_za32(0, 9, p32_all, &p1[0 + (2*dy+1*16)]);   
    svst1_ver_za32(0, 10, p32_all, &p1[0 + (2*dy+2*16)]);
    svst1_ver_za32(0, 11, p32_all, &p1[0 + (2*dy+3*16)]);
    svst1_ver_za32(0, 12, p32_all, &p1[0 + (3*dy)]);
    svst1_ver_za32(0, 13, p32_all, &p1[0 + (3*dy+1*16)]);
    svst1_ver_za32(0, 14, p32_all, &p1[0 + (3*dy+2*16)]);
    svst1_ver_za32(0, 15, p32_all, &p1[0 + (3*dy+3*16)]);
    svst1_ver_za32(1, 0, p32_all, &p1[0 + (1*16*4)]);
    svst1_ver_za32(1, 1, p32_all, &p1[0 + (1*16+1*16*4)]);
    svst1_ver_za32(1, 2, p32_all, &p1[0 + (2*16+1*16*4)]);
    svst1_ver_za32(1, 3, p32_all, &p1[0 + (3*16+1*16*4)]);
    svst1_ver_za32(1, 4, p32_all, &p1[0 + (1*dy+1*16*4)]);
    svst1_ver_za32(1, 5, p32_all, &p1[0 + (1*dy+1*16+1*16*4)]);
    svst1_ver_za32(1, 6, p32_all, &p1[0 + (1*dy+2*16+1*16*4)]);
    svst1_ver_za32(1, 7, p32_all, &p1[0 + (1*dy+3*16+1*16*4)]);
    svst1_ver_za32(1, 8, p32_all, &p1[0 + (2*dy+1*16*4)]);
    svst1_ver_za32(1, 9, p32_all, &p1[0 + (2*dy+1*16+1*16*4)]);   
    svst1_ver_za32(1, 10, p32_all, &p1[0 + (2*dy+2*16+1*16*4)]);
    svst1_ver_za32(1, 11, p32_all, &p1[0 + (2*dy+3*16+1*16*4)]);
    svst1_ver_za32(1, 12, p32_all, &p1[0 + (3*dy+1*16*4)]);
    svst1_ver_za32(1, 13, p32_all, &p1[0 + (3*dy+1*16+1*16*4)]);
    svst1_ver_za32(1, 14, p32_all, &p1[0 + (3*dy+2*16+1*16*4)]);
    svst1_ver_za32(1, 15, p32_all, &p1[0 + (3*dy+3*16+1*16*4)]);
    svst1_ver_za32(2, 0, p32_all, &p1[0 + (2*16*4)]);
    svst1_ver_za32(2, 1, p32_all, &p1[0 + (1*16+2*16*4)]);
    svst1_ver_za32(2, 2, p32_all, &p1[0 + (2*16+2*16*4)]);
    svst1_ver_za32(2, 3, p32_all, &p1[0 + (3*16+2*16*4)]);
    svst1_ver_za32(2, 4, p32_all, &p1[0 + (1*dy+2*16*4)]);
    svst1_ver_za32(2, 5, p32_all, &p1[0 + (1*dy+1*16+2*16*4)]);
    svst1_ver_za32(2, 6, p32_all, &p1[0 + (1*dy+2*16+2*16*4)]);
    svst1_ver_za32(2, 7, p32_all, &p1[0 + (1*dy+3*16+2*16*4)]);
    svst1_ver_za32(2, 8, p32_all, &p1[0 + (2*dy+2*16*4)]);
    svst1_ver_za32(2, 9, p32_all, &p1[0 + (2*dy+1*16+2*16*4)]);   
    svst1_ver_za32(2, 10, p32_all, &p1[0 + (2*dy+2*16+2*16*4)]);
    svst1_ver_za32(2, 11, p32_all, &p1[0 + (2*dy+3*16+2*16*4)]);
    svst1_ver_za32(2, 12, p32_all, &p1[0 + (3*dy+2*16*4)]);
    svst1_ver_za32(2, 13, p32_all, &p1[0 + (3*dy+1*16+2*16*4)]);
    svst1_ver_za32(2, 14, p32_all, &p1[0 + (3*dy+2*16+2*16*4)]);
    svst1_ver_za32(2, 15, p32_all, &p1[0 + (3*dy+3*16+2*16*4)]);
    svst1_ver_za32(3, 0, p32_all, &p1[0 + (3*16*4)]);
    svst1_ver_za32(3, 1, p32_all, &p1[0 + (1*16+3*16*4)]);
    svst1_ver_za32(3, 2, p32_all, &p1[0 + (2*16+3*16*4)]);
    svst1_ver_za32(3, 3, p32_all, &p1[0 + (3*16+3*16*4)]);
    svst1_ver_za32(3, 4, p32_all, &p1[0 + (1*dy+3*16*4)]);
    svst1_ver_za32(3, 5, p32_all, &p1[0 + (1*dy+1*16+3*16*4)]);
    svst1_ver_za32(3, 6, p32_all, &p1[0 + (1*dy+2*16+3*16*4)]);
    svst1_ver_za32(3, 7, p32_all, &p1[0 + (1*dy+3*16+3*16*4)]);
    svst1_ver_za32(3, 8, p32_all, &p1[0 + (2*dy+3*16*4)]);
    svst1_ver_za32(3, 9, p32_all, &p1[0 + (2*dy+1*16+3*16*4)]);   
    svst1_ver_za32(3, 10, p32_all, &p1[0 + (2*dy+2*16+3*16*4)]);
    svst1_ver_za32(3, 11, p32_all, &p1[0 + (2*dy+3*16+3*16*4)]);
    svst1_ver_za32(3, 12, p32_all, &p1[0 + (3*dy+3*16*4)]);
    svst1_ver_za32(3, 13, p32_all, &p1[0 + (3*dy+1*16+3*16*4)]);
    svst1_ver_za32(3, 14, p32_all, &p1[0 + (3*dy+2*16+3*16*4)]);
    svst1_ver_za32(3, 15, p32_all, &p1[0 + (3*dy+3*16+3*16*4)]);
}