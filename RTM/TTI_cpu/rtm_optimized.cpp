#include "common.h"
//v delta e_d xdip_1 ydip_1 nz_node_last * nxf * nyf
//u, q (nz_node_last + 2 nPad ) * nxf * nyf
//uzz, uxx n_threads*(iyStncilsiz*nxf*BLOCK_SIZE + 8*nxf)
//z_fdcoef_1st z_fdcoef nz_fd * (2 * nPad + 1)
#define TileX 128
#define TileY 64
#define TileZ 16
#define HALO 4
#define PADDING 16
#define VX 32
#define VY 32
#define VZ 2


void rtm3_update_3d_tti_omp(void *Rtmig_thrd0) {

    struct RTMIG_THRD *Rtmig_thrd = (struct RTMIG_THRD *) Rtmig_thrd0;
    const int rank = Rtmig_thrd->rank;
    const int size = Rtmig_thrd->size;

    const int nPad = Rtmig_thrd->nPad;
    const int nxf = Rtmig_thrd->nxf;
    const int nyf = Rtmig_thrd->nyf;
    const int nx = nxf - 2 * nPad;
    const int ny = nyf - 2 * nPad;
    const int nz = (rank == size - 1) ? Rtmig_thrd->nz_node_last : Rtmig_thrd->nz_node;
    const int nzf = nz + 2*nPad;
    
    // const int nxf2 = nxf + nxf;
    // const int nxf3 = nxf2 + nxf;
    // const int nxf4 = nxf3 + nxf;

    // const int slice = nxf * nyf;
    // const int slice2 = slice + slice;
    // const int slice3 = slice2 + slice;
    // const int slice4 = slice3 + slice;

    const int stncilsiz = 9;

    const float (* __restrict__ V)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->v;
    const float (* __restrict__ D)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->delta;
    const float (* __restrict__ E)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->e;

    // suppose we have the following dips data
    // revise it according to gpu tti code late May 12, 2013 RC
    const float (* __restrict__ DIPX)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->dip_x;
    const float (* __restrict__ DIPY)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->dip_y;

    const float (* __restrict__ U1)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->u1;
    const float (* __restrict__ U2)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->u2;
    float (* __restrict__ U3)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->u3;

    const float (* __restrict__ Q1)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->q1;
    const float (* __restrict__ Q2)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->q2;
    float (* __restrict__ Q3)[nyf][nxf] = (float (*)[nyf][nxf])Rtmig_thrd->q3;

    const float *__restrict__ ZC1 = Rtmig_thrd->z_fdcoef_1st;
    const float *__restrict__ ZC2 = Rtmig_thrd->z_fdcoef;

    // // U2 and QZ thread working buffer May 12, 2013 RC
    // float * __restrict__ UZ = Rtmig_thrd->uxx + ibufsize * i_thread;
    // float * __restrict__ QZ = Rtmig_thrd->uzz + ibufsize * i_thread;
    static float UZ[VZ][VY + 2*HALO][TileX + 2*PADDING];
    static float QZ[VZ][VY + 2*HALO][TileX + 2*PADDING];

    static float UY [VZ][VY][TileX + 2*PADDING];
    static float UZY[VZ][VY][TileX + 2*PADDING];
    static float UZX[VZ][VY][TileX + 2*PADDING];
    static float UYX[VZ][VY][TileX + 2*PADDING];
    static float UX2[VZ][VY][TileX + 2*PADDING];
    static float UY2[VZ][VY][TileX + 2*PADDING];
    static float UZ2[VZ][VY][TileX + 2*PADDING];

    static float QY[VZ][VY][TileX + 2*PADDING];
    static float QZY[VZ][VY][TileX + 2*PADDING];
    static float QZX[VZ][VY][TileX + 2*PADDING];
    static float QYX[VZ][VY][TileX + 2*PADDING];
    static float QX2[VZ][VY][TileX + 2*PADDING];
    static float QY2[VZ][VY][TileX + 2*PADDING];
    static float QZ2[VZ][VY][TileX + 2*PADDING];

    #pragma omp thread_private(UZ, QZ, UY, UZY, UZX, UYX, UX2, UY2, UZ2, QY, QZY, QZX, QYX, QX2, QY2, QZ2)
    const float dx = Rtmig_thrd->Fda_dx;
    const float b2 = cos(Rtmig_thrd->angle * M_PI / 180.0);

    const float sigma = 0.66667f;

    const float dy1i = 1.0f / Rtmig_thrd->Fda_dy;
    const float dx1i = 1.0f / Rtmig_thrd->Fda_dx;
    const float dy2i = dy1i*dy1i;
    const float dx2i = dx1i*dx1i;
    
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

#if DDE_ON
    const int bx1 = (Rtmig_thrd->bx1 < 4) ? 4 : Rtmig_thrd->bx1;
    const int bx2 = (Rtmig_thrd->bx2 > nxf - 4) ? (nxf - 4) : Rtmig_thrd->bx2;
    const int by1 = (Rtmig_thrd->by1 < 4) ? 4 : Rtmig_thrd->by1;
    const int by2 = (Rtmig_thrd->by2 > nyf - 4) ? (nyf - 4) : Rtmig_thrd->by2;
    const int bz1 = (Rtmig_thrd->bz1 < 4) ? 4 : Rtmig_thrd->bz1;
    const int bz2 = (Rtmig_thrd->bz2 > nzf - 4) ? (nzf - 4) : Rtmig_thrd->bz2;
#else
    const int bx1 = 4;
    const int bx2 = nxf - 4;
    const int by1 = 4;
    const int by2 = nyf - 4;
    const int bz1 = 4;
    const int bz2 = nzf - 4;
#endif
    #pragma omp parallel for collapse(3)
    PARALLEL_3D(ti, tj, tk, bx1, by1, bz1, bx2, by2, bz2, TileX, TileY, TileZ)
        int tile_size_x = MIN(TileX, bx2 - ti);
        int tile_size_y = MIN(TileY, by2 - tj);
        int tile_size_z = MIN(TileZ, bz2 - tk);

        float (* __restrict__ uz)[VY + 2*HALO][TileX + 2*PADDING] = (float (*)[VY + 2*HALO][TileX + 2*PADDING])&UZ[0][HALO][PADDING];
        float (* __restrict__ qz)[VY + 2*HALO][TileX + 2*PADDING] = (float (*)[VY + 2*HALO][TileX + 2*PADDING])&QZ[0][HALO][PADDING];

        float (* __restrict__ uy)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UY[0][0][PADDING];
        float (* __restrict__ uzy)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UZY[0][0][PADDING];
        float (* __restrict__ uzx)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UZX[0][0][PADDING];
        float (* __restrict__ uyx)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UYX[0][0][PADDING];
        float (* __restrict__ ux2)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UX2[0][0][PADDING];
        float (* __restrict__ uy2)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UY2[0][0][PADDING];
        float (* __restrict__ uz2)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&UZ2[0][0][PADDING];

        float (* __restrict__ qy)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QY[0][0][PADDING];
        float (* __restrict__ qzy)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QZY[0][0][PADDING];
        float (* __restrict__ qzx)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QZX[0][0][PADDING];
        float (* __restrict__ qyx)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QYX[0][0][PADDING];
        float (* __restrict__ qx2)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QX2[0][0][PADDING];
        float (* __restrict__ qy2)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QY2[0][0][PADDING];
        float (* __restrict__ qz2)[VY][TileX + 2*PADDING] = (float (*)[VY][TileX + 2*PADDING])&QZ2[0][0][PADDING];

        PARALLEL_2D(k, j, tk, tj, tk + tile_size_z, tj + tile_size_y, VZ, VY)
            int vec_size_y = MIN(VY, tj + tile_size_y - j);
            int vec_size_z = MIN(VZ, tk + tile_size_z - k);

            const float (* __restrict__ v)[nyf][nxf] = (float (*)[nyf][nxf])&V[k-nPad][j][ti];
            const float (* __restrict__ d)[nyf][nxf] = (float (*)[nyf][nxf])&D[k-nPad][j][ti];
            const float (* __restrict__ e)[nyf][nxf] = (float (*)[nyf][nxf])&E[k-nPad][j][ti];
            const float (* __restrict__ xd)[nyf][nxf] = (float (*)[nyf][nxf])&DIPX[k-nPad][j][ti];
            const float (* __restrict__ yd)[nyf][nxf] = (float (*)[nyf][nxf])&DIPY[k-nPad][j][ti];


            const float (* __restrict__ u1)[nyf][nxf] = (float (*)[nyf][nxf])&U1[k][j][ti];
            const float (* __restrict__ u2)[nyf][nxf] = (float (*)[nyf][nxf])&U2[k][j][ti];
            float (* __restrict__ u3)[nyf][nxf] = (float (*)[nyf][nxf])&U3[k][j][ti];

            const float (* __restrict__ q1)[nyf][nxf] = (float (*)[nyf][nxf])&Q1[k][j][ti];
            const float (* __restrict__ q2)[nyf][nxf] = (float (*)[nyf][nxf])&Q2[k][j][ti];
            float (* __restrict__ q3)[nyf][nxf] = (float (*)[nyf][nxf])&Q3[k][j][ti];


            for(int iuq=0; iuq<2; ++iuq) {
                const float (* __restrict__ p2)[nyf][nxf] = (iuq==0) ? u2 : q2;
                float (* __restrict__ pz)[VY + 2*HALO][TileX + 2*PADDING] = (iuq==0) ? uz : qz;

                float (* __restrict__ py) [VY][TileX + 2*PADDING] = (iuq==0) ? uy : qy;
                float (* __restrict__ pzy)[VY][TileX + 2*PADDING] = (iuq==0) ? uzy : qzy;
                float (* __restrict__ pzx)[VY][TileX + 2*PADDING] = (iuq==0) ? uzx : qzx;
                float (* __restrict__ pyx)[VY][TileX + 2*PADDING] = (iuq==0) ? uyx : qyx;
                float (* __restrict__ px2)[VY][TileX + 2*PADDING] = (iuq==0) ? ux2 : qx2;
                float (* __restrict__ py2)[VY][TileX + 2*PADDING] = (iuq==0) ? uy2 : qy2;
                float (* __restrict__ pz2)[VY][TileX + 2*PADDING] = (iuq==0) ? uz2 : qz2;

                //get pz2
                PARALLEL_1D(vk, 0, vec_size_z, 1)
                    const float * __restrict__ zc2 = ZC2 + (k + vk - nPad) * stncilsiz + nPad;
                    PARALLEL_2D(vi, vj, 0, 0, tile_size_x, vec_size_y, 1, 1)
                        pz2[vk][vj][vi] = zc2[0] * p2[vk][vj][vi]
                            + zc2[-1]*p2[vk - 1][vj][vi]  + zc2[1]*p2[vk + 1][vj][vi]
                            + zc2[-2]*p2[vk - 2][vj][vi]  + zc2[2]*p2[vk + 2][vj][vi]
                            + zc2[-3]*p2[vk - 3][vj][vi]  + zc2[3]*p2[vk + 3][vj][vi]
                            + zc2[-4]*p2[vk - 4][vj][vi]  + zc2[4]*p2[vk + 4][vj][vi];
                    END_PARALLEL_2D( )
                END_PARALLEL_1D( )

                //get pz
                PARALLEL_1D(vk, 0, vec_size_z, 1)
                    const float * __restrict__ zc1 = ZC1 + (k + vk - nPad) * stncilsiz + nPad;
                    PARALLEL_2D(vi, vj, -nPad, -nPad, tile_size_x + nPad, vec_size_y + nPad, 1, 1)
                        pz[vk][vj][vi] = 
                              zc1[-1]*p2[vk - 1][vj][vi]  + zc1[1]*p2[vk + 1][vj][vi]
                            + zc1[-2]*p2[vk - 2][vj][vi]  + zc1[2]*p2[vk + 2][vj][vi]
                            + zc1[-3]*p2[vk - 3][vj][vi]  + zc1[3]*p2[vk + 3][vj][vi]
                            + zc1[-4]*p2[vk - 4][vj][vi]  + zc1[4]*p2[vk + 4][vj][vi];
                    END_PARALLEL_2D( )
                END_PARALLEL_1D( )

                //get pzx
                PARALLEL_3D(vi, vj, vk, 0, 0, 0, tile_size_x, vec_size_y, vec_size_z, 1, 1, 1)
                    pzx[vk][vj][vi] = 
                                  xc1[1]*(pz[vk][vj][vi+1] - pz[vk][vj][vi-1])
                                + xc1[2]*(pz[vk][vj][vi+2] - pz[vk][vj][vi-2])
                                + xc1[3]*(pz[vk][vj][vi+3] - pz[vk][vj][vi-3])
                                + xc1[4]*(pz[vk][vj][vi+4] - pz[vk][vj][vi-4]);
                END_PARALLEL_3D( )

                //get pzy
                PARALLEL_3D(vi, vj, vk, 0, 0, 0, tile_size_x, vec_size_y, vec_size_z, 1, 1, 1)
                    pzy[vk][vj][vi] = 
                                  yc1[1]*(pz[vk][vj+1][vi] - pz[vk][vj-1][vi])
                                + yc1[2]*(pz[vk][vj+2][vi] - pz[vk][vj-2][vi])
                                + yc1[3]*(pz[vk][vj+3][vi] - pz[vk][vj-3][vi])
                                + yc1[4]*(pz[vk][vj+4][vi] - pz[vk][vj-4][vi]);
                END_PARALLEL_3D( )

                //get py
                PARALLEL_3D(vi, vj, vk, -nPad, 0, 0, tile_size_x + nPad, vec_size_y, vec_size_z, 1, 1, 1)
                    py[vk][vj][vi] = 
                                  yc1[1]*(p2[vk][vj+1][vi] - p2[vk][vj-1][vi])
                                + yc1[2]*(p2[vk][vj+2][vi] - p2[vk][vj-2][vi])
                                + yc1[3]*(p2[vk][vj+3][vi] - p2[vk][vj-3][vi])
                                + yc1[4]*(p2[vk][vj+4][vi] - p2[vk][vj-4][vi]);
                END_PARALLEL_3D( )

                //get pyx
                PARALLEL_3D(vi, vj, vk, 0, 0, 0, tile_size_x, vec_size_y, vec_size_z, 1, 1, 1)
                    pyx[vk][vj][vi] = 
                                  xc1[1]*(py[vk][vj][vi+1] - py[vk][vj][vi-1])
                                + xc1[2]*(py[vk][vj][vi+2] - py[vk][vj][vi-2])
                                + xc1[3]*(py[vk][vj][vi+3] - py[vk][vj][vi-3])
                                + xc1[4]*(py[vk][vj][vi+4] - py[vk][vj][vi-4]);
                END_PARALLEL_3D( )

                //get px2
                PARALLEL_3D(vi, vj, vk, 0, 0, 0, tile_size_x, vec_size_y, vec_size_z, 1, 1, 1)
                    px2[vk][vj][vi] = xc2[0] * p2[vk][vj][vi]
                            + xc2[1] * (p2[vk][vj][vi+1] + p2[vk][vj][vi-1])
                            + xc2[2] * (p2[vk][vj][vi+2] + p2[vk][vj][vi-2])
                            + xc2[3] * (p2[vk][vj][vi+3] + p2[vk][vj][vi-3])
                            + xc2[4] * (p2[vk][vj][vi+4] + p2[vk][vj][vi-4]);
                END_PARALLEL_3D( )

                //get py2
                PARALLEL_3D(vi, vj, vk, 0, 0, 0, tile_size_x, vec_size_y, vec_size_z, 1, 1, 1)
                    py2[vk][vj][vi] = yc2[0] * p2[vk][vj][vi]
                            + yc2[1] * (p2[vk][vj+1][vi] + p2[vk][vj-1][vi])
                            + yc2[2] * (p2[vk][vj+2][vi] + p2[vk][vj-2][vi])
                            + yc2[3] * (p2[vk][vj+3][vi] + p2[vk][vj-3][vi])
                            + yc2[4] * (p2[vk][vj+4][vi] + p2[vk][vj-4][vi]);
                END_PARALLEL_3D( )
            }// end of iuq


#pragma ivdep
#pragma vector nontemporal (u3, q3)
            PARALLEL_3D(vi, vj, vk, 0, 0, 0, tile_size_x, vec_size_y, vec_size_z, 1, 1, 1)
                const float xdip = xd[vk][vj][vi];
                const float ydip = yd[vk][vj][vi];
                const float xdip2 = xdip * xdip;
                const float ydip2 = ydip * ydip;
                const float xdip_2 = -2.0f * xdip;
                const float ydip_2 = -2.0f * ydip;
                const float xydip_2 = 2.0f * xdip * ydip;
                const float xydip_i = 1.0f / (1.0f + xdip2 + ydip2);

                float h1u = (ux2[vk][vj][vi] * xdip2 + uy2[vk][vj][vi] * ydip2 + uz2[vk][vj][vi]
                                + uyx[vk][vj][vi] * xydip_2 + uzy[vk][vj][vi] * ydip_2 + uzx[vk][vj][vi] * xdip_2) * xydip_i;
                float h2u = ux2[vk][vj][vi] + uy2[vk][vj][vi] + uz2[vk][vj][vi] - h1u;

                float h1q = (qx2[vk][vj][vi] * xdip2 + qy2[vk][vj][vi] * ydip2 + qz2[vk][vj][vi]
                                + qyx[vk][vj][vi] * xydip_2 + qzy[vk][vj][vi] * ydip_2 + qzx[vk][vj][vi] * xdip_2) * xydip_i;
                float h2q = qx2[vk][vj][vi] + qy2[vk][vj][vi] + qz2[vk][vj][vi] - h1q;

                const float iv = v[vk][vj][vi];
                const float ie = e[vk][vj][vi];
                const float id = d[vk][vj][vi];

                float isigma = sigma * (ie - id);
                u3[vk][vj][vi] = u2[vk][vj][vi] + u2[vk][vj][vi] - u1[vk][vj][vi] + iv * (ie * h2u + h1q + isigma * (h1u - h1q));
                q3[vk][vj][vi] = q2[vk][vj][vi] + q2[vk][vj][vi] - q1[vk][vj][vi] + iv * (id * h2u + h1q + isigma * (h2q - h2u));

            END_PARALLEL_3D( )
        END_PARALLEL_2D( )
    END_PARALLEL_3D( ) 
    return;
}