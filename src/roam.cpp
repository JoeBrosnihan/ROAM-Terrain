#include "roam.hpp"

#include <algorithm>

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
	active_lpts.erase(lpt);
	
	auto it = std::find(active_triangles.begin(), active_triangles.end(),
			lpt);
	if (it != active_triangles.end())
		active_triangles.erase(it);

	//TODO optimization http://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
/*
	for (std::vector<struct lptcode>::size_type it =
			active_triangles.begin();
			i < active_triangles.size(); i++) {
                priority_queue.push(active_triangles[i]);
        }
	//No need to remove from priority queue
*/
};

//Build a new split queue from the active triangles
void ROAMImpl::construct_split_queue() {
	//TODO implement
};

void ROAMImpl::single_split(const struct lptcode &lpt) {
	int new_len = lpt.len_p + 1;

	struct lptcode sub0;
	sub0.len_p = new_len;
	sub0.l = new_len % 2;
	sub0.permutation[0] = lpt.permutation[0];
	sub0.permutation[1] = lpt.permutation[1];
	add_active_lpt(sub0);

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
	add_active_lpt(sub1);
	
	remove_active_lpt(lpt);
};

void ROAMImpl::force_split(const struct lptcode &lpt) {
	remove_active_lpt(lpt);
	//TODO implement
};

