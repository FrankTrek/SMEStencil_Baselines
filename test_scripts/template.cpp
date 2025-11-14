#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <omp.h>
#include <sys/time.h>
#if defined(__AVX512F__) || defined(__AVX512__)
#include <immintrin.h>
#elif defined(__ARM_FEATURE_SVE)
#include <arm_sve.h>
#else
#include <arm_neon.h>
#endif
#if defined(__ARM_FEATURE_SME)
#include <arm_sme.h>

















#endif


static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

template<typename T>
T uniform() {
    static uint64_t s[2] = { 0x41, 0x29837592 };
    const uint64_t s0 = s[0];
    uint64_t s1 = s[1];
    const uint64_t result = s0 + s1;

    s1 ^= s0;
    s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
    s[1] = rotl(s1, 36); // c

    return result*((1.0/18446744073709551616.0));
}


#define TOT_TIME 10
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

#define min(x, y) ((x) < (y) ? (x) : (y))
#define ceil(x, y) (((x) + (y) - 1)/(y))
<INDEX MACROS>


<FUNCTIONS>



int main(int argc, char** argv) {

    assert(argc == 4);
    int nx = atoi(argv[1]);
    int ny = atoi(argv[2]);
    int nz = atoi(argv[3]);
    <EXTRA DECLARE>
    <ALLOC>

    <CHECK RESULT>

    double elapsed_time = time_func([&](){
        <BENCHMARK>
    });

    <OUTPUT>

    return 0;
}