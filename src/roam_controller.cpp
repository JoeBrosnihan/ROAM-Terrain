#include "roam_controller.hpp"

#include <iostream>


void ROAMController::add_active_lpt(const struct lptcode &lpt) {
	std::cout << "adding lpt, needs_split = " << needs_split(lpt) << "\n";
	if (needs_split(lpt))
		needs_split_queue.push(lpt);
	ROAMImpl::add_active_lpt(lpt);
}

bool ROAMController::needs_split(const struct lptcode &lpt) {
	float v0[2];
	float v1[2];
	float v2[2];
	get_vertices(v0, v1, v2, lpt);
	float centroid_x = (v0[0] + v1[0] + v2[0]) / 3.f;
	float centroid_y = (v0[1] + v1[1] + v2[1]) / 3.f;
	return get_target_lod(centroid_x, centroid_y) > lpt.len_p;
}

int ROAMController::get_target_lod(float x, float y) {
	return 2;
}

void ROAMController::full_split() {
	std::cout << "full_split()\n";
	while (!needs_split_queue.empty()) {
		std::cout << "pop queue\n";
		if (active_lpts.count(needs_split_queue.front()) != 0)
			force_split(needs_split_queue.front());
		needs_split_queue.pop();
	}
}

