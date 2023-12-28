#include <stdio.h>
#include <stdint.h>


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
            float sum[8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            //debugger: printf("UNROL_FACTOR!: %d (EIGHT) \n", UNROLL_FACTOR);
            # pragma novector
            # pragma nounroll
            for (uint32_t i = 0; i < length; i += 8) {
                sum[0] += array[i]; 
                sum[1] += array[i + 1]; 
                sum[2] += array[i + 2];
                sum[3] += array[i + 3];

                sum[4] += array[i + 4]; 
                sum[5] += array[i + 5];
                sum[6] += array[i + 6];
                sum[7] += array[i + 7];
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
