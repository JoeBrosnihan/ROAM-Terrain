#include "packed_triangle.hpp"

#include <utility>
#include <cstdlib>
#include <cassert>
#include <cstring>


namespace packedlpt {

void compute_orthant(int *result, int *permutation) {
	//TODO implement
	result[0] = 1;
	result[1] = 1;
}

//Returns 0 or 1 if lpt is a 0 or 1 child simplex respectively
//lpt must not be a root simplex.
int childtype_lpt(const struct lptcode &lpt) {
	//TODO implement
	return 0;
}

bool child_lpt(struct lptcode *result, const struct lptcode &lpt, int child) {
	//TODO implement
	result->len_p = 0;
	for (int i = 0; i < DATA_LEN; i++) {
		result->data[i] = 0;
	}
	return true;
}

//returns true if neighbor exists within bounds, false otherwise
//If neighbor exists, neighbor lpt code is stored in *result.
bool neighbor_lpt(struct lptcode *result, const struct lptcode &lpt, int neighbor) {
	//TODO implement
	result->len_p = 0;
	for (int i = 0; i < DATA_LEN; i++) {
		result->data[i] = 0;
	}
	return true;
}

bool parent_lpt(struct lptcode *result, const struct lptcode &lpt) {
	//TODO implement
	result->len_p = 0;
	for (int i = 0; i < DATA_LEN; i++) {
		result->data[i] = 0;
	}
	return true;
}

//stores [row1 row2] in the result array whith length 4
void get_perm_matrix(int *result, const struct lptcode &lpt) {
	//TODO implement
	result[0] = 1;
	result[1] = 0;
	result[2] = 0;
	result[3] = 1;
}

//Multiplies 2x2 matrix by 2x1 vec
//Stores result. result may equal vec.
inline void multiply_2by2(float *result, int *matrix, float *vec) {
	float temp = vec[0] * matrix[0] + vec[1] * matrix[1];
	result[1] = vec[0] * matrix[2] + vec[1] * matrix[3];
	result[0] = temp;
}

void get_vertices(float *v0, float *v1, float *v2, const struct lptcode &lpt) {
	//TODO implement
	v0[0] = 0;
	v0[1] = 0;
	v1[0] = 0;
	v1[1] = 0;
	v2[0] = 0;
	v2[1] = 0;
}

}

