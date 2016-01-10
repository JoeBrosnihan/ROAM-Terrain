#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "packed_triangle.hpp"
#include "roam.hpp"



using namespace packedlpt;

class Plot {
	public:
		Plot(std::string filename);
		void draw_triangle(const struct lptcode &lpt);
		void draw_active_lpts(ROAMImpl &roam);
		//Sets the strokestyle to the given color, specified
		//as a hex string. e.g. "#ff0000"
		void setColor(std::string color);
		void finish();
	private:
		std::ofstream plotfile;
		float width = 500.f;
		float height = 500.f;
};

