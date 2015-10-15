
#include "roam.hpp"

inline bool edges_equivalent(vec3 a1, vec3 a2, vec3 b1, vec3 b2) {
	return (a1 == b1 && a2 == b2) || (a1 == b2 && a2 == b1);
}

ROAMImpl::update_priority(struct tri &triangle) {
	//TODO Update the triangle's priority based on error metrics
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

ROAMImpl::single_split(const struct tri *triangle) {
	remove_active_tri(triangle);
	add_active_tri(triangle->tri0);
	priority_queue.push(triangle->tri0);
	add_active_tri(triangle->tri1);
	priority_queue.push(triangle->tri1);
}

ROAMImpl::force_split(const struct tri *triangle) {
	remove_active_tri(triangle);

	//There will always be an adjacent triangle that needs to be split.
	//Get the adjacent triangle.
	struct tri *adjacent_triangle;

	//If this subtriangle is on the edge of the root triangle, don't split further
	if (adjacent_triangle == NULL)
		return;

	if (edges_equivanelt(triangle->v0, triangle->v1, adjacent_triangle->v0,
			adjacent_triangle->v1) {
		//Single split, no recursion
		single_split(adjacent_triangle);
	} else {
		//Recursively split
		force_split(adjacent_triangle);
		
		//Find the new adjacent triangle
		struct tri * new_adj;
		if (edges_equivalent(triangle->v0, triangle->v1, adjacent_triangle->v0,
				adjacent_triangle->va))
			new_adj = adjacent_triangle->tri0;
		else
			new_adj = adjacent_triangle->tri1;
		//Then do a single split on the new adjacent triangle.
		//Exactly one split here is always required.
		single_split(new_adj);
	}
}

