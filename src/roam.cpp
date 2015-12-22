#include "roam.hpp"

#include <algorithm>
#include <cstring>
#include <cassert>

#include "triangle.hpp"

/*
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
};
*/

void ROAMImpl::add_active_lpt(const struct lptcode &lpt) {
	active_triangles.push_back(lpt);
	active_lpts[lpt] = lpt;
	//No need to add to priority queue here - it is rebuilt every frame
};

void ROAMImpl::remove_active_lpt(const struct lptcode &lpt) {
	auto it = std::find(active_triangles.begin(), active_triangles.end(),
			lpt);
	assert(it != active_triangles.end());
	active_lpts.erase(lpt);
	if (it != active_triangles.end())
		active_triangles.erase(it);
	
	//TODO optimization http://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
};

//Build a new split queue from the active triangles
void ROAMImpl::construct_split_queue() {
	//TODO implement
};

bool ROAMImpl::single_split(const struct lptcode &lpt) {
	struct lptcode sub0;
	if (!child_lpt(&sub0, lpt, 0)) //Simplex is already split to maximum
		return false;
	struct lptcode sub1;
	child_lpt(&sub1, lpt, 1);
	
	remove_active_lpt(lpt);
	add_active_lpt(sub0);
	add_active_lpt(sub1);
	
	return true;
};

void ROAMImpl::force_split(const struct lptcode &lpt) {
	struct lptcode nbor; //the nbor accross 
	bool nbor_in_bounds;
	if (lpt.l == 0) {
		nbor_in_bounds = neighbor_lpt(&nbor, lpt, 1);
	} else {
		nbor_in_bounds = neighbor_lpt(&nbor, lpt, 0);
	}
	single_split(lpt);

	if (!nbor_in_bounds) //check if nbor is active
		return;
	//else check if we need a recursive split	
	if (active_lpts.count(nbor) != 0)
		single_split(nbor);
	//else check nbor parent
	struct lptcode nbor_parent;
	parent_lpt(&nbor_parent, nbor);
	if (active_lpts.count(nbor_parent) != 0) {
		//need to recursively split
		force_split(nbor_parent);
		single_split(nbor);
	}
	//else splitting has already been done
};

