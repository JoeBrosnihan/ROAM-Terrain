
#include "triangle.hpp"
#include "roam.hpp"
#include "plot.hpp"

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

void draw_active_lpts(ROAMImpl &roam, Plot &plot) {
	for (size_t i = 0; i < roam.active_triangles.size(); i++) {
		plot.draw_triangle(roam.active_triangles[i]);
	}
}



int main(int argc, char *argv[]) {
	ROAMImpl roam;
	Plot plot("plot.html");

	print_active_lpts(roam);
	printf("\n");

	

	draw_active_lpts(roam, plot);
	//plot.draw_triangle(target);
	//plot.draw_triangle(nbor0);
	//plot.draw_triangle(nbor1);
	plot.finish();
}

