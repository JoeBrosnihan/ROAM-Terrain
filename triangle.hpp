#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vec3.hpp"

struct tri {
	//Vertices with counter-clockwise winding
	//va is opposite to the hypotenuse.
	vec3 va, v0, v1;
	//Left and right subtriangles
	struct tri *tri0, *tri1;
}

#endif
