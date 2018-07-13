#include <cmath>
#include "include\GL\freeglut.h"
#include <vector>
#include <iostream>
#include "Class.h"
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("–усский биль€рд");
	Control::init();
	glutDisplayFunc(Display::Strike);
	glutReshapeFunc(Display::reshape);
	glutKeyboardFunc(Keyboard::ki_control);
	glutIdleFunc(Display::move);
	glutMainLoop();
}