#include "common.h"
//v delta e_d xdip_1 ydip_1 nz_node_last * nxf * nyf
//u, q (nz_node_last + 2 nPad ) * nxf * nyf
//uzz, uxx n_threads*(iyStncilsiz*nxf*BLOCK_SIZE + 8*nxf)
//z_fdcoef_1st z_fdcoef nz_fd * (2 * nPad + 1)

void *rtm3_update_3d_tti_pthread(void *Rtmig_thrd0) {

    struct RTMIG_THRD *Rtmig_thrd = (struct RTMIG_THRD *) Rtmig_thrd0;
    const int i_thread = Rtmig_thrd->i_thread;
    const int n_threads = Rtmig_thrd->n_threads;
    const int rank = Rtmig_thrd->rank;
    const int size = Rtmig_thrd->size;

    const int nPad = Rtmig_thrd->nPad;
    const int nxf = Rtmig_thrd->nxf;
    const int nyf = Rtmig_thrd->nyf;
    const int nx = nxf - 2 * nPad;
    const int ny = nyf - 2 * nPad;
    const int nz = (rank == size - 1) ? Rtmig_thrd->nz_node_last : Rtmig_thrd->nz_node;
    const int nzf = nz + 2*nPad;
    
    const int nxf2 = nxf + nxf;
    const int nxf3 = nxf2 + nxf;
    const int nxf4 = nxf3 + nxf;

    const int slice = nxf * nyf;
    const int slice2 = slice + slice;
    const int slice3 = slice2 + slice;
    const int slice4 = slice3 + slice;

    const float * __restrict__ V = Rtmig_thrd->v;
    const float * __restrict__ D = Rtmig_thrd->delta;
    const float * __restrict__ E = Rtmig_thrd->e;

    // suppose we have the following dips data
    // revise it according to gpu tti code late May 12, 2013 RC
    const float * __restrict__ DIPX = Rtmig_thrd->dip_x;
    const float * __restrict__ DIPY = Rtmig_thrd->dip_y;

    const float * __restrict__ U1 = Rtmig_thrd->u1;
    const float * __restrict__ U2 = Rtmig_thrd->u2;
    float * __restrict__ U3 = Rtmig_thrd->u3;

    const float * __restrict__ Q1 = Rtmig_thrd->q1;
    const float * __restrict__ Q2 = Rtmig_thrd->q2;
    float * __restrict__ Q3 = Rtmig_thrd->q3;

    const float *__restrict__ ZC1 = Rtmig_thrd->z_fdcoef_1st;
    const float *__restrict__ ZC2 = Rtmig_thrd->z_fdcoef;

    const int blksiz = BLOCK_SIZE; // assuming BLOCK_SIZE is a macro for block size
    const int stncilsiz = 9;
    const int pz_slice = stncilsiz * nxf;
    const int pz_bufsiz = blksiz * pz_slice;
    const int ibufsize = pz_bufsiz + 7 * nxf;

    // U2 and QZ thread working buffer May 12, 2013 RC
    float * __restrict__ UZ = Rtmig_thrd->uxx + ibufsize * i_thread;
    float * __restrict__ QZ = Rtmig_thrd->uzz + ibufsize * i_thread;

    float * __restrict__ uy = UZ + pz_bufsiz;
    float * __restrict__ uzy = uy + nxf;
    float * __restrict__ uzx = uzy + nxf;
    float * __restrict__ uyx = uzx + nxf;
    float * __restrict__ ux2 = uyx + nxf;
    float * __restrict__ uy2 = ux2 + nxf;
    float * __restrict__ uz2 = uy2 + nxf;

    float * __restrict__ qy = QZ + pz_bufsiz;
    float * __restrict__ qzy = qy + nxf;
    float * __restrict__ qzx = qzy + nxf;
    float * __restrict__ qyx = qzx + nxf;
    float * __restrict__ qx2 = qyx + nxf;
    float * __restrict__ qy2 = qx2 + nxf;
    float * __restrict__ qz2 = qy2 + nxf;


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

    const int pybx1 = bx1 - 4;
    const int pybx2 = bx2 + 4;

    const int zbgn = bz1 + (bz2 - bz1) * i_thread / n_threads;
    const int zend = bz1 + (bz2 - bz1) * (i_thread + 1) / n_threads;
    int blkbgn = zbgn;

    // exclude nPad in y dim May 12, 2013 RC
    const int uzybgn = by1-nPad;
    const int uzyend = by1+nPad;
    // assume that one thread may take care more than one block
    for(; blkbgn < zend && blkbgn < bz2; blkbgn += blksiz) {
        int blkend = (blkbgn + blksiz) > zend ? zend : blkbgn + blksiz;

        // step 1: first 8 y layers calculation
        for(int iuq=0; iuq<2; ++iuq) {
            const float * __restrict__ P2 = (iuq==0) ? U2 : Q2;
            float * __restrict__ PZ = (iuq==0) ? UZ : QZ;

            for(int iy=uzybgn, k=0; iy<uzyend; ++iy,++k) {
                // iz2: idx to global wavefield
                const float * __restrict__ p2 = P2 + blkbgn*slice + iy*nxf;
                float * __restrict__ pz = PZ + k*nxf;
                const float * __restrict__ zc1 = ZC1 + (blkbgn - nPad) * stncilsiz + nPad;

                for (int iz=blkbgn; iz<blkend; ++iz) {
                    for (int ix=pybx1; ix<pybx2; ++ix) {
                        pz[ix]  = zc1[-1]*p2[ix-slice]   + zc1[1]*p2[ix+slice]
                                + zc1[-2]*p2[ix-slice2]  + zc1[2]*p2[ix+slice2]
                                + zc1[-3]*p2[ix-slice3]  + zc1[3]*p2[ix+slice3]
                                + zc1[-4]*p2[ix-slice4]  + zc1[4]*p2[ix+slice4];
                    } // ix loop
                    zc1 += stncilsiz;
                    p2  += slice;
                    pz  += pz_slice;
                } // iz loop
            }// end of iuq loop
        }

        //second pass: get rest of them, uy, uzy, uzx, ayx, ux2, uy2, u22, qy, qay, gex, qyx, qx2, qv2, gaz
        for (int iy=by1; iy<by2; ++iy) {
            const int iy_current = (iy-by1+nPad)%stncilsiz;
            const int iy_remote = (iy_current+nPad)%stncilsiz;

            const int uoff = blkbgn*slice + iy*nxf;
            const int voff = (blkbgn-nPad)*slice + iy*nxf;

            const float * __restrict__ u1 = U1 + uoff;
            const float * __restrict__ u2 = U2 + uoff;
            const float * __restrict__ q1 = Q1 + uoff;
            const float * __restrict__ q2 = Q2 + uoff;

            const float * __restrict__ v = V + voff;
            const float * __restrict__ e = E + voff;
            const float * __restrict__ d = D + voff;
            const float * __restrict__ xd = DIPX + voff;
            const float * __restrict__ yd = DIPY + voff;

            float * __restrict__ u3 = U3 + uoff;
            float * __restrict__ q3 = Q3 + uoff;

            const float * __restrict__ zc1 = ZC1 + (blkbgn-nPad)*stncilsiz + nPad; // move to center point
            const float * __restrict__ zc2 = ZC2 + (blkbgn-nPad)*stncilsiz + nPad; // move to center point

            int iz_current_offset = 0;
            const int iy_remote_offset = iy_remote*nxf;
            const int iy_current_offset = iy_current*nxf;

            for(int iz=blkbgn; iz<blkend; iz++) {
                for(int iuq=0; iuq<2; ++iuq) {
                    const float * __restrict__ p2 = (iuq==0) ? u2 : q2;
                    float * __restrict__ PZ = (iuq==0) ? UZ : QZ;
                    float * __restrict__ py = (iuq==0) ? uy : qy;
                    float * __restrict__ pzy = (iuq==0) ? uzy : qzy;
                    float * __restrict__ pzx = (iuq==0) ? uzx : qzx;
                    float * __restrict__ pyx = (iuq==0) ? uyx : qyx;
                    float * __restrict__ px2 = (iuq==0) ? ux2 : qx2;
                    float * __restrict__ py2 = (iuq==0) ? uy2 : qy2;
                    float * __restrict__ pz2 = (iuq==0) ? uz2 : qz2;

                    // right most pz calculation
                    const float * __restrict__  pr2 = p2 + nPad*nxf;
                    float * __restrict__        pzr = PZ + iz_current_offset + iy_remote_offset;

                    for(int ix=pybx1; ix<pybx2; ++ix) {
                        pzr[ix] = zc1[-1]*pr2[ix-slice] + zc1[1]*pr2[ix+slice]
                                + zc1[-2]*pr2[ix-slice2] + zc1[2]*pr2[ix+slice2]
                                + zc1[-3]*pr2[ix-slice3] + zc1[3]*pr2[ix+slice3]
                                + zc1[-4]*pr2[ix-slice4] + zc1[4]*pr2[ix+slice4];
                    }// pz right most done

                    // get py
                    for(int ix=pybx1; ix<pybx2; ++ix) {
                        py[ix]  = yc1[1]*(p2[ix+nxf] - p2[ix-nxf])
                                + yc1[2]*(p2[ix+nxf2] - p2[ix-nxf2])
                                + yc1[3]*(p2[ix+nxf3] - p2[ix-nxf3])
                                + yc1[4]*(p2[ix+nxf4] - p2[ix-nxf4]);
                    } // py done

                    // get pyx
                    for(int ix=bx1; ix<bx2; ++ix) {
                        pyx[ix] = xc1[1]*(py[ix+1] - py[ix-1])
                                + xc1[2]*(py[ix+2] - py[ix-2])
                                + xc1[3]*(py[ix+3] - py[ix-3])
                                + xc1[4]*(py[ix+4] - py[ix-4]);
                    }
                    // pyx done

                    // uzx
                    float* __restrict__ pz = PZ + iz_current_offset + iy_current_offset;
                    for(int ix=bx1; ix<bx2; ++ix) {
                        pzx[ix] = xc1[1]*(pz[ix+1] - pz[ix-1])
                                + xc1[2]*(pz[ix+2] - pz[ix-2])
                                + xc1[3]*(pz[ix+3] - pz[ix-3])
                                + xc1[4]*(pz[ix+4] - pz[ix-4]);
                    }
                    // pzx done

#pragma ivdep
                    for (int ix=bx1; ix<bx2; ++ix) {
                        float *pzr = PZ + iz_current_offset + (stncilsiz + iy_current + 1) % stncilsiz * nxf;
                        float *pzl = PZ + iz_current_offset + (stncilsiz + iy_current - 1) % stncilsiz * nxf;
                        pzy[ix] = yc1[1] * (pzr[ix] - pzl[ix]);

                        pzr = PZ + iz_current_offset + (stncilsiz + iy_current + 2) % stncilsiz * nxf;
                        pzl = PZ + iz_current_offset + (stncilsiz + iy_current - 2) % stncilsiz * nxf;
                        pzy[ix] += yc1[2] * (pzr[ix] - pzl[ix]);

                        pzr = PZ + iz_current_offset + (stncilsiz + iy_current + 3) % stncilsiz * nxf;
                        pzl = PZ + iz_current_offset + (stncilsiz + iy_current - 3) % stncilsiz * nxf;
                        pzy[ix] += yc1[3] * (pzr[ix] - pzl[ix]);

                        pzr = PZ + iz_current_offset + (stncilsiz + iy_current + 4) % stncilsiz * nxf;
                        pzl = PZ + iz_current_offset + (stncilsiz + iy_current - 4) % stncilsiz * nxf;
                        pzy[ix] += yc1[4] * (pzr[ix] - pzl[ix]);
                    }   // pzy done

                // ux2
#pragma ivdep
                    for (int ix=bx1; ix<bx2; ++ix) {
                        px2[ix] = xc2[0] * p2[ix]
                                + xc2[1] * (p2[ix + 1] + p2[ix - 1])
                                + xc2[2] * (p2[ix + 2] + p2[ix - 2])
                                + xc2[3] * (p2[ix + 3] + p2[ix - 3])
                                + xc2[4] * (p2[ix + 4] + p2[ix - 4]);
                    }  // ux2 done


#pragma ivdep
                    for (int ix=bx1; ix<bx2; ++ix) {
                        py2[ix] = yc2[0] * p2[ix]
                                + yc2[1] * (p2[ix + nxf] + p2[ix - nxf])
                                + yc2[2] * (p2[ix + nxf2] + p2[ix - nxf2])
                                + yc2[3] * (p2[ix + nxf3] + p2[ix - nxf3])
                                + yc2[4] * (p2[ix + nxf4] + p2[ix - nxf4]);
                    }   // uy2 done

                // uz2
#pragma ivdep
                    for (int ix=bx1; ix<bx2; ++ix) {
                        pz2[ix] = zc2[0] * p2[ix]
                                + zc2[1] * p2[ix + slice] + zc2[-1] * p2[ix - slice]
                                + zc2[2] * p2[ix + slice2] + zc2[-2] * p2[ix - slice2]
                                + zc2[3] * p2[ix + slice3] + zc2[-3] * p2[ix - slice3]
                                + zc2[4] * p2[ix + slice4] + zc2[-4] * p2[ix - slice4];
                    }   // uz2 done
                }

#pragma ivdep
#pragma vector nontemporal (u3, q3)
                for (int ix=bx1; ix<bx2; ++ix) {
                    const float xdip = xd[ix];
                    const float ydip = yd[ix];
                    const float xdip2 = xdip * xdip;
                    const float ydip2 = ydip * ydip;
                    const float xdip_2 = -2.0f * xdip;
                    const float ydip_2 = -2.0f * ydip;
                    const float xydip_2 = 2.0f * xdip * ydip;
                    const float xydip_i = 1.0f / (1.0f + xdip2 + ydip2);

                    float h1u = (ux2[ix] * xdip2 + uy2[ix] * ydip2 + uz2[ix]
                                    + uyx[ix] * xydip_2 + uzy[ix] * ydip_2 + uzx[ix] * xdip_2) * xydip_i;
                    float h2u = ux2[ix] + uy2[ix] + uz2[ix] - h1u;

                    float h1q = (qx2[ix] * xdip2 + qy2[ix] * ydip2 + qz2[ix]
                                    + qyx[ix] * xydip_2 + qzy[ix] * ydip_2 + qzx[ix] * xdip_2) * xydip_i;
                    float h2q = qx2[ix] + qy2[ix] + qz2[ix] - h1q;

                    const float iv = v[ix];
                    const float ie = e[ix];
                    const float id = d[ix];

                    float isigma = sigma * (ie - id);
                    u3[ix] = u2[ix] + u2[ix] - u1[ix] + iv * (ie * h2u + h1q + isigma * (h1u - h1q));
                    q3[ix] = q2[ix] + q2[ix] - q1[ix] + iv * (id * h2u + h1q + isigma * (h2q - h2u));
                }
                // move forwards
                iz_current_offset += pz_slice;
                zc1 += 9;
                zc2 += 9;

                u1 += slice;
                u2 += slice;
                u3 += slice;

                q1 += slice;
                q2 += slice;
                q3 += slice;

                v += slice;
                d += slice;
                e += slice;

                xd += slice;
                yd += slice;

            } // end of z block
        } // end of y loop
    } // end of block z loop
    pthread_exit((void *)0);
}