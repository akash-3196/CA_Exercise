#include "vec_sum.h"
#include <stdint.h>
/*

float vec_sum(float *array, uint32_t length) {
	//TODO implement
	float sum = 0.0f;
	for(uint32_t i=0; i<length; ++i){
		sum += array[i];
	}
	return sum;
}
*/



float vec_sum(float *array, uint32_t length) {
    float sum = 0.0f;

    // Check if unrolling is desired
    #ifdef UNROLL_FACTOR
        // Perform loop unrolling based on the specified factor
        #if UNROLL_FACTOR == 2
            for (uint32_t i = 0; i < length; i += 2) {
                sum += array[i] + array[i + 1];
            }
        #elif UNROLL_FACTOR == 3
            for (uint32_t i = 0; i < length; i += 3) {
                sum += array[i] + array[i + 1] + array[i + 2];
            }
        #elif UNROLL_FACTOR == 4
            for (uint32_t i = 0; i < length; i += 4) {
                sum += array[i] + array[i + 1] + array[i + 2] + array[i + 3];
            }
        #elif UNROLL_FACTOR == 8
            for (uint32_t i = 0; i < length; i += 8) {
                sum += array[i] + array[i + 1] + array[i + 2] + array[i + 3] +
                       array[i + 4] + array[i + 5] + array[i + 6] + array[i + 7];
            }
        #else
            // No unrolling
            for (uint32_t i = 0; i < length; ++i) {
                sum += array[i];
            }
        #endif

        // Handle remainder
        for (uint32_t i = length - (length % UNROLL_FACTOR); i < length; ++i) {
            sum += array[i];
        }

    #else
        // No unrolling
        for (uint32_t i = 0; i < length; ++i) {
            sum += array[i];
        }
    #endif

    return sum;
}
