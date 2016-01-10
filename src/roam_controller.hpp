#pragma once

#include "roam.hpp"

#include <queue>

#include "packed_triangle.hpp"


using namespace packedlpt;

class ROAMController : public ROAMImpl {
	public:
		//Split simplices down to their target lods.
		void full_split();
	private:
		void add_active_lpt(const struct lptcode &lpt);
		bool needs_split(const struct lptcode &lpt);
		virtual int get_target_lod(float x, float y);
		
		std::queue<struct lptcode> needs_split_queue;
};

