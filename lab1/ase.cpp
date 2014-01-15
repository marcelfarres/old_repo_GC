#include "ase.h"
#include "text.h"
#include "vector3f.h"
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

CASEModel::CASEModel()
{
}

bool CASEModel::load(const char* filename)
{
	CText t(filename);

	t.Seek("*MESH_NUMVERTEX");
	int n = t.GetInt();

	m_vertices.resize(n);

	t.Seek("*MESH_NUMFACES");
	n = t.GetInt();
	m_triangles.resize(n);

	int i;
	for (i=0; i<m_vertices.size(); i++)
	{
		t.Seek("*MESH_VERTEX");
		if (t.GetInt()==i)
		{
			// MAX TO OPENGL CONVERSION: +x,+y,+z -> -x,+z,+y
			m_vertices[i].x=-t.GetFloat();
			m_vertices[i].z=t.GetFloat();
			m_vertices[i].y=t.GetFloat();

		}
		else
			return false;
	}

	for (i=0;i<m_triangles.size(); i++)
	{
		t.Seek("*MESH_FACE");
		if (t.GetInt()==i)
		{
			t.Seek("A:");
			m_triangles[i].a=t.GetInt();
			t.Seek("B:");
			m_triangles[i].b=t.GetInt();
			t.Seek("C:");
			m_triangles[i].c=t.GetInt();
		}
	}

	return true;
}

void CASEModel::render() const
{	
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(1,1,1);
	glBegin(GL_TRIANGLES);
	int i;
	for (i=0;i<m_triangles.size();i++)
	{
		const triangle & t = m_triangles[i];
/*
		vector3 normal;
		normal = cross(
			m_vertices[t.b] - m_vertices[t.a],
			m_vertices[t.c] - m_vertices[t.a]);
		normal.normalize();

		
		glNormal3fv(normal);
		*/
		glVertex3fv(m_vertices[t.a]);
		glVertex3fv(m_vertices[t.b]);
		glVertex3fv(m_vertices[t.c]);
	}
	glEnd();
}

box3f CASEModel::getBoundingBox() const {
    if (m_vertices.size() == 0) {
        return box3f(0,0,0,0,0,0);
    }
    vector3f f = m_vertices[0];
    box3f bBox(f.x, f.x, f.y, f.y, f.z, f.z);
    for (unsigned i = 1; i < m_vertices.size(); i++) {
        
        if (bBox.top < m_vertices[i].y) {
            bBox.top = m_vertices[i].y;
        }
        else if (bBox.bottom > m_vertices[i].y) {
            bBox.bottom = m_vertices[i].y;
        }
        if (bBox.right < m_vertices[i].x) {
            bBox.right = m_vertices[i].x;
        }
        else if (bBox.left > m_vertices[i].x) {
            bBox.left = m_vertices[i].x;
        }
        if (bBox.front < m_vertices[i].z) {
            bBox.front = m_vertices[i].z;
        }
        else if (bBox.back > m_vertices[i].z) {
            bBox.back = m_vertices[i].z;
        }
    }
    return bBox;
}
