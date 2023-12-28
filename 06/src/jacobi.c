#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include "jacobi.h"

// Uncomment the following line to enable twofold unrolling
#define JACOBI_UNROLLING 4
#define BLOCKING_FACTOR 64

#define BLOCKING_FACTOR_Y 50
#define BLOCKING_FACTOR_X 768

void jacobi(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{
// TODO implement
#ifdef JACOBI_UNROLLING

#if JACOBI_UNROLLING == 2
    // debugger: printf("JACOBI_FACTOR = TWO\n");
    for (uint32_t i = 1; i < y - 1; ++i)
    {

#pragma novector
#pragma nounroll
        for (uint32_t j = 1; j < x - 1; j += JACOBI_UNROLLING)
        {
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
    // debugger: printf("JACOBI_FACTOR = FOUR\n");
    for (uint32_t i = 1; i < y - 1; ++i)
    {

#pragma novector
#pragma nounroll
        for (uint32_t j = 1; j < x - 1; j += JACOBI_UNROLLING)
        {

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

    /*
                //debugger: printf("JACOBI_FACTOR = FOUR\n");
                for(uint32_t i = 1; i < y - 1; ++i) {

                    #pragma novector
                    #pragma nounroll
                    for(uint32_t j = 1; j < x - 1; j+=JACOBI_UNROLLING) {
                         grid_target[x * i + j] = 0.25 * (
                                grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                            );
                        grid_target[x * i + (j+1)] = 0.25 * (
                                grid_source[x * i + (j)] + grid_source[x * i + (j + 2)] +
                                grid_source[x * (i - 1) + (j+1)] + grid_source[x * (i + 1) + (j+1)]
                            );

                        grid_target[x * i + (j+2)] = 0.25 * (
                                grid_source[x * i + (j+1)] + grid_source[x * i + (j + 3)] +
                                grid_source[x * (i - 1) + (j+2)] + grid_source[x * (i + 1) + (j+2)]
                            );
                        grid_target[x * i + (j+3)] = 0.25 * (
                                grid_source[x * i + (j+2)] + grid_source[x * i + (j + 4)] +
                                grid_source[x * (i - 1) + (j+3)] + grid_source[x * (i + 1) + (j+3)]
                            );

                    }
                }
                */
#else
    // debugger: printf("JACOBI_FACTOR = ONE\n");
    for (uint32_t i = 1; i < y - 1; ++i)
    {

        // #pragma novector
        // #pragma nounroll
        for (uint32_t j = 1; j < x - 1; ++j)
        {
            grid_target[x * i + j] = 0.25 * (grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                             grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]);
        }
    }

#endif

#else

    for (uint32_t i = 1; i < y - 1; ++i)
    {

        // #pragma novector
        // #pragma nounroll
        for (uint32_t j = 1; j < x - 1; ++j)
        {
            grid_target[x * i + j] = 0.25 * (grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                             grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]);
        }
    }

#endif
}

void jacobi_column_wise(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{

#ifdef JACOBI_UNROLLING

#if JACOBI_UNROLLING == 2
    // debugger: printf("JACOBI_FACTOR = TWO\n");
    for (uint32_t i = 1; i < x - 1; ++i)
    {

#pragma novector
#pragma nounroll
        for (uint32_t j = 1; j < y - 1; j += JACOBI_UNROLLING)
        {
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
    // debugger: printf("JACOBI_FACTOR = FOUR\n");
    for (uint32_t i = 1; i < x - 1; ++i)
    {

#pragma novector
#pragma nounroll
        for (uint32_t j = 1; j < y - 1; j += JACOBI_UNROLLING)
        {

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
    // debugger: printf("JACOBI_FACTOR = ONE\n");
    for (uint32_t i = 1; i < x - 1; ++i)
    {

        // #pragma novector
        // #pragma nounroll
        for (uint32_t j = 1; j < y - 1; ++j)
        {
            grid_target[x * i + j] = 0.25 * (grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                             grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]);
        }
    }

#endif

#else

    for (uint32_t i = 1; i < x - 1; ++i)
    {

        // #pragma novector
        // #pragma nounroll
        for (uint32_t j = 1; j < y - 1; ++j)
        {
            grid_target[x * i + j] = 0.25 * (grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                             grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]);
        }
    }

#endif
}

void jacobi_spatial_blocking(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{

    for (uint32_t i = 1; i < y - 1; ++i)
    {
        for (uint32_t j = 1; j < x - 1; j += BLOCKING_FACTOR)
        {
#pragma novector
#pragma nounroll
            for (uint32_t k = 0; k < BLOCKING_FACTOR; k += JACOBI_UNROLLING)
            {
                uint32_t offset = j + k;

                // Load data using AVX
                __m256d top_point = _mm256_loadu_pd(&grid_source[x * (i - 1) + offset]);
                __m256d bottom_point = _mm256_loadu_pd(&grid_source[x * (i + 1) + offset]);

                __m256d left_point = _mm256_loadu_pd(&grid_source[x * i + (offset - 1)]);
                __m256d right_point = _mm256_loadu_pd(&grid_source[x * i + (offset + 1)]);

                // Perform the Jacobi computation and store the results at different offsets
                _mm256_storeu_pd(&grid_target[x * i + offset], _mm256_mul_pd(
                                                                   _mm256_add_pd(top_point, bottom_point) + _mm256_add_pd(left_point, right_point),
                                                                   _mm256_set1_pd(0.25)));
            }
        }
    }

    /*
    for (uint32_t i = 1; i < y - 1; ++i) {
            for (uint32_t j = 1; j < x - 1; j += BLOCKING_FACTOR) {
                #pragma novector
                #pragma nounroll
                for (uint32_t k = 0; k < BLOCKING_FACTOR; k += JACOBI_UNROLLING) {
                    uint32_t offset1 = j + k;
                    uint32_t offset2 = offset1 + 1;
                    uint32_t offset3 = offset1 + 2;
                    uint32_t offset4 = offset1 + 3;

                    grid_target[x * i + offset1] = 0.25 * (
                        grid_source[x * i + (offset1 - 1)] + grid_source[x * i + (offset1 + 1)] +
                        grid_source[x * (i - 1) + offset1] + grid_source[x * (i + 1) + offset1]
                    );

                    grid_target[x * i + offset2] = 0.25 * (
                        grid_source[x * i + (offset2 - 1)] + grid_source[x * i + (offset2 + 1)] +
                        grid_source[x * (i - 1) + offset2] + grid_source[x * (i + 1) + offset2]
                    );

                    grid_target[x * i + offset3] = 0.25 * (
                        grid_source[x * i + (offset3 - 1)] + grid_source[x * i + (offset3 + 1)] +
                        grid_source[x * (i - 1) + offset3] + grid_source[x * (i + 1) + offset3]
                    );

                    grid_target[x * i + offset4] = 0.25 * (
                        grid_source[x * i + (offset4 - 1)] + grid_source[x * i + (offset4 + 1)] +
                        grid_source[x * (i - 1) + offset4] + grid_source[x * (i + 1) + offset4]
                    );
                }
            }
        }
    */
}



/*void jacobi_L1_prefetch_blocking(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{
    for (uint32_t i = 1; i < y - 1; i += BLOCKING_FACTOR_Y)
    {
        for (uint32_t outer = 1; outer < BLOCKING_FACTOR_Y; outer++)
        {
            for (uint32_t j = 1; j < x - 1; j += BLOCKING_FACTOR_X)
            {
                #pragma novector
                #pragma nounroll
                for (uint32_t k = 0; k < BLOCKING_FACTOR_X; k += JACOBI_UNROLLING)
                {
                    uint32_t offset = j + k;

                    // Load data using AVX with boundary checks
                    __m256d top_point = (i > 0) ? _mm256_loadu_pd(&grid_source[x * (i - 1) + offset]) : _mm256_setzero_pd();
                    __m256d bottom_point = (i < y - 1) ? _mm256_loadu_pd(&grid_source[x * (i + 1) + offset]) : _mm256_setzero_pd();
                    __m256d left_point = (offset > 0) ? _mm256_loadu_pd(&grid_source[x * i + (offset - 1)]) : _mm256_setzero_pd();
                    __m256d right_point = (offset < x - 1) ? _mm256_loadu_pd(&grid_source[x * i + (offset + 1)]) : _mm256_setzero_pd();

                    // Perform the Jacobi computation and store the results at different offsets
                    __m256d result1 = _mm256_add_pd(top_point, bottom_point);
                    __m256d result2 = _mm256_add_pd(left_point, right_point);
                    __m256d result3 = _mm256_add_pd(result1, result2);

                    _mm256_storeu_pd(&grid_target[x * i + offset], _mm256_mul_pd(result3, _mm256_set1_pd(0.25)));
                }
            }
        }
    }
}
*/

void jacobi_L1_prefetch_blocking(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{
    for (uint32_t i = 1; i < y - 1; i += BLOCKING_FACTOR_Y)
    {
        for (uint32_t outer = 1; outer < BLOCKING_FACTOR_Y; outer++)
        {
            for (uint32_t j = 1; j < x - 1; j += BLOCKING_FACTOR_X)
            {
                #pragma novector
                #pragma nounroll
                for (uint32_t k = 0; k < BLOCKING_FACTOR_X; k += JACOBI_UNROLLING)
                {
                    uint32_t offset_xaxis = j + k;
                    uint32_t offset_yaxis = i + outer;

                    // Load data using AVX
                    __m256d top_point = _mm256_loadu_pd(&grid_source[x * (offset_yaxis - 1) + offset_xaxis]);
                    __m256d bottom_point = _mm256_loadu_pd(&grid_source[x * (offset_yaxis + 1) + offset_xaxis]);

                    __m256d left_point = _mm256_loadu_pd(&grid_source[x * offset_yaxis + (offset_xaxis - 1)]);
                    __m256d right_point = _mm256_loadu_pd(&grid_source[x * offset_yaxis + (offset_xaxis + 1)]);

                    // Perform the Jacobi computation and store the results at different offsets
                    __m256d result1 = _mm256_add_pd(top_point, bottom_point);
                    __m256d result2 = _mm256_add_pd(left_point, right_point);
                    __m256d result3 = _mm256_add_pd(result1, result2);

                    _mm256_storeu_pd(&grid_target[x * offset_yaxis + offset_xaxis], _mm256_mul_pd(result3, _mm256_set1_pd(0.25)));
                }
            }
        }
    }
}


