#include <stdio.h>
#include <stdlib.h>
#include "include\GL\freeglut.h"
#include "structs.h"
#include <math.h>
#include <time.h>

Raketka raketka;
Plate table;
Sphere ball;
GLfloat normal[3] = {0.0, 350.0, 0.0};
double current_x, current_y; //ракетка
char next_player = 'p'; //следующий удар: next_player или bot
GLint touch = -1000; //число касаний шарика о стол после удара player

void normalize(GLfloat *v)
{
	GLfloat d = sqrt((GLfloat)v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = (GLfloat)v[0] / d;
	v[1] = (GLfloat)v[1] / d;
	v[2] = (GLfloat)v[2] / d;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	normalize(normal);
	glLoadIdentity();

	

	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 25.0, 40.0, 10.0, 0.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glPushMatrix();
	
	GLfloat mat_specular_ball[] = { 1.0, 0.75, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_ball);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_specular_ball);
	glTranslated(ball.X + ball.SpdX, ball.Y + ball.SpdY, ball.Z + ball.SpdZ);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(ball.R, 40, 16);
	glTranslated(-ball.X - ball.SpdX, -ball.Y - ball.SpdY, -ball.Z - ball.SpdZ);
	
	glPushMatrix();
	GLfloat mat_specular_table[] = { 0.0, 0.7, 0.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_table);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_specular_table);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glNormal3f(normal[0], normal[1], normal[2]);
	glVertex3f(-10.0, 0.0, 30.0);
	glVertex3f(15.0, 0.0, 30.0);
	glVertex3f(15.0, 0.0, -40.0);
	glVertex3f(-10.0, 0.0, -40.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	GLfloat mat_specular_setka[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_setka);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_specular_setka);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(2.5, 0, -5);
	glScalef(2.5, 0.2, 1);
	glutSolidCube(10.0);
	glTranslatef(-2.5, 0, 5);
	glPopMatrix();

	glPushMatrix();
	raketka.X = current_x;
	raketka.Y = current_y;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(current_x, 10.0, current_y);
	glVertex3f(current_x, 10.0, current_y + 5);
	glVertex3f(current_x + 5, 10.0, current_y + 5);
	glVertex3f(current_x + 5, 10.0, current_y);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

void motion(int x, int y)
{
	current_x = x / 10 - 39;
	current_y = -((GLdouble)-y / 10 + 40) * 32 / sqrt(325.0);
}

void reshape(int w, int h){
	gluLookAt(5.0, 10.0, 0.0, 5.0, 0.0, -15.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-40.0, 40.0, -40.0, 40.0, -40.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
}



void calculate()
{
	glutMotionFunc(motion);
	if (ball.SpdY <= ball.AclY) Collison(&ball, &table, &next_player, &touch);
	if (next_player == 'p' && ball.Z >= -5 && touch == 1) 
		Shot(&ball, &raketka, &next_player, &touch);
	if (next_player == 'b' && ball.Z >= -40 && ball.Z <= -5 && touch == 1)
		BOT(&ball, &next_player, &touch);
	Setka(&ball, &next_player);
	Lose(&ball, &table, &next_player, &touch);
	ball.SpdX += ball.AclX;
	ball.X += ball.SpdX;
	ball.SpdY += ball.AclY;
	ball.Y += ball.SpdY;
	ball.SpdZ += ball.AclZ;
	ball.Z += ball.SpdZ;
	glutPostRedisplay();
	Sleep(20);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMotionFunc(motion);
	glutIdleFunc(calculate);
	glutMainLoop();
	return 0;
}