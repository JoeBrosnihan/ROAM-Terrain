
#include "packed_triangle.hpp"
#include "roam.hpp"
#include "roam_controller.hpp"
#include "plot.hpp"


using namespace packedlpt;

void print_lpt(struct lptcode &lpt) {
	std::cout << (int) lpt.len_p << " " << (int) (lpt.data[0] & 7) << " | " << (int) (lpt.data[0] >> 4) << "\n";
	std::cout << "type: " << childtype_lpt(lpt) << "\n";
	float v0[2];
	float v1[2];
	float v2[2];
	get_vertices(v0, v1, v2, lpt);
	std::cout << "(" << v0[0] << ", " << v0[1] << ")\n";
	std::cout << "(" << v1[0] << ", " << v1[1] << ")\n";
	std::cout << "(" << v2[0] << ", " << v2[1] << ")\n";
	std::cout << "\n";
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
/*
	for (size_t i = 0; i < roam.active_triangles.size(); i++) {
		if (roam.active_triangles[i].len_p < 3)
			roam.force_split(roam.active_triangles[i--]);
	}
*/
	size_t iter = 11;
	for (size_t i = 0; i < iter; i++) {
		roam.force_split(roam.active_triangles[0]);
	}

	struct lptcode lpt = roam.active_triangles[3];
	plot.setColor("#ff0000");
	plot.draw_triangle(lpt);
	struct lptcode nbor;
	neighbor_lpt(&nbor, lpt, 1);
	plot.setColor("#0000ff");
	plot.draw_triangle(nbor);
	struct lptcode parent;
	parent_lpt(&parent, nbor);
	plot.setColor("#00ff00");
	plot.draw_triangle(parent);

	//roam.force_split(roam.active_triangles[3]);

	print_active_lpts(roam);
	std::cout << "\nnbor:\n";
	print_lpt(nbor);
	std::cout << "parent:\n";
	print_lpt(parent);

	plot.setColor("#000000");
	plot.draw_active_lpts(roam);

	plot.finish();
}

