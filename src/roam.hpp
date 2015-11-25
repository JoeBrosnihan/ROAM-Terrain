#ifndef ROAM_HPP
#define ROAM_HPP

#include <queue>
#include <unordered_map>

#include "triangle.hpp"

class ROAMImpl {
	public:
		//Store only triangles currently rendered
		std::vector<struct lptcode> active_triangles;
		
	private:
		//Store all active lptcodes
		std::unordered_map<struct lptcode, struct lptcode, LPTHasher>
				active_lpts;

		//Split lowest priority triangle in the split_queue
		//Initialize queue with a comparator that compares triangle priority
		std::priority_queue<struct lptcode> split_queue; //TODO Make comparator
		
		void add_active_lpt(const struct lptcode &lpt);
		void remove_active_lpt(const struct lptcode &lpt);
		//Build a new split queue from the active triangles
		void construct_split_queue();
		//Split a single triangle
		void single_split(const struct lptcode &lpt);
		//Recursively split a triangle
		void force_split(const struct lptcode &lpt);
};

#endif
