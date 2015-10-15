#ifndef ROAM_HPP
#define ROAM_HPP

#include <queue>

class ROAMImpl {
	public:
	private:
		//Store all triangles
		std::vector<struct tri> all_triangles;
		
		//Store only triangles currently rendered
		std::vector<struct tri*> active_triangles;
		
		//Split lowest priority triangle in the split_queue
		//Initialize queue with a comparator that compares triangle priority
		std::priority_queue<struct tri*> split_queue; //TODO Make comparator
		
		void update_priority(struct tri &triangle);
		void add_active_tri(const struct tri &triangle);
		void remove_active_tri(const struct tri &triangle);
		//Build a new split queue from the active triangles
		void construct_split_queue();
		//Split a single triangle
		void single_split(const struct tri &triangle);
		//Recursively split a triangle
		void force_split(const struct tri &triangle);
};

#endif
