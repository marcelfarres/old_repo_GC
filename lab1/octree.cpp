#include "octree.h"
#include "ase.h"

Octree::Octree(const CASEModel &m) : triangles(m.getTriangles()), model(m){
	max_depth = 1;
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

Octree::~Octree() {
    delete root_node;
}

OctreeNode::OctreeNode(const Octree *r, int d, int min_t) : root(r), depth(d), min_tri(min_t), n_tri(0) {
    for(int i = 0; i < 8; i++) {
        children[i] = NULL;
    }
}
void OctreeNode::add_triangle(int idx) {
    n_tri ++;
    triangle_references.push_back(idx);
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
        box3f box(i&1?BBox.right:center.x,
                  i&2?BBox.top:center.y,
                  i&4?BBox.front:center.z,
                  i&1?center.x:BBox.left,
                  i&2?center.y:BBox.bottom,
                  i&4?center.z:BBox.back); 
        std::cout << box;
        children[i]->set_BBox(box);

    }
    while(triangle_references.size() > 0) {
        int idx = triangle_references.back();
        triangle_references.pop_back();
        triangle t = root->triangles[idx];
        // TODO do something with the intersecting triangles.
        
        // if all three vertices are in the same octant,
        int octant = BBox.get_octant(root->get_vertex(t.a));
        if (octant == BBox.get_octant(root->get_vertex(t.b)) &&
            octant == BBox.get_octant(root->get_vertex(t.c))) {
            // insert the triangle in said octant.
            children[octant]->add_triangle(idx);
        }
    }
}

