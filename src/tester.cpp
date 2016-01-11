
#include <time.h>

#include "triangle.hpp"
#include "roam.hpp"
#include "roam_controller.hpp"
#include "plot.hpp"


#define MAX_TARGET_LOD (MAX_ORTH_LIST_LEN + 1) * 2

void print_lpt(struct lptcode &lpt) {
	printf("(len_p=%i,l=%i, perm={%i, %i}, orth={", lpt.len_p, lpt.l,
			lpt.permutation[0], lpt.permutation[1]);
	int n_orthants = lpt.len_p / 2;
	for (int i = 0; i < n_orthants; i++) {
		printf("\n(%i, %i)", lpt.orthant_list[2 * i],
				lpt.orthant_list[2 * i + 1]);
	}
	if (n_orthants != 0)
		printf("\n");
	printf("}\nvertices=[\n");
	float v0[2];
	float v1[2];
	float v2[2];
	get_vertices(v0, v1, v2, lpt);
	printf("%g %g\n%g %g\n%g %g\n", v0[0], v0[1], v1[0], v1[1], v2[0], v2[1]);
	printf("])\n");
}

void print_active_lpts(ROAMImpl &roam) {
	printf("Active triangle lptcodes:\n");
	for (size_t i = 0; i < roam.active_triangles.size(); i++) {
		print_lpt(roam.active_triangles[i]);
	}
}


class Test_Constant : public ROAMController {
	public:
		int get_target_lod(float x, float y) {
			return MAX_TARGET_LOD;
		}
};

class Test_ConstantQuadrant : public ROAMController {
	public:
		int get_target_lod(float x, float y) {
			if (x > 0 && y < 0)
				return MAX_TARGET_LOD;
			else
				return 0;
		}
};

class Test_Corner : public ROAMController {
	public:
		bool needs_split(const struct lptcode &lpt) {
			float v0[2];
			float v1[2];
			float v2[2];
			get_vertices(v0, v1, v2, lpt);
			return v2[0] >= 1 && v2[1] >= 1 && MAX_TARGET_LOD > lpt.len_p; //target lod
		}
};

int main(int argc, char *argv[]) {
	Test_Corner roam;
	Plot plot("output_plot.html");

	roam.add_base_square();

	struct timespec start;
	clock_gettime(CLOCK_MONOTONIC, &start);	
	
	roam.full_split();
	
	struct timespec finish;
	clock_gettime(CLOCK_MONOTONIC, &finish);	

	double sec = finish.tv_sec - start.tv_sec + (finish.tv_nsec - start.tv_nsec) / 1000000000.f;
	std::cout << "t = " << sec << "\n";

	plot.draw_active_lpts(roam);
	
	plot.finish();
}

