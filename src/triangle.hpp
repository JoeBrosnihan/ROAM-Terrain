#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <tuple>
#include <functional>
#include <utility>
#include <cstddef>

#include "vec3.hpp"

#define MAX_ORTH_LIST_LEN 10

struct tri {
	//Vertices with counter-clockwise winding
	//va is opposite to the hypotenuse.
	vec3 va, v0, v1;
	//Left and right subtriangles
	struct tri *tri0, *tri1;
	//Priority metric (ammount of error)
	float priority;

	//Triangle comparison for priority_gueues
	inline bool operator<(struct tri other_tri) {
		if (priority < other_tri.priority)
			return true;
		else
			return false;
	}
};

//A code that describes a triangle
struct lptcode {
	//The length of the simplex code	
	int len_p;
	//l = |p| mod d, the simplex's level
	int l;
	//TODO Permutation
	int permutation[2];
	//list of orthants (always +/-1, +/-1)
	//n orthants = floor(|p| / 2)
	int orthant_list[MAX_ORTH_LIST_LEN * 2];

	bool operator==(const struct lptcode &rhs) const {
		bool equal = (len_p == rhs.len_p) && (permutation[0]
				== rhs.permutation[0]) && (permutation[1]
				== rhs.permutation[1]);
		if (!equal)
			return false;
		int n_orthants = len_p / 2;
		for (int i = 0; i < n_orthants; i++) {
			equal = (orthant_list[2 * i] ==
					rhs.orthant_list[2 * i]) &&
					(orthant_list[2 * i + 1] ==
					rhs.orthant_list[2 * i + 1]);
			if (!equal)
				return false;
		}
		return true;
	}
};

struct LPTHasher {
	size_t operator()(const struct lptcode &lpt) const {
		size_t hash = 0;
		hash += std::hash<int>()(lpt.len_p);
		return hash;
	}
};

//Computes the orthant of a given permutation and stores it in the result array
//result must have space for 2 integers.
void compute_orthant(int *result, int *permutation);

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

#endif
