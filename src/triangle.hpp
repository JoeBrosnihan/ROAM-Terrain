#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <tuple>
#include <functional>

#include "vec3.hpp"

#define MAX_LOD 10

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
	int orthant_list[MAX_LOD * 2];
};

struct LPTHasher {
	size_t operator()(const struct lptcode &lpt) const {
		size_t hash = 0;
		hash += std::hash<int>()(lpt.len_p);
		return hash;
	}
};

std::tuple<float, float> get_xy_from_lpt(struct lptcode lpt);

#endif
