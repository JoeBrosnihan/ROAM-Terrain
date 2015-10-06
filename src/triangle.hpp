#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vec3.hpp"

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
}

#endif
