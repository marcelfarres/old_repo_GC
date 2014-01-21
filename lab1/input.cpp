#include "input.h"


using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

input::input(){
	// screen size 
	height = 600;
	width = 800;

	// This is hardcoded..... (we should control this by rotation around (0,0,0)
	direction = glm::vec3(0, 0.5, 1);

	// init params scale factor (Borrar si al final no es fan servir tots ! )
	sf_trlz[0] = 1.0f;      // Translate and dolly
	sf_trlz[1] = 5.0f;      // Rotate (degrees)
	sf_trlz[2] = 0.1f;      // Light
	sf_trlz[3] = 1.0f;      // Zoom

	reset();
}

void input::reset(){
	// init view
	dolly = 70.0;
	updateView();

	// init proj
	zoom = 40.0;
	updateProjection();
}

void input::onReshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	updateProjection();
}

void input::MyKeyboardFunc(unsigned char Key, int x, int y){
	switch (Key){
	case '+': SetZoom(-1); std::cout << "working ";           break; // Zoom IN 
	case '-': SetZoom(1);              break; // Zoom OUT
	case ',': SetDolly(-1);             break; // Dolly IN 
	case '.': SetDolly(1);             break; // Dolly OUT
	case 'Z': case 'z': reset();        break; // Reset to defaults
	};
}

void input::updateProjection(){
	Projection = glm::perspective(zoom, width / (float)height, 0.1f, 1000.0f);
}

void input::updateView()
{
	// The up vector is orthogonal to direction, and with the same Y
	View = glm::lookAt(direction * dolly, glm::vec3(0.0f),
		glm::vec3(0, 1, 0));
	Camera = direction * dolly;
}

void input::SetZoom(float in_zoom)
{
	zoom = zoom + in_zoom * sf_trlz[3];
	zoom = MIN(zoom, 150);
	zoom = MAX(zoom, 0.01);
	updateProjection();
}


void input::SetDolly(float in_dolly)
{
	dolly = dolly + in_dolly * sf_trlz[0];
	dolly = MAX(dolly, 0.01);
	updateView();
}
input::~input()
{
}
