#pragma once
#include <vector>
#include "ase.h"
#include "box3f.h"

class OctreeNode;

class Octree {
public:
    const std::vector<triangle> &triangles;
    Octree(const CASEModel & m);
    ~Octree();
    
    vector3f get_vertex(unsigned int i) const;

    const triangle * const get_intersecting_triangle(const vector3f & point, const vector3f & direction) const;
    void render() const;
    int max_depth;
    int min_tri;

private:
    OctreeNode *root_node;
    CASEModel model;
};

class OctreeNode {
public:
	OctreeNode(const Octree *r, int d, int t);
	~OctreeNode();

    const triangle * const  get_intersecting_triangle(const vector3f & point, const vector3f & direction) const;
    const Octree* root;
    void add_triangle(int idx);
	void build_octree();
    void set_BBox(box3f b);
    void render() const;
private:
    box3f BBox;
    int depth;
	int min_tri;
    int n_tri; 
	std::vector<int> triangle_references;
	OctreeNode* children[8];
	OctreeNode* parent;

};

