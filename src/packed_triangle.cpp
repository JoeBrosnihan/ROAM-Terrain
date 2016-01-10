#include "packed_triangle.hpp"

#include <utility>
#include <cstdlib>
#include <cassert>
#include <cstring>


namespace packedlpt {

//Gets the bit of data at index
//returns -1 if bit is 0, 1 if bit is 1.
inline int bit_to_sign(uint8_t data, int index) {
	uint8_t bit = (data & (1 << index)) >> index;
	return bit * 2 - 1;
}

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
        if (lpt.data[0] & 1) {
                //yes flip about x = y
                result[0] = 0;
                result[1] = bit_to_sign(lpt.data[0], 2);
                result[2] = bit_to_sign(lpt.data[0], 1);
                result[3] = 0;
        } else {
                //no flip about x = y
                result[0] = bit_to_sign(lpt.data[0], 1);
                result[1] = 0;
                result[2] = 0;
                result[3] = bit_to_sign(lpt.data[0], 2);
        }
}

//Multiplies 2x2 matrix by 2x1 vec
//Stores result. result may equal vec.
inline void multiply_2by2(float *result, int *matrix, float *vec) {
	float temp = vec[0] * matrix[0] + vec[1] * matrix[1];
	result[1] = vec[0] * matrix[2] + vec[1] * matrix[3];
	result[0] = temp;
}

void get_vertices(float *v0, float *v1, float *v2, const struct lptcode &lpt) {
        int n_orthants = lpt.len_p / 2;
        float cx = 0, cy = 0;
        float scale = 1.f;
        for (int i = 0; i < n_orthants; i++) {
                scale *= .5f;
		
		uint8_t bit_index = 4 + 2 * i;
		cx += bit_to_sign(lpt.data[bit_index / 8], bit_index % 8) * scale;
		cy += bit_to_sign(lpt.data[bit_index / 8], bit_index % 8 + 1) * scale;
        }

        int perm_matrix[4];
        get_perm_matrix(perm_matrix, lpt);
        if (lpt.len_p % 2 == 0) { //base simplex type 0
                v0[0] = -scale;
                v0[1] = -scale;
        } else { //base simplex type 1
                v0[0] = 0;
                v0[1] = 0;
        }
        v1[0] = scale;
        v1[1] = -scale;
        v2[0] = scale;
        v2[1] = scale;
        multiply_2by2(v0, perm_matrix, v0);
        multiply_2by2(v1, perm_matrix, v1);
        multiply_2by2(v2, perm_matrix, v2);
        v0[0] += cx;
        v0[1] += cy;
        v1[0] += cx;
        v1[1] += cy;
        v2[0] += cx;
        v2[1] += cy;
}

}

