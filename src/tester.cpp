
#include "triangle.hpp"
#include "roam.hpp"

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
	printf("})\n");
}

void print_active_lpts(ROAMImpl &roam) {
	printf("Active triangle lptcodes:\n");
	for (size_t i = 0; i < roam.active_triangles.size(); i++) {
		print_lpt(roam.active_triangles[i]);
	}
}

int main(int argc, char *argv[]) {
	ROAMImpl roam;

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

	printf("Target simplex to get neighbor:\n");
	struct lptcode target = roam.active_triangles[3];
	print_lpt(target);

	printf("Neighbor 0 simplex:\n");
	struct lptcode nbor0;
	neighbor_lpt(&nbor0, target, 0);
	print_lpt(nbor0);

	printf("Neighbor 1 simplex:\n");
	struct lptcode nbor1;
	neighbor_lpt(&nbor1, target, 1);
	print_lpt(nbor1);
}

