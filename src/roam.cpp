
#include "roam.hpp"

//child = 0 or 1
struct lptcode get_subtriangle(const struct &lpt, int child) {
	struct lptcode child_lpt;
	child_lpt.len_p = lpt.len_p++;
	child_lpt.l = (lpt.l + 1) % 2;
	if (child == 0) {
		//inherit permutation
		child_lpt.permutation[0] = lpt.permutation[0];
		child_lpt.permutation[1] = lpt.permutation[1];
	} else { //child = 1
		//TODO Need help with this
		//What is Pi of Sigma l on p7
	}
	if (child_lpt.l == 0) {
		//TODO add orth(permutation) to the orthant list
	}
	return child_lpt;
}

ROAMImpl::add_active_lpt(const struct lptcode &lpt) {
	active_lpts[lpt] = lpt;
	//No need to add to priority queue here - it is rebuilt every frame
}

ROAMImpl::remove_active_lpt(const struct lptcode &lpt) {
	active_lpts.erase(lpt);
	//No need to remove from priority queue
}

//Build a new split queue from the active triangles
ROAMImpl::construct_split_queue() {
	//TODO implement
}

ROAMImpl::single_split(const struct lptcode &lpt) {
	remove_active_lpt(lpt);

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

