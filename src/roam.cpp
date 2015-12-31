#include "roam.hpp"

#include <algorithm>
#include <cstring>
#include <cassert>

#include "triangle.hpp"


ROAMImpl::ROAMImpl() {
	struct lptcode base0;
        base0.len_p = 0;
        base0.l = 0;
        base0.permutation[0] = 1;
        base0.permutation[1] = 2;
	struct lptcode base1;
        base1.len_p = 0;
        base1.l = 0;
        base1.permutation[0] = 2;
        base1.permutation[1] = 1;

        add_active_lpt(base0);
        add_active_lpt(base1);
}

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

