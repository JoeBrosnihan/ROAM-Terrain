
#include "roam.hpp"

inline bool edges_equivalent(vec3 a1, vec3 a2, vec3 b1, vec3 b2) {
	return (a1 == b1 && a2 == b2) || (a1 == b2 && a2 == b1);
}

ROAMImpl::update_priority(struct tri &triangle) {
	//Update the triangle's priority based on error metrics
}

ROAMImpl::add_active_tri(const struct tri *triangle) {
	active_triangles.push(triangle);
}

ROAMImpl::remove_active_tri(const struct tri *triangle) {
	//Remove triangle from active triangles vector
	//No need to remove from priority queue
}

//Build a new split queue from the active triangles
ROAMImpl::construct_split_queue() {
	//First, clear the queue in a memory-safe way
	//clear priority_queue
	
	for (std::vector<struct tri>::size_type i = 0; i < active_triangles.size(); i++) {
		priority_queue.push(active_triangles[i]);
	}
}

ROAMImpl::force_split(const struct tri *triangle) {
	remove_active_tri(triangle);

	//There will always be an adjacent triangle that needs to be split.
	//Get the adjacent triangle.
	struct tri *adjacent_triangle;

	if (edges_equivanelt(triangle->v0, triangle->v1, adjacent_triangle->v0,
			adjacent_triangle->v1) {
		//Single split, no recursion
	} else {
		//Recursively split
		force_split(adjacent_triangle);
		
		//Then do a single split on the new adjacent triangle.
		//Exactly one split here is always required.
	}
}

