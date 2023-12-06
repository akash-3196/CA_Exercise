#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
# include <immintrin.h>
#include <xmmintrin.h>
#include "jacobi.h"

// Uncomment the following line to enable twofold unrolling
#define JACOBI_UNROLLING 2

// Uncomment the following line to enable fourfold unrolling
// #define FOURFOLD_UNROLLING

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
    // TODO implement
    #ifdef JACOBI_UNROLLING

        #if JACOBI_UNROLLING == 2
               //debugger: printf("JACOBI_FACTOR = TWO\n");
            for(uint32_t i = 1; i < y - 1; ++i) {

                //#pragma novector
                //#pragma nounroll
                for (uint32_t j = 1; j < x - 1; j += JACOBI_UNROLLING) {
                    __m128d top_point = _mm_loadu_pd(&grid_source[x * (i - 1) + j]);
                    __m128d bottom_point = _mm_loadu_pd(&grid_source[x * (i + 1) + j]);

                    __m128d left_point = _mm_loadu_pd(&grid_source[x * i + (j - 1)]);
                    __m128d right_point = _mm_loadu_pd(&grid_source[x * i + (j + 1)]);

                    __m128d result1 = _mm_add_pd(top_point, bottom_point);
                    __m128d result2 = _mm_add_pd(left_point, right_point);

                    __m128d total_points = _mm_add_pd(result1, result2);

                    total_points = _mm_mul_pd(total_points, _mm_set1_pd(0.25));

                    _mm_storeu_pd(&grid_target[x * i + j], total_points);
                }
            }
        #elif JACOBI_UNROLLING == 4
            //debugger: printf("JACOBI_FACTOR = FOUR\n");
            for(uint32_t i = 1; i < y - 1; ++i) {

                //#pragma novector
                //#pragma nounroll
                for (uint32_t j = 1; j < x - 1; j += JACOBI_UNROLLING) {
                 
                    __m256d top_point = _mm256_loadu_pd(&grid_source[x * (i - 1) + j]);
                    __m256d bottom_point = _mm256_loadu_pd(&grid_source[x * (i + 1) + j]);

                    __m256d left_point = _mm256_loadu_pd(&grid_source[x * i + (j - 1)]);
                    __m256d right_point = _mm256_loadu_pd(&grid_source[x * i + (j + 1)]);

                    __m256d result1 = _mm256_add_pd(top_point, bottom_point);
                    __m256d result2 = _mm256_add_pd(left_point, right_point);

                    __m256d total_points = _mm256_add_pd(result1, result2);

                    total_points = _mm256_mul_pd(total_points, _mm256_set1_pd(0.25));

                    _mm256_storeu_pd(&grid_target[x * i + j], total_points);
                }
            }
         #else
        //debugger: printf("JACOBI_FACTOR = ONE\n");
            for(uint32_t i = 1; i < y - 1; ++i) {

                    //#pragma novector
                    //#pragma nounroll
                    for(uint32_t j = 1; j < x - 1; ++j) {
                        grid_target[x * i + j] = 0.25 * (
                                grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                    }
                }

         #endif

    #else 

            for(uint32_t i = 1; i < y - 1; ++i) {

                //#pragma novector
                //#pragma nounroll
                for(uint32_t j = 1; j < x - 1; ++j) {
                     grid_target[x * i + j] = 0.25 * (
                            grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                            grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                }
            }
        
    #endif
}



void jacobi_column_wise(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {

    #ifdef JACOBI_UNROLLING

        #if JACOBI_UNROLLING == 2
               //debugger: printf("JACOBI_FACTOR = TWO\n");
            for(uint32_t i = 1; i < x - 1; ++i) {

                //#pragma novector
                //#pragma nounroll
                for (uint32_t j = 1; j < y - 1; j += JACOBI_UNROLLING) {
                    __m128d top_point = _mm_loadu_pd(&grid_source[x * (i - 1) + j]);
                    __m128d bottom_point = _mm_loadu_pd(&grid_source[x * (i + 1) + j]);

                    __m128d left_point = _mm_loadu_pd(&grid_source[x * i + (j - 1)]);
                    __m128d right_point = _mm_loadu_pd(&grid_source[x * i + (j + 1)]);

                    __m128d result1 = _mm_add_pd(top_point, bottom_point);
                    __m128d result2 = _mm_add_pd(left_point, right_point);

                    __m128d total_points = _mm_add_pd(result1, result2);

                    total_points = _mm_mul_pd(total_points, _mm_set1_pd(0.25));

                    _mm_storeu_pd(&grid_target[x * i + j], total_points);
                }
            }
        #elif JACOBI_UNROLLING == 4
            //debugger: printf("JACOBI_FACTOR = FOUR\n");
            for(uint32_t i = 1; i < x - 1; ++i) {

                #pragma novector
                #pragma nounroll
                for (uint32_t j = 1; j < y - 1; j += JACOBI_UNROLLING) {
                 
                    __m256d top_point = _mm256_loadu_pd(&grid_source[x * (i - 1) + j]);
                    __m256d bottom_point = _mm256_loadu_pd(&grid_source[x * (i + 1) + j]);

                    __m256d left_point = _mm256_loadu_pd(&grid_source[x * i + (j - 1)]);
                    __m256d right_point = _mm256_loadu_pd(&grid_source[x * i + (j + 1)]);

                    __m256d result1 = _mm256_add_pd(top_point, bottom_point);
                    __m256d result2 = _mm256_add_pd(left_point, right_point);

                    __m256d total_points = _mm256_add_pd(result1, result2);

                    total_points = _mm256_mul_pd(total_points, _mm256_set1_pd(0.25));

                    _mm256_storeu_pd(&grid_target[x * i + j], total_points);
                }
            }
         #else
        //debugger: printf("JACOBI_FACTOR = ONE\n");
            for(uint32_t i = 1; i < x - 1; ++i) {

                    //#pragma novector
                    //#pragma nounroll
                    for(uint32_t j = 1; j < y - 1; ++j) {
                        grid_target[x * i + j] = 0.25 * (
                                grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                    }
                }

         #endif

    #else 

            for(uint32_t i = 1; i < x - 1; ++i) {

                //#pragma novector
                //#pragma nounroll
                for(uint32_t j = 1; j < y - 1; ++j) {
                     grid_target[x * i + j] = 0.25 * (
                            grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                            grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                }
            }
        
    #endif
        
}
