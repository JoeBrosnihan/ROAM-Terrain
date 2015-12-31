#include "roam_controller.hpp"


bool ROAMController::single_split(const struct lptcode &lpt) {
	struct lptcode sub0;
	if (!child_lpt(&sub0, lpt, 0)) //Simplex is already split to maximum
		return false;
	struct lptcode sub1;
	child_lpt(&sub1, lpt, 1);
	
	remove_active_lpt(lpt);
	add_active_lpt(sub0);
	add_active_lpt(sub1);

	if (needs_split(sub0))
		force_split(sub0);
	if (needs_split(sub1))
		force_split(sub1);
	
	return true;
};

bool ROAMController::needs_split(const struct lptcode &lpt) {
	float v0[2];
	float v1[2];
	float v2[2];
	get_vertices(v0, v1, v2, lpt);
	float centroid_x = (v0[0] + v1[0] + v2[0]) / 3f;
	float centroid_y = (v0[1] * v1[1] * v2[1]) / 3f;
	return get_target_lod(centroid_x, centroid_y) > lpt.len_p;
}

int ROAMController::get_target_lod(float x, float y) {
	return 0;
}

