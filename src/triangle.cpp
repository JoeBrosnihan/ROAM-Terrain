
#include "triangle.hpp"

std::tuple<float, float> get_xy_from_lpt(struct lptcode lpt) {
	
}

void compute_orthant(int *result, int *permutation) {
	//Apply the permutation transformation matrix to the orthant (1, 1).
	if (permutation[0] == 1 || permutation[1] == 1)
		result[0] = 1;
	else
		result[0] = -1;
	if (permutation[0] == 2 || permutation[1] == 2)
		result[1] = 1;
	else
		result[1] = -1;
}

