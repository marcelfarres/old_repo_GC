#include "octree.h"
#include "ase.h"
#include <cassert>
#include <cmath>
#define EPSILON 0.00001

inline bool float_is_zero(float f) {
    return fabs(f) < EPSILON;
}


Octree::Octree(const CASEModel &m) : triangles(m.getTriangles()), model(m){
	max_depth = 8;
	min_tri = 10;
    root_node = new OctreeNode(this, max_depth, min_tri);
    for(unsigned i = 0; i < triangles.size(); i++) {
        root_node->add_triangle(i);
    }
    root_node->set_BBox(m.get_BBox());
    root_node->build_octree();

}

vector3f Octree::get_vertex(unsigned idx) const{
    return model.get_vertex(idx);
}

void Octree::render() const {
    root_node->render();
}

const triangle * const  Octree::get_intersecting_triangle(const vector3f & point, const vector3f & direction) const {
    // TODO: something i forgot
    return root_node->get_intersecting_triangle(point, direction);
}

Octree::~Octree() {
    delete root_node;
}

OctreeNode::OctreeNode(const Octree *r, int d, int min_t) : root(r), depth(d), min_tri(min_t), n_tri(0) {
    for(int i = 0; i < 8; i++) {
        children[i] = NULL;
    }
}
void OctreeNode::add_triangle(int idx) {
    if (triangle_references.empty() || triangle_references.back() != idx) {
        n_tri ++;
        triangle_references.push_back(idx);
    }
}

const triangle * const  OctreeNode::get_intersecting_triangle(const vector3f & point, const vector3f & direction) const {
    if (! BBox.intersects(point, direction)) {
        // TODO: Move this check to Octree for speed.
        return NULL;
    }
    // TODO:
    // if the triangle list is not empty, then we are on one leaf node,
    // so check if any of the triangles intersect with our ray. if it
    // does, return it.
    //
    // else, we either are in a completely empty octree node (which
    // should have no children) or in a parent node. if in empty we
    // should return NULL, otherwise check children.
    triangle * best_t = NULL;
    float distance = FLT_MAX;
    for (int i = 0; i < 8; i++) {
       // TODO: i'm sleepy now.
       // for each octree children check if the ray intersect its box.
       // if it does, enter it and recursively check for the
       // intersection.
    }
    return NULL;
}

void OctreeNode::render() const {
    BBox.render();
    for(int i = 0; i < 8; i++) {
        if (children[i] != NULL) {
            children[i]->render();
        }
    }
}

OctreeNode::~OctreeNode() {
    for(int i = 0; i < 8; i++) {
        if (children[i] != NULL) {
            delete children[i];
        }
    }
}

void OctreeNode::set_BBox(box3f b) {
    BBox = b;
}

void OctreeNode::build_octree() {
    if (n_tri < min_tri || depth == 0) {
        return;
    }
    vector3f center = BBox.get_center();
    for (int i = 0; i < 8; i++) {
        children[i] = new OctreeNode(root, depth-1, min_tri);
        box3f box(i&4?BBox.right:center.x,
                  i&2?BBox.top:center.y,
                  i&1?BBox.front:center.z,
                  i&4?center.x:BBox.left,
                  i&2?center.y:BBox.bottom,
                  i&1?center.z:BBox.back); 
        children[i]->set_BBox(box);

    }
    while(triangle_references.size() > 0) {
        int idx = triangle_references.back();
        triangle_references.pop_back();
        triangle t = root->triangles[idx];
        
        children[BBox.get_octant(root->get_vertex(t.a))]->add_triangle(idx);
        children[BBox.get_octant(root->get_vertex(t.b))]->add_triangle(idx);
        children[BBox.get_octant(root->get_vertex(t.c))]->add_triangle(idx);

    }
    for (int i = 0; i < 8; i++) {
        children[i]->build_octree();
    }
}

// from http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool triangle_intersects(const vector3f & v1,
                         const vector3f & v2,
                         const vector3f & v3,
                         const vector3f & point,
                         const vector3f & direction) {

    vector3f edge1 = v1 - v2;
    vector3f edge2 = v3 - v1;
    vector3f P = crossProduct(direction, edge2);
    float det = dotProduct(edge1, P);
    if(float_is_zero(det)) {
        // ray lies in plane of the triangle
        return false;
    }
    float inv_det = 1.0f / det;
    
    vector3f T = point - v1;
    float u = dotProduct(T,P) * inv_det;

    if (u < 0 || u > 1) {
        return false;
    }
    vector3f Q = crossProduct(T, edge1);
    float v = dotProduct(direction, Q) * inv_det;
    if(v < 0.f || u + v  > 1.f) {
        return false;
    }

    float t = dotProduct(edge2, Q) * inv_det;
    if (t > EPSILON) {
        return true;
    }

    return false;
}
