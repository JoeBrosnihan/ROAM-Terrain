#pragma once

#include "roam.hpp"

#include "triangle.hpp"

class ROAMController : ROAMImpl {
	private:
		bool needs_split(const struct lptcode &lpt);
		virtual int get_target_lod(float x, float y);
};

