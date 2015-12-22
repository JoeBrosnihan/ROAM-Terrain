#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "triangle.hpp"

using namespace std;

class Plot {
	public:
		Plot(string filename);
		void draw_triangle(const struct lptcode &lpt);
		void finish();
	private:
		ofstream plotfile;
		float width = 500.f;
		float height = 500.f;
};

