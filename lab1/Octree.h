#pragma once
#include <vector>
#include"ase.h"
class Octree
{
public:
	Octree::Octree(const std::vector<triangle> t);
	~Octree();
	void Octree::make_root();

	void build_octree();
private:
	int max_depth;
	int max_tri; 
	const std::vector<triangle> &triangles;
	std::vector<int> triangle_references;
	Octree* children[8];
	Octree* parent;

};

