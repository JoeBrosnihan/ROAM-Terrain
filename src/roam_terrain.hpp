#ifndef ROAM_TERRAIN_HPP
#define ROAM_TERRAIN_HPP

#include "roam.hpp"

//This extension of the ROAM class is specific to 
class ROAMTerrainImpl : ROAMImpl {
	public:
		//Load the mesh of a terrain from the given heightmap
		//heightmap is a cols*rows float array
		//maxlod is the max level of detail (= #lods - 1)
		void load_heightmap(float heightmap[], int cols, int rows,
				int maxlod);
	private:
}

#endif

