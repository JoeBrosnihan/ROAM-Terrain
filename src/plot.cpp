
#include "plot.hpp"

#include <iostream>
#include <fstream>

#include "triangle.hpp"

Plot::Plot(string filename) {
	plotfile.open(filename, ios::out | ios::trunc);
	plotfile << "\
	<!DOCTYPE HTML>\
	<html>\
		<head>\
			<script>\
				function display() {\
					var canvas = document.getElementById('plotcanvas');\
					var ctx = canvas.getContext('2d');\
	";
}

void Plot::draw_triangle(const struct lptcode &lpt) {
	
}

void Plot::finish() {
	plotfile << "\
				}\
			</script>\
		</head>\
		<body>\
			<canvas id=\"plotcanvas\"\
				width=\"" << width << "px\"\
				height=\"" << height << "px\">\
			</canvas>\
		</body>\
	</html>\
	";
	plotfile.close();
}

