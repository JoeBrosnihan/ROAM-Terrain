#include "triangle.hpp"

#include <utility>
#include <cstdlib>
#include <cassert>
#include <cstring>

void compute_orthant(int *result, int *permutation) {
	//Apply the permutation transformation matrix to the orthant (1, 1).
	if (permutation[0] == 1 || permutation[1] == 1)
		result[0] = 1;
	else
		result[0] = -1;
	if (permutation[0] == 2 || permutation[1] == 2)
		result[1] = 1;
	else
		result[1] = -1;
}

//Returns 0 or 1 if lpt is a 0 or 1 child simplex respectively
//lpt must not be a root simplex.
int childtype_lpt(const struct lptcode &lpt) {
	int lminus = (lpt.l - 1) % 2;
	int lstar = lminus + 1;

	int pi_lstar = lpt.permutation[lstar - 1];
	int pi_lstar_sign = 1;
	if (pi_lstar < 0)
		pi_lstar_sign = -1;
	
	int n_orthants = lpt.len_p / 2;
	int last_orth_index = (n_orthants - 1) * 2;
	//lpt is a 0 child iff sign(pi[l*]) = sign(o[|pi[l*]|]) Sect 5.1 Lemma 4
	if (pi_lstar_sign == lpt.orthant_list[last_orth_index + pi_lstar * pi_lstar_sign - 1])
		return 0;
	else
		return 1;
}

bool child_lpt(struct lptcode *result, const struct lptcode &lpt, int child) {
	int new_len = lpt.len_p + 1;
	if (new_len / 2 > MAX_ORTH_LIST_LEN)
		return false;
	int n_orthants = lpt.len_p / 2;

	result->len_p = new_len;
	result->l = new_len % 2;
	if (child == 0) {
		result->permutation[0] = lpt.permutation[0];
		result->permutation[1] = lpt.permutation[1];
	} else {
		if (lpt.l == 0) {
			result->permutation[0] = -lpt.permutation[1];
			result->permutation[1] = lpt.permutation[0];
		} else {
			result->permutation[0] = lpt.permutation[0];
			result->permutation[1] = -lpt.permutation[1];
		}
	}
	memcpy(result->orthant_list, lpt.orthant_list,
			sizeof(int) * n_orthants * 2);
	if (result->l == 0)
		compute_orthant(result->orthant_list + n_orthants * 2,
				result->permutation);
	return true;
}

//returns true if neighbor exists within bounds, false otherwise
//If neighbor exists, neighbor lpt code is stored in *result.
bool neighbor_lpt(struct lptcode *result, const struct lptcode &lpt, int neighbor) {
	result->len_p = lpt.len_p;
	result->l = lpt.l;

	int lminus = (lpt.l - 1) % 2;
	int lstar = lminus + 1;
	int n_orthants = lpt.len_p / 2;

	int childtype;
	if (n_orthants > 0)
		childtype = childtype_lpt(lpt);
	else //Simplex Level is 0 or 1
		//Consider root simplex a 0 child
		//[1, 2] and [2, 1] are the only possible 0 children
		//pi[0] is negative => lpt is a 1 child
		childtype = lpt.permutation[0] < 0;
	
	//Compute neighbor permutation
	if (childtype == 0) {
		if (neighbor == 0) {
			//NEG1
			result->permutation[0] = -lpt.permutation[0];
			result->permutation[1] = lpt.permutation[1];
		} else if (neighbor == 1) {
			//SWPi
			result->permutation[0] = lpt.permutation[1];
			result->permutation[1] = lpt.permutation[0];
		} else if (neighbor == 2) {
			//not used
			assert(false);
		}
	} else if (childtype == 1) {
		if (neighbor == 0) {
			//NEG1
			result->permutation[0] = -lpt.permutation[0];
			result->permutation[1] = lpt.permutation[1];
		} else if (neighbor == lstar) {
			//cyclically shift the last d - lminus elements and
			//negate the wrap around (LFT l-)
			if (lminus == 0) {
				result->permutation[0] = lpt.permutation[1];
				result->permutation[1] = -lpt.permutation[0];
			} else {//lminus == 1
				result->permutation[0] = lpt.permutation[0];
				result->permutation[1] = -lpt.permutation[1];
			}
		} else if (neighbor == 1) { // and neighbor != l*
			//SWPi
			result->permutation[0] = lpt.permutation[1];
			result->permutation[1] = lpt.permutation[0];
		} else if (neighbor == 2) { // and neighbor != l*
			//not used
			assert(false);
		}
	}

	//Compute neighbor orthant list
	if (neighbor == 0) {
		//arbitrarily different orthant list
		int direction_axis = abs(lpt.permutation[0]);//x axis = 1, y axis = 2
		int direction_sign = 1;
		if (lpt.permutation[0] < 0)
			direction_sign = -1;

		int ancestor = n_orthants - 1;
		//back out of orthant list until you find a common ancestor
		while (ancestor >= 0) {
			//flip the orthant along the direction_axis
			result->orthant_list[2 * ancestor + direction_axis - 1]
					= -lpt.orthant_list[2 * ancestor + direction_axis - 1];
			result->orthant_list[2 * ancestor + direction_axis % 2]
					= lpt.orthant_list[2 * ancestor + direction_axis % 2];

			//check if this was the last differing orthant
			if (lpt.orthant_list[2 * ancestor + direction_axis - 1] == -direction_sign)
				break;

			ancestor--;
		}
		if (ancestor == -1) {
			//error, neighbor is outside bounds of base simplex
			return false;
		} else {
			//copy the rest of the orthants unchanged.
			for (ancestor = ancestor - 1; ancestor >= 0; ancestor--) {
				result->orthant_list[ancestor * 2] = lpt.orthant_list[ancestor * 2];
				result->orthant_list[ancestor * 2 + 1] = lpt.orthant_list[ancestor * 2 + 1];
			}
		}
	} else if (lpt.l == 1 || neighbor == 1) {
		//same orthant list
		for (int i = 0; i < n_orthants; i++) {
			result->orthant_list[2 * i] = lpt.orthant_list[2 * i];
			result->orthant_list[2 * i + 1] = lpt.orthant_list[2 * i + 1];
		}
	} else { //neighbor == 2 && l == 0
		//differ only by last orth
		if (n_orthants > 0) {
			compute_orthant(&result->orthant_list[2 * (n_orthants - 1)],
					result->permutation);
			for (int i = 0; i < n_orthants - 1; i++) {
				result->orthant_list[2 * i] = lpt.orthant_list[2 * i];
				result->orthant_list[2 * i + 1] = lpt.orthant_list[2 * i + 1];
			}
		}
	}

	return true;
}

bool parent_lpt(struct lptcode *result, const struct lptcode &lpt) {
	if (lpt.len_p == 0)
		return false;
	result->len_p = lpt.len_p - 1;
	result->l = result->len_p % 2;
	int n_orthants = result->len_p / 2;
	memcpy(result->orthant_list, lpt.orthant_list,
			sizeof(int) * n_orthants * 2);

	int childtype = childtype_lpt(lpt);

	if (childtype == 0) {
		result->permutation[0] = lpt.permutation[0];
		result->permutation[1] = lpt.permutation[1];
	} else {
		if (result->l == 0) {
			result->permutation[0] = lpt.permutation[1];
			result->permutation[1] = -lpt.permutation[0];
		} else {
			result->permutation[0] = lpt.permutation[0];
			result->permutation[1] = -lpt.permutation[1];
		}
	}

	return true;	
}

//stores [row1 row2] in the result array whith length 4
void get_perm_matrix(int *result, const struct lptcode &lpt) {
	if (lpt.permutation[0] == 1 || lpt.permutation[0] == -1) {
		//no flip about x = y
		result[0] = lpt.permutation[0]; //1 or -1
		result[1] = 0;
		result[2] = 0;
		result[3] = lpt.permutation[1] == 2 ? 1 : -1;
	} else {
		//yes flip about x = y
		result[0] = 0;
		result[1] = lpt.permutation[1];
		result[2] = lpt.permutation[0] == 2 ? 1 : -1;
		result[3] = 0;
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
		cx += lpt.orthant_list[i * 2] * scale;
		cy += lpt.orthant_list[i * 2 + 1] * scale;
	}

	int perm_matrix[4];
	get_perm_matrix(perm_matrix, lpt);
	if (lpt.l == 0) { //base simplex type 0
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

