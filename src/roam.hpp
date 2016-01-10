#ifndef ROAM_HPP
#define ROAM_HPP

#include <queue>
#include <unordered_map>

#include "triangle.hpp"


using namespace nonpackedlpt;

class ROAMImpl {
	public:
		//Store only triangles currently rendered
		std::vector<struct lptcode> active_triangles;
		
		//Store all active lptcodes
		std::unordered_map<struct lptcode, struct lptcode, LPTHasher>
				active_lpts;

		virtual void add_active_lpt(const struct lptcode &lpt);
		void remove_active_lpt(const struct lptcode &lpt);
		//Split a single triangle
		//Returns true if the triangles was split
		//Returns false if the triangle is already maximally split
		bool single_split(const struct lptcode &lpt);
		//Recursively split a triangle
		void force_split(const struct lptcode &lpt);
		//Add two base simplices forming the unit square.
		void add_base_square();
};

#endif
