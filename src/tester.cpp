
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
	printf("}\n");
}

void print_active_lpts(ROAMImpl &roam) {
	for (size_t i = 0; i < roam.active_triangles.size(); i++) {
		print_lpt(roam.active_triangles[i]);
	}
}

int main(int argc, char *argv[]) {

}

