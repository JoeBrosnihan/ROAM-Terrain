
#include "plot.hpp"

#include <iostream>
#include <fstream>

#include "triangle.hpp"

#define SHOW_PERMUTATIONS true

Plot::Plot(string filename) {
	plotfile.open(filename, ios::out | ios::trunc);
	plotfile << "\n\
	<!DOCTYPE HTML>\n\
	<html>\n\
		<head>\n\
			<script>\n\
				function display() {\n\
					var canvas = document.getElementById('plotcanvas');\n\
					var ctx = canvas.getContext('2d');\n\
	";
}

void Plot::draw_triangle(const struct lptcode &lpt) {
	float v0[2];
	float v1[2];
	float v2[2];
	get_vertices(v0, v1, v2, lpt);
	plotfile << "\n\
		ctx.beginPath();\n\
		ctx.moveTo(" << (v0[0] * .5f + .5f) * width << ", " << (.5f - v0[1] * .5f) * height << ");\n\
		ctx.lineTo(" << (v1[0] * .5f + .5f) * width << ", " << (.5f - v1[1] * .5f) * height << ");\n\
		ctx.lineTo(" << (v2[0] * .5f + .5f) * width << ", " << (.5f - v2[1] * .5f) * height << ");\n\
		ctx.closePath();\n\
		ctx.stroke();\n\
	";
	if (SHOW_PERMUTATIONS) {
		float cx = (v0[0] + v1[0] + v2[0]) / 3.f;
		float cy = (v0[1] + v1[1] + v2[1]) / 3.f;
		plotfile << "\n\
		ctx.fillText(\"" << childtype_lpt(lpt) << " [" << lpt.permutation[0] << ", " << lpt.permutation[1] << "]\", " << (cx * .5f + .5f) * width << ", " << (.5f - cy * .5f) * height << ");\n";
	}
}

void Plot::draw_active_lpts(ROAMImpl &roam) {
	for (size_t i = 0; i < roam.active_triangles.size(); i++) {
		draw_triangle(roam.active_triangles[i]);
	}
}

void Plot::setColor(std::string color) {
	plotfile << "\n\
		ctx.strokeStyle = '" << color << "';\n\
		ctx.fillStyle = '" << color << "';\n";
}

void Plot::finish() {
	plotfile << "\n\
				}\n\
			</script>\n\
		</head>\n\
		<body onload=\"display();\">\n\
			<canvas id=\"plotcanvas\"\n\
				width=\"" << width << "px\"\n\
				height=\"" << height << "px\">\n\
			</canvas>\n\
		</body>\n\
	</html>\n\
	";
	plotfile.close();
}

