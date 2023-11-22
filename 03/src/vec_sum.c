#include <stdio.h>
#include <stdint.h>
# include <immintrin.h>
#include <xmmintrin.h>


#include "vec_sum.h"

	#define UNROLL_FACTOR 1



float vec_sum(float *array, uint32_t length) {
  
     float accumulator = 0.0f;

    // Check if unrolling is desired
    #ifdef UNROLL_FACTOR
        // Perform loop unrolling based on the specified factor
        #if UNROLL_FACTOR == 2
          float sum [2] = { 0.0f , 0.0f };
        //debugger: printf("UNROL_FACTOR!: %d (TWO) \n", UNROLL_FACTOR);
            # pragma novector
            # pragma nounroll
            for (uint32_t i = 0; i < length; i += 2) {
                sum[0] += array[i];
                sum[1] += array[i + 1];
                 
            }
        #elif UNROLL_FACTOR == 3
            float sum[3] = {0.0f, 0.0f, 0.0f};
            //debugger: printf("UNROL_FACTOR!: %d (THREE) \n", UNROLL_FACTOR);
            # pragma novector
            # pragma nounroll
            for (uint32_t i = 0; i < length; i += 3) {
                sum[0] += array[i]; 
                sum[1] += array[i + 1]; 
                sum[2] += array[i + 2];
            }
        #elif UNROLL_FACTOR == 4
            float sum[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            //debugger: printf("UNROL_FACTOR!: %d (FOUR) \n", UNROLL_FACTOR);
            # pragma novector
            # pragma nounroll
            for (uint32_t i = 0; i < length; i += 4) {
                sum[0] += array[i]; 
                sum[1] += array[i + 1]; 
                sum[2] += array[i + 2];
                sum[3] += array[i + 3];
            }
        #elif UNROLL_FACTOR == 8
            float sum = 0.0f;

            //debugger: printf("UNROL_FACTOR!: %d (EIGHT) \n", UNROLL_FACTOR);
                uint32_t remainder = length % UNROLL_FACTOR;
                __m256 result = _mm256_setzero_ps ();
                __m256 accu ;
                # pragma nounroll
                # pragma novector
                for ( uint32_t i = 0 ; i < length - remainder ; i +=8) {
                accu = _mm256_loadu_ps (& array [ i ]);
                result = _mm256_add_ps ( result , accu );
                }
                // Add result and remainder elements into ’sum ’
                 _mm256_storeu_ps(&sum, result);

                // Add remaining elements into 'sum'
                for (uint32_t i = length - remainder; i < length; ++i) {
                    sum += array[i];
                }
                
        #else
            // No unrolling
            float sum[1] = {0.0f};
            //debugger: printf("UNROL_FACTOR!: %d (NO_UNROLLING) \n", UNROLL_FACTOR);
            for (uint32_t i = 0; i < length; ++i) {
                sum[0] += array[i];
               
            }
        #endif
        

        //Merge sum parallel values
        size_t sum_length = sizeof(sum) / sizeof(sum[0]);
       

        for (uint32_t k = 0; k < sum_length; ++k) {
            accumulator += sum[k];
        }
        // Handle remainder
        for (uint32_t i = length - (length % UNROLL_FACTOR); i < length; ++i) {
            accumulator += array[i];
        }

    #else
        float sum = 0.0f;
        // No unrolling
        for (uint32_t i = 0; i < length; ++i) {
            sum += array[i];

        }
    #endif

    return accumulator;
}



//Not Mandatory Part
float two_three_four_fold_vecsum_unrol(float *array, uint32_t length) {
    // Check if unrolling is desired

        float sum = 0.0f;
        uint32_t remainder = length % UNROLL_FACTOR;
        __m128 result =  _mm_setzero_ps();
        __m128 accu ;

        #pragma unroll (UNROLL_FACTOR)
        #pragma novector
        for ( uint32_t i = 0 ; i < length - remainder ; i +=UNROLL_FACTOR) {
        accu = _mm_load_ps (& array [i]);
        result = _mm_add_ps(result, accu);
        
        }

        _mm_storeu_ps(&sum, result);

        // Add remaining elements into 'sum'
        for (uint32_t i = length - remainder; i < length; ++i) {
            sum += array[i];
        }

   
        
    return sum;
}
