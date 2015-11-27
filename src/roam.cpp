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

void ROAMImpl::single_split(const struct lptcode &lpt) {
	//TODO handle hitting max lod
	int n_orthants = lpt.len_p / 2;
	int new_len = lpt.len_p + 1;

	struct lptcode sub0;
	sub0.len_p = new_len;
	sub0.l = new_len % 2;
	sub0.permutation[0] = lpt.permutation[0];
	sub0.permutation[1] = lpt.permutation[1];
	memcpy(sub0.orthant_list, lpt.orthant_list,
			sizeof(int) * n_orthants * 2);
	if (sub0.l == 0)
		compute_orthant(sub0.orthant_list + n_orthants * 2,
				sub0.permutation);

	struct lptcode sub1;
	sub1.len_p = new_len;
	sub1.l = new_len % 2;
	if (lpt.l == 0) {
		sub1.permutation[0] = -lpt.permutation[1];
		sub1.permutation[1] = lpt.permutation[0];
	} else {
		sub1.permutation[0] = lpt.permutation[0];
		sub1.permutation[1] = -lpt.permutation[1];
	}
	memcpy(sub1.orthant_list, lpt.orthant_list,
			sizeof(int) * n_orthants * 2);
	if (sub1.l == 0)
		compute_orthant(sub1.orthant_list + n_orthants * 2,
				sub1.permutation);
	
	remove_active_lpt(lpt);
	add_active_lpt(sub0);
	add_active_lpt(sub1);
};

void ROAMImpl::force_split(const struct lptcode &lpt) {
	remove_active_lpt(lpt);
	//TODO implement
};

