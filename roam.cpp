
#include "roam.hpp"

ROAMImpl::update_priority(struct tri &triangle) {
	//Update the triangle's priority based on error metrics
}

ROAMImpl::add_active_tri(const struct tri &triangle) {
	active_triangles.push(triangle);
}

ROAMImpl::remove_active_tri(const struct tri &triangle) {
	//Remove triangle from active triangles vector
	//No need to remove from priority queue
}

//Build a new split queue from the active triangles
ROAMImpl::construct_split_queue() {
	//First, clear the queue in a memory-safe way
	//clear priority_queue
	
	for (std::vector<struct tri>::size_type i = 0; i < active_triangles.size(); i++) {
		priority_queue.push(&(active_triangles[i]));
	}
}

