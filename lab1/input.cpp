#include "input.h"

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

input::input(){
	// screen size 
	height = 600;
	width = 800;

	// This is hardcoded..... (we should control this by rotation around (0,0,0)
	direction = vector3f(0, 0.5, 1);

	// init params scale factor (Borrar si al final no es fan servir tots ! )
	sf_trlz[0] = 1.0f;      // Translate and dolly
	sf_trlz[1] = 5.0f;      // Rotate (degrees)
	sf_trlz[2] = 1.0f;      // Zoom

	reset();
}

void input::reset(){
	// init view
	dolly = 10.0;
	updateView();

	// init proj
	zoom = 40.0;
	updateProjection();

	// init model
	model = glm::mat4(1.0);
	updateModel();
}

void input::onReshape(int w, int h){
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	updateProjection();
}

void input::MyKeyboardFunc(unsigned char Key, int x, int y){
	switch (Key){
	case '+': SetZoom(-1);				break; // Zoom IN 
	case '-': SetZoom(1);				break; // Zoom OUT
	case ',': SetDolly(-1);				break; // Dolly IN 
	case '.': SetDolly(1);				break; // Dolly OUT
	case 'q': MoveObj( 1, 0, 0);		break; // Move X + OBJ
	case 'a': MoveObj(-1, 0, 0);		break; // Move X - OBJ          
	case 'w': MoveObj(0,  1, 0);		break; // Move Y + OBJ
	case 's': MoveObj(0, -1, 0);		break; // Move Y - OBJ
	case 'e': MoveObj(0, 0,  1);		break; // Move Z + OBJ
	case 'd': MoveObj(0, 0, -1);		break; // Move Z + OBJ  
	case 'r': RotObj(1, 0, 0,  1);		break; // Rotate X + OBJ 
	case 'f': RotObj(1, 0, 0, -1);		break; // Rotate X - OBJ        
	case 't': RotObj(0, 1, 0,  1);		break; // Rotate Y + OBJ
	case 'g': RotObj(0, 1, 0, -1);		break; // Rotate Y - OBJ 
	case 'y': RotObj(0, 0, 1,  1);		break; // Rotate Z + OBJ
	case 'h': RotObj(0, 0, 1, -1);		break; // Rotate Z + OBJ  
	case 'Z': case 'z': reset();        break; // Reset to defaults
	};
}

void input::MyKeyboardFunc(int Key, int x, int y){
	// futer worck with arrows keys
}

void input::updateProjection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, width / (float)height, 0.1f, 1000.0f);
	Projection = glm::perspective(zoom, width / (float)height, 0.1f, 1000.0f);
}

void input::updateView(){
	glMatrixMode(GL_PROJECTION);
	gluLookAt(direction[0] * dolly, direction[1] * dolly, direction[2] * dolly,
		0.f, 0.f, 0.f, 
		0, 1, 0);
	//View = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0, 1, 0));
}

void input::updateModel(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	matrix4x4f view;
	view.identity();

	view.m[0] = model[0][0];
	view.m[1] = model[0][1];
	view.m[2] = model[0][2];
	view.m[3] = model[0][3];

	view.m[4] = model[1][0];
	view.m[5] = model[1][1];
	view.m[6] = model[1][2];
	view.m[7] = model[1][3];

	view.m[8] = model[2][0];
	view.m[9] = model[2][1];
	view.m[10] = model[2][2];
	view.m[11] = model[2][3];

	view.m[12] = model[3][0];
	view.m[13] = model[3][1];
	view.m[14] = model[3][2];
	view.m[15] = model[3][3];

	glMultMatrixf(view.m);
}

void input::SetZoom(float in_zoom){
	zoom = zoom + in_zoom * sf_trlz[2];
	zoom = MIN(zoom, 150);
	zoom = MAX(zoom, 0.01);
	updateProjection();
}

void input::SetDolly(float in_dolly){
	dolly = dolly + in_dolly * sf_trlz[0];
	dolly = MAX(dolly, 0.01);
	updateView();
}

void input::MoveObj(float in_x, float in_y, float in_z){
	glm::vec3 tr = glm::vec3(sf_trlz[0] * in_x, sf_trlz[0] * in_y, sf_trlz[0] * in_z);
	model = glm::translate(model, tr);
}


void input::RotObj(float in_x, float in_y, float in_z, float dir){
	model = glm::rotate(model, sf_trlz[1] * dir, glm::vec3(in_x, in_y, in_z));
}

//int glhUnProjectf(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate)
//{
//	//Transformation matrices
//	float m[16], A[16];
//	float in[4], out[4];
//	//Calculation for inverting a matrix, compute projection x modelview
//	//and store in A[16]
//	MultiplyMatrices4by4OpenGL_FLOAT(A, projection, modelview);
//	//Now compute the inverse of matrix A
//	if (glhInvertMatrixf2(A, m) == 0)
//		return 0;
//	//Transformation of normalized coordinates between -1 and 1
//	in[0] = (winx - (float)viewport[0]) / (float)viewport[2] * 2.0 - 1.0;
//	in[1] = (winy - (float)viewport[1]) / (float)viewport[3] * 2.0 - 1.0;
//	in[2] = 2.0*winz - 1.0;
//	in[3] = 1.0;
//	//Objects coordinates
//	MultiplyMatrixByVector4by4OpenGL_FLOAT(out, m, in);
//	if (out[3] == 0.0)
//		return 0;
//	out[3] = 1.0 / out[3];
//	objectCoordinate[0] = out[0] * out[3];
//	objectCoordinate[1] = out[1] * out[3];
//	objectCoordinate[2] = out[2] * out[3];
//	return 1;

vector3f input::UnProjection(int  x, int  y, int  z){
	vector3f newPos;
	vector3f cords;
	glm::vec3 d;
	GLint viewport [4];
	matrix4x4f proj, mod;

	matrix4x4f m;
	glGetFloatv(GL_PROJECTION_MATRIX, proj.m);
	glGetFloatv(GL_MODELVIEW_MATRIX, mod.m);

	m = proj * mod;
	matrix4x4f inverseProjection = matrix4x4f::invertMatrix(&m);
	glGetIntegerv(GL_VIEWPORT, viewport);

	//cords[0] = 2 * (x - direction[0]) / direction[2] - 1;
	//cords[1] = 2 * (y - direction[1]) / direction[3] - 1;
	//cords[2] = 2 * (z)-1;
	//cords[3] = 1;

	cords.x = 2 * (x - (float)viewport[0]) / (float)viewport[2] - 1;
	cords.y = 2 * (y - (float)viewport[1]) / (float)viewport[3] - 1;
	cords.z = 2 * (z)-1;


	multVecMat(newPos.t, inverseProjection.m, cords.t);

	cout << "mouse window          " << "_" << x << "_" << y << "_" << z << endl;
	cout << "mouse window          " << "_" << cords.x << "_" << cords.y << "_" << z << endl;
	cout << "mouse world           " << "_" << newPos.x << "_" << newPos.y << "_" << newPos.z << endl;
	cout << "view port             " << "_" << viewport[0] << "_" << viewport[1] << "_" << viewport[2] << "_" << viewport[3] << endl;
	return newPos;
}


vector3f input::GetVecPoint(int x, int y, int z, vector3f *v){
	vector3f near;
	vector3f far;
	vector3f t;
	cout << "near  ";
	near = input::UnProjection(x, y, z);
	cout << "far  ";
	far = input::UnProjection(x, y, z+1);
	t = far - near;
	cout << "Vector no normalized" << "_" << t[0] << "_" << t[1] << "_" << t[2] << endl;
	*v = far - near;
	v->normalize();
	cout << "Vector normalized" << "_" << v->x << "_" << v->y << "_" << v->z << endl;


	return near;

}

void input::multVecMat(float *resultvector, const float *matrix, const float *pvector){
	resultvector[0] = matrix[0] * pvector[0] + matrix[4] * pvector[1] + matrix[8] * pvector[2] + matrix[12] * pvector[3];
	resultvector[1] = matrix[1] * pvector[0] + matrix[5] * pvector[1] + matrix[9] * pvector[2] + matrix[13] * pvector[3];
	resultvector[2] = matrix[2] * pvector[0] + matrix[6] * pvector[1] + matrix[10] * pvector[2] + matrix[14] * pvector[3];
	resultvector[3] = matrix[3] * pvector[0] + matrix[7] * pvector[1] + matrix[11] * pvector[2] + matrix[15] * pvector[3];
}
input::~input()
{
}
