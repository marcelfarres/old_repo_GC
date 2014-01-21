#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

class input
{
public:
	// Var
	int height;			// Screen height
	int width;			// Screen width 
	glm::mat4 Projection;
	glm::mat4 View;
	glm::vec3 Camera;

	// Fun
	input();
	~input();
	void reset();
	void updateProjection();
	void updateView();
	void onReshape(int width, int height);
	void MyKeyboardFunc(unsigned char Key, int x, int y);
	void SetZoom(float in_zoom);
	void SetDolly(float in_dolly);

private:
	float sf_trlz[4];
	int max_col;
	float zoom;
	float dolly;
	glm::vec3 direction;
};

