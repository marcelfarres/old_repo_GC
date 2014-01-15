#include "Octree.h"


Octree::Octree(const std::vector<triangle> t) : triangles(t){
	max_depth = 8;
	max_tri = 10;

}

void Octree::make_root() {

	triangle_references.reserve(triangles.size());
	for (unsigned i = 0; i < triangles.size(); i++) {
		triangle_references.push_back(i);
	}
	parent = this;
}

void Octree::build_octree(){

}

Octree::~Octree(){

}
