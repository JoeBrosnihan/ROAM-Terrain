#include "triangle.hpp"

#include <utility>


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

struct lptcode neighbor(const struct lptcode &lpt, int neighbor) {
	struct lptcode result; //Perhaps storing in a result ptr is better than returning.

	int lminus = (lpt.l - 1) % 2;
	int lstar = lminus + 1;

	//if lpt is a 0-child
		if (neighbor == 0) {
			result.permutation[0] = -lpt.permutation[0];
			result.permutation[1] = lpt.permutation[1];
		} else if (neighbor == 1) {
			result.permutation[0] = lpt.permutation[1];
			result.permutation[1] = lpt.permutation[0];
		} else if (neighbor == 2) {
			//not used
		}
	//else if lpt is a 1-child
		if (neighbor == 0) {
			result.permutation[0] = -lpt.permutation[0];
			result.permutation[1] = lpt.permutation[1];
		} else if (neighbor == 2) {

		} else if (neighbor == 2) {
			//not used
		}

	if (neighbor == 0) {
		
	} else if (lpt.l == 1) {
		if (neighbor == 1) {
			//same orth list
		} else if (neighbor == 2) {
			//same orth list up to last orth
		}
	}

	return result;
}

