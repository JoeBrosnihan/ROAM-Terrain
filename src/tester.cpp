
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

	struct lptcode base_simplex;
	base_simplex.len_p = 0;
	base_simplex.l = 0;
	base_simplex.permutation[0] = 1;
	base_simplex.permutation[1] = 2;
	
	roam.add_active_lpt(base_simplex);
	print_active_lpts(roam);
	printf("\n");
	roam.single_split(base_simplex);
	print_active_lpts(roam);
	printf("\n");
	roam.single_split(roam.active_triangles[0]);
	print_active_lpts(roam);
	printf("\n");
	roam.single_split(roam.active_triangles[1]);
	print_active_lpts(roam);
	printf("\n");
	roam.single_split(roam.active_triangles[3]);
	print_active_lpts(roam);
	printf("\n");

	printf("Target simplex:\n");
	struct lptcode target = roam.active_triangles[3];
	print_lpt(target);

	printf("\nNeighbor 0 simplex:\n");
	struct lptcode nbor0;
	neighbor_lpt(&nbor0, target, 0);
	print_lpt(nbor0);

	printf("Neighbor 1 simplex:\n");
	struct lptcode nbor1;
	neighbor_lpt(&nbor1, target, 1);
	print_lpt(nbor1);

	printf("Parent simplex:\n");
	struct lptcode parent;
	parent_lpt(&parent, target);
	print_lpt(parent);

	draw_active_lpts(roam, plot);
	//plot.draw_triangle(target);
	//plot.draw_triangle(nbor0);
	//plot.draw_triangle(nbor1);
	plot.finish();
}

