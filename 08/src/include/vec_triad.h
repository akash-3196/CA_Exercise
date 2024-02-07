#ifndef VEC_SUM_H
#define VEC_SUM_H

#include <stdint.h>


// Returns the sum of 'length' many array elements
// array: vector with 'length' float values
// length: length of the vector
void serial_vec_triad(float* A, float* B, float* C, float c, uint64_t vector_size);
float get_rand();

#endif
