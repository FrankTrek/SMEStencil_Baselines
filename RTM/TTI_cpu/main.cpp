#include "common.h"

extern const char* func_name;
// uint64_t s[2] = { 0x41, 0x29837592 };

inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

// uint64_t next(void) {
//     const uint64_t s0 = s[0];
//     uint64_t s1 = s[1];
//     const uint64_t result = s0 + s1;

//     s1 ^= s0;
//     s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
//     s[1] = rotl(s1, 36); // c

//     return result;
// }

// float uniform() {
//     return next()*(1.0/18446744073709551616.0);
// }


void fast_randomize(float* arr, size_t size) {
    static uint64_t s[8] = { 0x41, 0x29837592, 0, 0, 0, 0, 0, 0 };
    #pragma omp thread private(s)

    #pragma omp parallel 
    {
        int tid = omp_get_thread_num();
        s[0] = 0x41 + tid;
        #pragma omp for schedule(static)
        for(size_t i = 0; i < size; i++) {
            const uint64_t s0 = s[0];
            uint64_t s1 = s[1];
            const uint64_t result = s0 + s1;
            s1 ^= s0;
            s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
            s[1] = rotl(s1, 36); // c

            arr[i] = result*(1.0/18446744073709551616.0);
        }
    }
} 

void check_result(float* arr, float* ref, size_t size) {
    double err = 0.0, sum = 0.0, rel_err = 0.0, ref_val, arr_val;
    int pos_i = 0;
    #pragma omp parallel for reduction(+: err, sum) 
    for(size_t i = 0; i < size; i++) {
        sum += fabs(arr[i]);
        err += fabs(arr[i] - ref[i]);
        double tmp_rel_err = fabs(arr[i] - ref[i]) / (fabs(ref[i]) + 1e-3);
        if(rel_err < tmp_rel_err) {
            #pragma omp critical
            {
                rel_err = tmp_rel_err;
                pos_i = i;
                ref_val = ref[i];
                arr_val = arr[i];
            }
        }
        
    } 
    printf("total error: %.6lf, total sum: %.6lf, relative error: %.6lf, pos: %u, ref: %lf, target: %lf\n", err, sum, rel_err, pos_i, ref_val, arr_val);
}


#if defined(__ARM_FEATURE_SME)
int main(int argc, char** argv)__arm_streaming
#else
int main(int argc, char** argv)
#endif
{
    assert(argc == 4);
    int nx = atoi(argv[1]);
    int ny = atoi(argv[2]);
    int nz = atoi(argv[3]);
    // int nx = 512;
    // int ny = 512;
    // int nz = 512;
    int n_threads = omp_get_max_threads();
    printf("test RTM TTI kernel under grid size: (%d, %d, %d), maximum number of threads: %d\n", nx, ny, nz, n_threads);

    printf("\n-------------------- Initalizing Sandbox --------------------\n\n");
    int nPad = 4;
    int stncilsiz = 9;
    int nxf = nx + 2*nPad;
    int nyf = ny + 2*nPad;
    int nzf = nz + 2*nPad;

    float * v = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * delta = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * e = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * dip_x = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * dip_y = (float*)malloc(sizeof(float)*nxf*nyf*nzf);

    float * u1 = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * u2 = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * u3 = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * q1 = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * q2 = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * q3 = (float*)malloc(sizeof(float)*nxf*nyf*nzf);

    float * u3_ref = (float*)malloc(sizeof(float)*nxf*nyf*nzf);
    float * q3_ref = (float*)malloc(sizeof(float)*nxf*nyf*nzf);

    float * z_fdcoef_1st = (float*)malloc(sizeof(float)*stncilsiz*nzf);
    float * z_fdcoef = (float*)malloc(sizeof(float)*stncilsiz*nzf);

    float * uxx = (float*)malloc(sizeof(float)*(stncilsiz*nxf*BLOCK_SIZE + 8*nxf)*n_threads);
    float * uzz = (float*)malloc(sizeof(float)*(stncilsiz*nxf*BLOCK_SIZE + 8*nxf)*n_threads);
    struct RTMIG_THRD thrd_param[n_threads];
    struct RTMIG_THRD thrd_ref_param[n_threads];
    for(int i = 0; i < n_threads; i++) {
        thrd_param[i].size = 1;
        thrd_param[i].rank = 0;
        thrd_param[i].n_threads = n_threads;
        thrd_param[i].i_thread = i;

        thrd_param[i].nPad = nPad;
        thrd_param[i].nxf = nxf;
        thrd_param[i].nyf = nyf;
        thrd_param[i].nz_node = nz;
        thrd_param[i].nz_node_last = nz;

        thrd_param[i].Fda_dx = 1.0f;
        thrd_param[i].Fda_dy = 2.0f;
        thrd_param[i].angle = 0.5f;

        thrd_param[i].v = v;
        thrd_param[i].delta = delta;
        thrd_param[i].e = e;
        thrd_param[i].dip_x = dip_x;
        thrd_param[i].dip_y = dip_y;

        thrd_param[i].u1 = u1;
        thrd_param[i].u2 = u2;
        thrd_param[i].u3 = u3;
        thrd_param[i].q1 = q1;
        thrd_param[i].q2 = q2;
        thrd_param[i].q3 = q3;

        thrd_param[i].z_fdcoef_1st = z_fdcoef_1st;
        thrd_param[i].z_fdcoef = z_fdcoef;
    }

    for(int i = 0; i < n_threads; i++) {
        thrd_ref_param[i] = thrd_param[i];
        thrd_ref_param[i].u3 = u3_ref;
        thrd_ref_param[i].q3 = q3_ref;
        thrd_ref_param[i].uxx = uxx;
        thrd_ref_param[i].uzz = uzz;
    }

    printf("\n-------------------- Random Initalizing Grid Variables --------------------\n\n");
    fast_randomize(v, (size_t)nxf*nyf*nzf);
    fast_randomize(delta, (size_t)nxf*nyf*nzf);
    fast_randomize(e, (size_t)nxf*nyf*nzf);
    fast_randomize(dip_x, (size_t)nxf*nyf*nzf);
    fast_randomize(dip_y, (size_t)nxf*nyf*nzf);

    fast_randomize(u1, (size_t)nxf*nyf*nzf);
    fast_randomize(u2, (size_t)nxf*nyf*nzf);
    memset(u3, 0, sizeof(float)*nxf*nyf*nzf);
    fast_randomize(q1, (size_t)nxf*nyf*nzf);
    fast_randomize(q2, (size_t)nxf*nyf*nzf);
    memset(q3, 0, sizeof(float)*nxf*nyf*nzf);

    memset(u3_ref, 0, sizeof(float)*nxf*nyf*nzf);
    memset(q3_ref, 0, sizeof(float)*nxf*nyf*nzf);

    fast_randomize(z_fdcoef_1st, (size_t)stncilsiz*nzf);
    fast_randomize(z_fdcoef, (size_t)stncilsiz*nzf);
    for(int k = 0; k < nzf; k++) {
        z_fdcoef_1st[k*stncilsiz + nPad] = 0.0f;
    }

    printf("\n-------------------- Run Native TTI --------------------\n\n");
    double native_time = time_func([&](){
        pthread_t thr_id[n_threads];
        for(int i = 0; i < n_threads; i++) {
            pthread_attr_t att;
            pthread_attr_init(&att);
            pthread_attr_setscope(&att, PTHREAD_SCOPE_SYSTEM);
            pthread_create(&thr_id[i], &att, rtm3_update_3d_tti_pthread, (void*)&thrd_ref_param[i]);
            pthread_attr_destroy(&att);
        }
        for(int i = 0; i < n_threads; i++) {
            pthread_join(thr_id[i], 0);
        }
    });
    printf("\tnative tti function time cost: %.6lfs\n", native_time);

    printf("\n-------------------- Run Optimized TTI --------------------\n\n");
    printf("\t TTI version: %s\n", func_name);
    rtm3_initalize((void*)&thrd_param[0]);
    double optim_time = time_func([&](){
        rtm3_update_3d_tti_omp((void*)&thrd_param[0]);
    });
    printf("\toptimized tti function time cost: %.6lfs\n", optim_time);
    rtm3_finalized((void*)&thrd_param[0]);
    printf("\n-------------------- Check Result --------------------\n\n");
    printf("checking q: "); check_result(q3, q3_ref, (size_t)nxf*nyf*nzf);
    printf("checking u: "); check_result(u3, u3_ref, (size_t)nxf*nyf*nzf);
    
    
    return 0;
}
