#ifndef VEC_SUM_H
#define VEC_SUM_H

#include <stdint.h>
# include <immintrin.h>
#include <xmmintrin.h>

// Returns the sum of 'length' many array elements
// array: vector with 'length' float values
// length: length of the vector
float vec_sum(float *array, uint32_t length);

#endif
