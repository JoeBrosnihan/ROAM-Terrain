
#include "roam.hpp"

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
//	active_lpts[lpt] = lpt;
	//No need to add to priority queue here - it is rebuilt every frame
};

void ROAMImpl::remove_active_lpt(const struct lptcode &lpt) {
//	active_lpts.erase(lpt);
	//No need to remove from priority queue
};

//Build a new split queue from the active triangles
void ROAMImpl::construct_split_queue() {
	//TODO implement
};

void ROAMImpl::single_split(const struct lptcode &lpt) {
	remove_active_lpt(lpt);

/*	TODO implement with lpts
	add_active_tri(triangle->tri0);
	priority_queue.push(triangle->tri0);

	add_active_tri(triangle->tri1);
	priority_queue.push(triangle->tri1);
*/
};

void ROAMImpl::force_split(const struct lptcode &lpt) {
	remove_active_lpt(lpt);
	//TODO implement
};

