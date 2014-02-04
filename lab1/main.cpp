#include <iostream>
#include <cstring>
// global includes
#include "GL/glut.h"

// local includes
#include "ase.h"
#include "vector3f.h"
#include "input.h"
#include "box3f.h"
#include "octree.h"
#include "matrix4x4f.h" 
// global libs

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#endif
// global variables
int g_buttons[3];
int g_mouse_x,g_mouse_y;
int g_width, g_height;
input inputinstance;

// the mesh model
CASEModel g_model;
box3f box;
Octree *o;

// local defines
#define LEFTMOUSE 0
#define MIDDLEMOUSE 1
#define RIGHTMOUSE 2

//2k8

void drawString(int x, int y, const char* string){
	int i, len;
	glRasterPos2f(x, y);
	glColor3f(1,1,1);
	len = strlen (string);
	for (i=0;i<len;i++)	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
	}
}

void help(){
	glDisable(GL_LIGHTING);
	// prepare 2d viewport
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,1000,0,1000);

	// REESCRIURE
	drawString(60,10," MOVE --->  RIGHT:q LEFT:a UP:w DOWN:s BACK:e FORWARDS:d");
	drawString(60,40," X Axis rotation (+/-): r/f, Y Axis rotation (+/-): t/g Z Axis rotation (+/-): y/h");
}

void drawAxis() {
    // XYZ correspond to RGB. 
    // Negative coordinates are the inverse color.
    
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(2,0,0);
        glColor3f(0,1,1);
        glVertex3f(-2,0,0);
        glColor3f(0,1,0);
        glVertex3f(0,2,0);
        glColor3f(1,0,1);
        glVertex3f(0,-2,0);
        glColor3f(0,0,1);
        glVertex3f(0,0,2);
        glColor3f(1,1,0);
        glVertex3f(0,0,-2);
    glEnd();
}

void init(void){


}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glShadeModel(GL_FLAT);
	// setup camera
	inputinstance.updateProjection();
	inputinstance.updateView();
	inputinstance.updateModel();

	//render here

	//draw  a square centered at 0,0
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3f(-3,0,3);
	glVertex3f(3,0,3);
	glVertex3f(3, 0, -3);
	glVertex3f(-3, 0, -3);
	glEnd();

    // draw axis centered at 0,0,0
	drawAxis();

	// draw model
	g_model.render();

	// draw octre
	o->render();

	//glDisable(GL_LIGHTING);
	help();
	

	glFlush();
	glutSwapBuffers();
}

void onReshape(int w, int h){
	inputinstance.onReshape(w, h);
}

void onKeyboard(unsigned char k, int x, int y){
	inputinstance.MyKeyboardFunc(k, x, y);
}

void onKeyboard(int k, int x, int y){
	inputinstance.MyKeyboardFunc(k, x, y);
}
//void parsekey(unsigned char key, int x, int y){
//	switch (key)
//	{
//		case 27: exit(0); break;
//		case 13: break;
//	}
//}
//
//void parsekey_special(int key, int x, int y){
//	switch (key)
//	{
//		case GLUT_KEY_UP:
//			g_vEye += (g_vLook)*0.05f;
//			break;
//		case GLUT_KEY_DOWN:
//			g_vEye -= (g_vLook)*0.05f;
//			break;
//		case GLUT_KEY_RIGHT:
//			g_vEye += (g_vRight)*0.05f;
//			break;
//		case GLUT_KEY_LEFT:	
//			g_vEye -= (g_vRight)*0.05f;
//			break;
//	}
//}

void idle(){
	display();
}

//void motion(int x, int y){
//	int dx = x - g_mouse_x;
//	int dy = y - g_mouse_y;
//
//	if (g_buttons[LEFTMOUSE] == 1)
//	{
//		matrix4x4f matRotation;
//		if( dy != 0 )
//		{
//			matRotation.rotate( -(float)dy / 3.0f, g_vRight );
//			matRotation.transformVector( &g_vLook );
//			matRotation.transformVector( &g_vUp );
//		}
//
//		if( dx != 0 )
//		{
//			matRotation.rotate( -(float)dx / 3.0f, vector3f(0.0f, 1.0f, 0.0f) );
//			matRotation.transformVector( &g_vLook );
//			matRotation.transformVector( &g_vUp );
//		}
//
//	}
//
//	g_mouse_x = x;
//	g_mouse_y = y;
//}

void mouse(int button, int state, int x, int y)
{
    g_mouse_x = x;
    g_mouse_y = y;
    switch (button) {
    case GLUT_LEFT_BUTTON:
        g_buttons[LEFTMOUSE] = (state == GLUT_DOWN);
        break;
    case GLUT_MIDDLE_BUTTON:
        g_buttons[MIDDLEMOUSE] = (state == GLUT_DOWN);
        break;
    case GLUT_RIGHT_BUTTON:
        g_buttons[RIGHTMOUSE] = (state == GLUT_DOWN);
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Practica 1. Creacio d un octree a partir d un mesh");
	glutDisplayFunc(display);
	glutKeyboardFunc(onKeyboard);
	glutSpecialFunc(onKeyboard);
	glutReshapeFunc(onReshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	//glutMotionFunc(motion);

	// load a model
	//g_model.load("data/teapot.ase");
	g_model.load("data/knot.ase");
	//g_model.load("data\\terrain.ase");
    o = new Octree(g_model);
	
	glutSwapBuffers();
	glutMainLoop();
	glutReshapeFunc(onReshape);
	return 0;
}


#undef LEFTMOUSE
#undef MIDDLEMOUSE
#undef RIGHTMOUSE
