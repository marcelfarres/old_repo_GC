#ifndef _ASE_LOADER_
#define _ASE_LOADER_

#include <iostream>
#include <vector>

#include "vector3f.h"
#include "box3f.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class triangle
{
public:
	union
	{
		struct{unsigned int t[3];};
		struct{unsigned int a,b,c;};
	};
	
};

/////////////////////////////////////////////////////////////////////////////////////////
// Simple ASE File format Loader
/////////////////////////////////////////////////////////////////////////////////////////
class CASEModel
{
public:
	CASEModel();

public:
	// primary load model method
	bool load(const char* filename);

	// gl render
	void render() const;

    box3f getBoundingBox() const;

protected:
	std::vector<vector3f> m_vertices;
	std::vector<triangle> m_triangles;
};


#endif
