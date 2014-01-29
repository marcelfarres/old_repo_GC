#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "matrix4x4f.h" 

class input{
public:
	// Fun
	input();
	~input();
	void reset();
	void updateProjection();
	void updateView();
	void updateModel();
	void onReshape(int width, int height);
	void MyKeyboardFunc(unsigned char Key, int x, int y);
	void MyKeyboardFunc(int Key, int x, int y);

private:
	float sf_trlz[3];
	int max_col;
	glm::vec3 direction;
	int height;			// Screen height
	int width;			// Screen width 
	glm::mat4 Projection;
	glm::mat4 View;
	glm::vec3 Camera;
	glm::mat4 model;
	float dolly;
	float zoom;

	void SetZoom(float in_zoom);
	void SetDolly(float in_dolly);
	void MoveObj(float in_x, float in_y, float in_z);
	void RotObj(float in_x, float in_y, float in_z, float dir);
};
#endif
