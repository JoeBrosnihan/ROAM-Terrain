#ifndef ROAM_HPP
#define ROAM_HPP

#include <queue>

class ROAMImpl {
	public:
	private:
		std::vector<struct tri> active_triangles;
		//Split lowest priority triangle in the split_queue
		//Initialize queue with a comparator that compares triangle priority
		std::priority_queue<struct tri*> split_queue;
		void update_priority(struct tri &triangle);
		void add_active_tri(const struct tri &triangle);
		void remove_active_tri(const struct tri &triangle);
		void construct_split_queue();
};

#endif
