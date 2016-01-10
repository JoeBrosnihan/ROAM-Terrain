#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <tuple>
#include <functional>
#include <utility>
#include <cstddef>

#include "vec3.hpp"

#define MAX_ORTH_LIST_LEN 10
#define DATA_LEN ((4 + 2 * MAX_ORTH_LIST_LEN) + 7) / 8
#define OFFSET_BASIS 2166136261
#define FNV_PRIME 16777619


namespace packedlpt {

//A code that describes a triangle
struct lptcode {
	//the length of the simplex code
	uint8_t len_p;

	//transform is 1,2 if bit0 is 0; 2,1 if bit0 is 1
	//first entry of transform is positive iff bit1 is 0
	//second entry ... bit2
	//starting with bit4, every two bits store the sign of the orthant's
		//x and y coordinates respectively. 0 means positive, 1 negative.

	//The tail of data must be zeroed out.
	uint8_t data[DATA_LEN];

	bool operator==(const struct lptcode &rhs) const {
		if (len_p != rhs.len_p)
			return false;
		for (int i = 0; i < DATA_LEN; i++) {
			if (data[i] != rhs.data[i])
				return false;
		}
		return true;
	}
};

struct LPTHasher {
	size_t operator()(const struct lptcode &lpt) const {
		size_t hash = OFFSET_BASIS;
		hash ^= lpt.len_p;
		hash *= FNV_PRIME;

		for (int i = 0; i < DATA_LEN; i++) {
			hash ^= lpt.data[i];
			hash *= FNV_PRIME;
		}
		return hash;
	}
};

//Computes the orthant of a given permutation
//uses 3 bits stored in permutation
//the lowest two bits of the return value hold the orthant.
uint8_t compute_orthant(uint8_t permutation);

//Computes the 0 or 1 child of the given lpt
//Return true iff the child's orthant list does not exceed the max length
bool child_lpt(struct lptcode *result, const struct lptcode &lpt, int child);

//Computes the neighbor N(neighbor)(lpt)
bool neighbor_lpt(struct lptcode *result, const struct lptcode &lpt, int neighbor);

//Computes the parent simplex
//Returns false if lpt is a root simplex
bool parent_lpt(struct lptcode *result, const struct lptcode &lpt);

//Computes the vertices of the given simplex within the unit square
//The vertices are stored in the float arrays, v0, v1, and v2 each of length 2.
void get_vertices(float *v0, float *v1, float *v2, const struct lptcode &lpt);

//Returns 0 or 1 if lpt is a 0 or 1 child simplex respectively
//lpt must not be a root simplex.
int childtype_lpt(const struct lptcode &lpt);

}

#endif
