
#include "packed_triangle.hpp"
#include "roam.hpp"
#include "roam_controller.hpp"
#include "plot.hpp"


using namespace packedlpt;

void print_lpt(struct lptcode &lpt) {

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
	
	plot.finish();
}

