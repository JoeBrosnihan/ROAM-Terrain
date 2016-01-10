
#include "triangle.hpp"
#include "roam.hpp"
#include "roam_controller.hpp"
#include "plot.hpp"


using namespace nonpackedlpt;

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


class Test1 : public ROAMController {
	public:
	private:
		int get_target_lod(float x, float y) {
			if (x > 0 && y > -.4f)
				return 4;
			else
				return 0;
		}
};

int main(int argc, char *argv[]) {
	Test1 roam;
	Plot plot("output_plot.html");

	roam.add_base_square();
	roam.full_split();

	plot.draw_active_lpts(roam);
	
	struct lptcode lpt;
	lpt.len_p = 3;
	lpt.l = 1;
	lpt.permutation[0] = -1;
	lpt.permutation[1] = 2;
	lpt.orthant_list[0] = 1;
	lpt.orthant_list[1] = 1;
	plot.setColor("#ff0000");
	plot.draw_triangle(lpt);
	
	struct lptcode nbor;
	neighbor_lpt(&nbor, lpt, 0);
	plot.setColor("#00ff00");
	plot.draw_triangle(nbor);

	struct lptcode parent;
	parent_lpt(&parent, nbor);
	plot.setColor("#0000ff");
	plot.draw_triangle(parent);

	plot.finish();
}

