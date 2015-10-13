#include "roam_terrain.h"

#include "triangle.hpp"
#include "roam.hpp"

//Sample the heightmap, return the float altitude;
float sample_heightmap(float heightmap[], int cols, float x, float z) {
	return 0; //TODO implement
}

//Sample the heightmap, return a vec3.
vec3 sample_heightmap_vec(float heightmap[], int cols, float x, float z) {
	vec3 sample = {x, sample_heightmap(heightmap, cols, x, z), z};
	return sample;
}

void ROAMTerrainImpl:load_heightmap(float heightmap[], int rows, int cols,
			int maxlod) {
	//Create a base triangle.
	struct tri t0;
	vec3 t0va = {0, heightmap[0], 0};
	vec3 t0v0 = {0, heightmap[cols * rows - 1], -rows};
	vec3 t0v1 = {cols, heightmap[cols - 1], 0};

	t0.priority = 0;
	t0.va = t0va;
	t0.v0 = t0v0;
	t0.v1 = t0v1;
	t0.tri0 = recursively_construct(heightmap, cols, t0.va, t0.v0,
			(t0.v0.x + t0.v1.x) * .5f, (t0.v0.z + t0.v1.z) * .5f,
			maxlod - 1);
	t0.tri1 = recursively_construct(heightmap, cols, t0.v1, t0.va,
			(t0.v0.x + t0.v1.x) * .5f, (t0.v0.z + t0.v1.z) * .5f,
			maxlod - 1);
	
	all_triangles.push(t0);

	//TODO Repeat for other triangle
}

//Creates a new triangle with verts v0, v1, and (ax, y[ax, az] az).
//Adds the triangle to all_triangles and recursively creates children.
void recursively_construct(float heightmap[], int cols, const vec3 &v0,
			const vec3 &v1, float ax, float az, int lod) {
	//Check if parent can be split. If not, stop.
	if (lod == -1)
		return NULL;
	
	//Create the triangle.
	struct tri t;
	t.priority = 0;
	t.va = sample_heightmap_vec(heightmap, cols, ax, az);
	t.v0 = v0;
	t.v1 = v1;
	t.tri0 = recursively_construct(heightmap, cols, t.va, t.v0,
			(t.v0.x + t.v1.x) * .5f, (t.v0.z + t.v1.z) * .5f,
			maxlod - 1);
	t.tri1 = recursively_construct(heightmap, cols, t.v1, t.va,
			(t.v0.x + t.v1.x) * .5f, (t.v0.z + t.v1.z) * .5f,
			maxlod - 1);

	all_triangles.push(t);
	return t;
}

