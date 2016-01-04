
#include "plot.hpp"

#include <iostream>
#include <fstream>

#include "triangle.hpp"

#define SHOW_PERMUTATIONS true

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
	float v0[2];
	float v1[2];
	float v2[2];
	get_vertices(v0, v1, v2, lpt);
	plotfile << "\
		ctx.beginPath();\
		ctx.moveTo(" << (v0[0] * .5f + .5f) * width << ", " << (.5f - v0[1] * .5f) * height << ");\
		ctx.lineTo(" << (v1[0] * .5f + .5f) * width << ", " << (.5f - v1[1] * .5f) * height << ");\
		ctx.lineTo(" << (v2[0] * .5f + .5f) * width << ", " << (.5f - v2[1] * .5f) * height << ");\
		ctx.closePath();\
		ctx.stroke();\
	";
	if (SHOW_PERMUTATIONS) {
		float cx = (v0[0] + v1[0] + v2[0]) / 3.f;
		float cy = (v0[1] + v1[1] + v2[1]) / 3.f;
		plotfile << "ctx.fillText(\"[" << lpt.permutation[0] << ", " << lpt.permutation[1] << "]\", " << (cx * .5f + .5f) * width << ", " << (.5f - cy * .5f) * height << ");";
	}
}

void Plot::finish() {
	plotfile << "\
				}\
			</script>\
		</head>\
		<body onload=\"display();\">\
			<canvas id=\"plotcanvas\"\
				width=\"" << width << "px\"\
				height=\"" << height << "px\">\
			</canvas>\
		</body>\
	</html>\
	";
	plotfile.close();
}

