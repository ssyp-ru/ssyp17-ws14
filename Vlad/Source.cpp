#include "freeglut.h"
#include "stdlib.h"
#include <math.h>
#include <string>

GLdouble coord[159][159];

GLdouble xspider = 0;
GLdouble yspider = -5;

int level = 1;
GLdouble xpers = 0;
GLdouble ypers = 0;
GLdouble xspell = 0;
GLdouble yspell = 0;
GLdouble xspellsp = 0;
GLdouble yspellsp = 0;
int wid = 800;
int hei = 600;
GLdouble xmo, ymo, xmmo, ymmo, xmos, ymos;
int invent = 0;
int attack = 0;
int attacksp = 0;
int moving = 0;
int movingsp = 1;
GLdouble xO = 0;
GLdouble yO = 0;
GLdouble xOspell = 0;
GLdouble yOspell = 0;
GLdouble xOspellsp = 0;
GLdouble yOspellsp = 0;
GLdouble xOspider = 0;
GLdouble yOspider = 0;
GLdouble xf = 0;
GLdouble yf = 0;
int ability = 1;
int GOD_MOD = 0;
GLdouble xmanek = 7;
GLdouble ymanek = 3;
int expgive = 0;

#define STEP 0.2
#define STEPSP 0.1
#define FROSTBOLT_SPEED 0.5
#define FIREBALL_SPEED 0.25
#define EARTHBALL_SPEED 1.2
#define SPIDER_ATTACK_SPEED 0.3
#define RADIUS 16
#define MAGIC_ORB_SPEED 0.2

typedef struct mob
{
	int hp;
	int mana;
	int maxhp;
	int maxmana;
	int exp;
	int maxexp;
	int level;
	int damage;
}mob;

mob* player = (mob*)malloc(sizeof(mob));

mob* maneken = (mob*)malloc(sizeof(mob));

mob* spider = (mob*)malloc(sizeof(mob));

typedef struct spell
{
	int manacost;
	int damage;

}spell;

spell* frost = (spell*)malloc(sizeof(spell));

spell* fireb = (spell*)malloc(sizeof(spell));

spell* earthball = (spell*)malloc(sizeof(spell));

spell* magic_orb = (spell*)malloc(sizeof(spell));

void init(void)
{
	/*GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat mat_shininess[] = { 30.0 };
	GLfloat light_position[] = { 3.0, 3.0, 3.0, 0.0 };
	GLfloat white_light[] = { 1.0, 0.35, 0.0, 0.8 };

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	*/
	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_NORMALIZE);
	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-40.0, 40.0, -40.0, 40.0, -40.0, 40.0);
	//gluLookAt(5.0 + ypers, 0.0, 0.0,  xpers, -1.0 + ypers, -5.0,  xpers, -1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}

void displaycube(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, -50.0);
	glVertex3f(-50.0, 50.0, -50.0);
	glVertex3f(-50.0, 50.0, 50.0);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(50.0, -50.0, 50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, -50.0, 50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(50.0, 50.0, -50.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(50.0, 50.0, -50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(-50.0, 50.0, -50.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.35, 0.1);
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(-50.0, 50.0, -50.0);
	glVertex3f(-50.0, 50.0, 50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-50.0, 50.0, 50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glVertex3f(50.0, -50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glEnd();

	/*glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, -50.0, 50.0);
	glVertex3f(50.0, -50.0, -50.0);
	glVertex3f(50.0, 50.0, -50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-50.0, 50.0, 50.0);
	glVertex3f(-50.0, -50.0, 50.0);
	glVertex3f(-50.0, -50.0, -50.0);
	glVertex3f(-50.0, 50.0, -50.0);
	glVertex3f(-50.0, 50.0, 50.0);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glVertex3f(50.0, 50.0, 50.0);
	glEnd();*/

	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void move(int xmou, int ymou)
{
	float x = (xmou - 400) / 2.5;
	float y = -(ymou - 345) / 2.5;
	float size = sqrt(y*y + x*x);
	if (size < round(size) + 0.5)
		size = round(size);
	else
		size = round(size) + 1;
	if (moving == 1)
		if (x<80 || x>-80 || y<80 || y>-80)
			if (x > 0)
				if (y > 0)
				{
					if (x > y)
					{
						 xpers =  xpers + 1;
						 ypers =  ypers + y / x*sqrt(2);
						glutPostRedisplay();
					}
				}
				else
				{
					for (int i = 0; i < (y -  ypers)*sqrt(2); i++)
					{
						 xpers =  xpers + x / y;
						 ypers =  ypers + 1;
						glutPostRedisplay();
					}
					Sleep(10);
				}
	if ( xpers == x &&  ypers == y)
		moving = 0;
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			if (invent == 0)
			{
				xO = xpers;
				yO = ypers;
				moving = 1;
				xmo = (x - 400) / 19;
				ymo = -(y - 299) / 19;
			}
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			if (invent == 0)
			{
				if (attack == 0)
				{
					if (ability == 1)
						if (player->mana > frost->manacost)
						{
							xf = xpers;
							yf = ypers;
							if (moving == 1)
							{
								xOspell = xpers;
								yOspell = ypers;
							}
							else
							{
								xOspell = xspell;
								yOspell = yspell;
							}
							attack = 1;
							player->mana = player->mana - frost->manacost;
							xmmo = (x - 400) / 19;
							ymmo = -(y - 299) / 19;
						}

					if (ability == 2)
						if (player->mana > fireb->manacost)
						{
							if (moving == 1)
							{
								xOspell = xpers;
								yOspell = ypers;
							}
							else
							{
								xOspell = xspell;
								yOspell = yspell;
							}
							attack = 1;
							player->mana = player->mana - fireb->manacost;
							xmmo = (x - 400) / 19;
							ymmo = -(y - 299) / 19;
						}
					if (ability == 3)
						if (player->mana > earthball->manacost)
						{
							if (moving == 1)
							{
								xOspell = xpers;
								yOspell = ypers;
							}
							else
							{
								xOspell = xspell;
								yOspell = yspell;
							}
							attack = 1;
							player->mana = player->mana - earthball->manacost;
							xmmo = (x - 400) / 19;
							ymmo = -(y - 299) / 19;
						}
					if (ability == 4)
						if (player->mana > magic_orb->manacost)
						{
							if (moving == 1)
							{
								xOspell = xpers;
								yOspell = ypers;
							}
							else
							{
								xOspell = xspell;
								yOspell = yspell;
							}
							attack = 1;
							player->mana = player->mana - magic_orb->manacost;
							xmmo = (x - 400) / 19;
							ymmo = -(y - 299) / 19;
						}
				}
			}
		}
		break;
	default:
		break;
	}
}

void calculate(void)
{
	GLdouble x = 0;
	GLdouble y = 0;
	if (moving == 0)
	{
	xO = xpers;
	yO = ypers;
	if (ability == 4)
	{
		xOspell = xpers;
		yOspell = ypers;
	}
	}

	if (moving == 1)
	{
		x = xmo;
		y = ymo;
		if (xpers<79 && xpers>-79 && ypers<79 && ypers>-79)
		{
			if (fabs(x) < 1)
				if (y > ypers)
					ypers = ypers + STEP;
				else
					ypers = ypers - STEP;
			if (fabs(y) < 1)
				if (x > xpers)
					xpers = xpers + STEP;
				else
					xpers = xpers - STEP;
			if (x > 0)
			{
				if (y > 0)
				{
					if (x > y)
					{
						xpers = xpers + STEP;
						ypers = ypers + (y / x) / (1 / STEP);
					}
					else
					{
						xpers = xpers + (x / y) / (1 / STEP);
						ypers = ypers + STEP;
					}
					if ((xpers >= x + xO && fabs(x) > 1) || (ypers >= y + yO && fabs(y) > 1))
						moving = 0;
				}
				else
				{
					if (x > -y)
					{
						xpers = xpers + STEP;
						ypers = ypers + (y / x) / (1 / STEP);
					}
					else
					{
						xpers = xpers + (x / (-y)) / (1 / STEP);
						ypers = ypers - STEP;
					}
					if ((xpers >= x + xO && fabs(x) > 1) || (ypers >= -y + yO && fabs(y) > 1))
						moving = 0;
				}
			}
			else /////////////////////////////////////////// X<0
			{
				if (y > 0)
				{
					if (-x > y)
					{
						xpers = xpers - STEP;
						ypers = ypers - (y / x) / (1 / STEP);
					}
					else
					{
						xpers = xpers + (x / y) / (1 / STEP);
						ypers = ypers + STEP;
					}
					if ((xpers >= -x + xO && fabs(x) > 1) || (ypers >= y + yO && fabs(y) > 1))
						moving = 0;
				}
				else
				{
					if (-x > -y)
					{
						xpers = xpers - STEP;
						ypers = ypers - (y / x) / (1 / STEP);
					}
					else
					{
						xpers = xpers - (x / y) / (1 / STEP);
						ypers = ypers - STEP;
					}
					if ((xpers <= x + xO && fabs(x) > 1) || (ypers <= y + yO && fabs(y) > 1))
						moving = 0;
				}
			}
		}
	}

	///////////////////////////////////////////////////////ATTACK

	xf = xmmo;
	yf = ymmo;
	if (attack == 0)
	{
		xOspell = xspell;
		yOspell = yspell;
	}

	if (attack == 1)
	{
		xf = xmmo;
		yf = ymmo;
			if (xf > 0)
			{
				if (yf > 0)
				{
					if (xf > yf)
					{
						if (ability == 1)
						{
							xspell = xspell + FROSTBOLT_SPEED;
							yspell = yspell + (yf / xf) / (1 / FROSTBOLT_SPEED);
						}
						if (ability == 2)
						{
							xspell = xspell + FIREBALL_SPEED;
							yspell = yspell + (yf / xf) / (1 / FIREBALL_SPEED);
						}
						if (ability == 3)
						{
							xspell = xspell + EARTHBALL_SPEED;
							yspell = yspell + (yf / xf) / (1 / EARTHBALL_SPEED);
						}
						if (ability == 4)
						{
							xspell = xspell + MAGIC_ORB_SPEED;
							yspell = yspell + (yf / xf) / (1 / MAGIC_ORB_SPEED);
						}
					}
					else
					{
						if (ability == 1)
						{
							xspell = xspell + (xf / yf) / (1 / FROSTBOLT_SPEED);
							yspell = yspell + FROSTBOLT_SPEED;
						}
						if (ability == 2)
						{
							xspell = xspell + (xf / yf) / (1 / FIREBALL_SPEED);
							yspell = yspell + FIREBALL_SPEED;
						}
						if (ability == 3)
						{
							xspell = xspell + (xf / yf) / (1 / EARTHBALL_SPEED);
							yspell = yspell + EARTHBALL_SPEED;
						}
						if (ability == 4)
						{
							xspell = xspell + (xf / yf) / (1 / MAGIC_ORB_SPEED);
							yspell = yspell + MAGIC_ORB_SPEED;
						}
					}
				}
				else
				{
					if (xf > -yf)
					{
						if (ability == 1)
						{
							xspell = xspell + FROSTBOLT_SPEED;
							yspell = yspell + (yf / xf) / (1 / FROSTBOLT_SPEED);
						}
						if (ability == 2)
						{
							xspell = xspell + FIREBALL_SPEED;
							yspell = yspell + (yf / xf) / (1 / FIREBALL_SPEED);
						}
						if (ability == 3)
						{
							xspell = xspell + EARTHBALL_SPEED;
							yspell = yspell + (yf / xf) / (1 / EARTHBALL_SPEED);
						}
						if (ability == 4)
						{
							xspell = xspell + MAGIC_ORB_SPEED;
							yspell = yspell + (yf / xf) / (1 / MAGIC_ORB_SPEED);
						}
					}
					else
					{
						if (ability == 1)
						{
							xspell = xspell + (xf / (-yf)) / (1 / FROSTBOLT_SPEED);
							yspell = yspell - FROSTBOLT_SPEED;
						}
						if (ability == 2)
						{
							xspell = xspell + (xf / (-yf)) / (1 / FIREBALL_SPEED);
							yspell = yspell - FIREBALL_SPEED;
						}
						if (ability == 3)
						{
							xspell = xspell + (xf / (-yf)) / (1 / EARTHBALL_SPEED);
							yspell = yspell - EARTHBALL_SPEED;
						}
						if (ability == 4)
						{
							xspell = xspell + (xf / (-yf)) / (1 / MAGIC_ORB_SPEED);
							yspell = yspell - MAGIC_ORB_SPEED;
						}
					}
				}
			}
			else /////////////////////////////////////////// X<0
			{
				if (yf > 0)
				{
					if (-xf > yf)
					{
						if (ability == 1)
						{
							xspell = xspell - FROSTBOLT_SPEED;
							yspell = yspell - (yf / xf) / (1 / FROSTBOLT_SPEED);
						}
						if (ability == 2)
						{
							xspell = xspell - FIREBALL_SPEED;
							yspell = yspell - (yf / xf) / (1 / FIREBALL_SPEED);
						}
						if (ability == 3)
						{
							xspell = xspell - EARTHBALL_SPEED;
							yspell = yspell - (yf / xf) / (1 / EARTHBALL_SPEED);
						}
						if (ability == 4)
						{
							xspell = xspell - MAGIC_ORB_SPEED;
							yspell = yspell - (yf / xf) / (1 / MAGIC_ORB_SPEED);
						}
					}
					else
					{
						if (ability == 1)
						{
							xspell = xspell + (xf / yf) / (1 / FROSTBOLT_SPEED);
							yspell = yspell + FROSTBOLT_SPEED;
						}
						if (ability == 2)
						{
							xspell = xspell + (xf / yf) / (1 / FIREBALL_SPEED);
							yspell = yspell + FIREBALL_SPEED;
						}
						if (ability == 3)
						{
							xspell = xspell + (xf / yf) / (1 / EARTHBALL_SPEED);
							yspell = yspell + EARTHBALL_SPEED;
						}
						if (ability == 4)
						{
							xspell = xspell + (xf / yf) / (1 / MAGIC_ORB_SPEED);
							yspell = yspell + MAGIC_ORB_SPEED;
						}
					}
				}
				else
				{
					if (-xf > -yf)
					{
						if (ability == 1)
						{
							xspell = xspell - FROSTBOLT_SPEED;
							yspell = yspell - (yf / xf) / (1 / FROSTBOLT_SPEED);
						}
						if (ability == 2)
						{
							xspell = xspell - FIREBALL_SPEED;
							yspell = yspell - (yf / xf) / (1 / FIREBALL_SPEED);
						}
						if (ability == 3)
						{
							xspell = xspell - EARTHBALL_SPEED;
							yspell = yspell - (yf / xf) / (1 / EARTHBALL_SPEED);
						}
						if (ability == 4)
						{
							xspell = xspell - MAGIC_ORB_SPEED;
							yspell = yspell - (yf / xf) / (1 / MAGIC_ORB_SPEED);
						}
					}
					else
					{
						if (ability == 1)
						{
							xspell = xspell - (xf / yf) / (1 / FROSTBOLT_SPEED);
							yspell = yspell - FROSTBOLT_SPEED;
						}
						if (ability == 2)
						{
							xspell = xspell - (xf / yf) / (1 / FIREBALL_SPEED);
							yspell = yspell - FIREBALL_SPEED;
						}
						if (ability == 3)
						{
							xspell = xspell - (xf / yf) / (1 / EARTHBALL_SPEED);
							yspell = yspell - EARTHBALL_SPEED;
						}
						if (ability == 4)
						{
							xspell = xspell - (xf / yf) / (1 / MAGIC_ORB_SPEED);
							yspell = yspell - MAGIC_ORB_SPEED;
						}
					}
				}
			}
	}
	if (maneken->hp>0)
	if (attack == 1)
		if (ability == 1)
			if ((xmanek - xspell) * (xmanek - xspell) + (ymanek + 0.25 - yspell) * (ymanek + 0.25 - yspell) <= 1 + 0.3)
			{
				if (maneken->hp < frost->damage)
				{
					maneken->hp = 0;
					player->exp = player->exp + 50;
				}
				else
					maneken->hp = maneken->hp - frost->damage;
		attack = 0;
		xspell = xpers;
		yspell = ypers;

		if (player->exp >= 0 && player->exp < player->maxexp - 3)
			player->exp = player->exp + 4;
		else
		{
			player->exp = 0;
			level++;
		}
	}

	if (maneken->hp>0)
		if (attack == 1)
			if (ability == 2)
				if ((xmanek - xspell) * (xmanek - xspell) + (ymanek + 0.25 - yspell) * (ymanek + 0.25 - yspell) <= 1 + 0.5)
				{
					if (maneken->hp < frost->damage)
					{
						maneken->hp = 0;
						player->exp = player->exp + 50;
					}
					else
						maneken->hp = maneken->hp - frost->damage;
					attack = 0;
					xspell = xpers;
					yspell = ypers;

					if (player->exp >= 0 && player->exp < player->maxexp - 7)
						player->exp = player->exp + 8;
					else
					{
						player->exp = 0;
						level++;
					}
				}

	if (maneken->hp>0)
		if (attack == 1)
			if (ability == 3)
				if ((xmanek - xspell) * (xmanek - xspell) + (ymanek + 0.25 - yspell) * (ymanek + 0.25 - yspell) <= 1 + 0.2)
				{
					if (maneken->hp < frost->damage)
					{
						maneken->hp = 0;
						player->exp = player->exp + 50;
					}
					else
						maneken->hp = maneken->hp - frost->damage;
					attack = 0;
					xspell = xpers;
					yspell = ypers;

					if (player->exp >= 0 && player->exp < player->maxexp - 1)
						player->exp = player->exp + 2;
					else
					{
						player->exp = 0;
						level++;
					}
				}

	if (spider->hp > 0)
	{
		if (attack == 1)
			if (ability == 3)
			if ((xspider - xspell) * (xspider - xspell) + (yspider + 0.25 - yspell) * (yspider + 0.25 - yspell) <= 1 + 0.2)
			{
					if (spider->hp < earthball->damage)
						spider->hp = 0;
					else
						spider->hp = spider->hp - earthball->damage;
				attack = 0;
				xspell = xpers;
				yspell = ypers;

				if (player->exp >= 0 && player->exp < player->maxexp)
				{
						player->exp = player->exp + 1;
				}
				else
				{
					player->exp = 0;
					level++;
				}
			}
	}
	else
	{
		if (expgive == 0)
		player->exp = player->exp + 50;
		expgive = 1;
	}

	if (spider->hp > 0)
	{
		if (attack == 1)
			if (ability == 3)
			if ((xspider - xspell) * (xspider - xspell) + (yspider + 0.25 - yspell) * (yspider + 0.25 - yspell) <= 1 + 0.2)
			{
					if (spider->hp < earthball->damage)
						spider->hp = 0;
					else
						spider->hp = spider->hp - earthball->damage;
				attack = 0;
				xspell = xpers;
				yspell = ypers;

				if (player->exp >= 0 && player->exp < player->maxexp)
				{
						player->exp = player->exp + 1;
				}
				else
				{
					player->exp = 0;
					level++;
				}
			}
	}
	else
	{
		if (expgive == 0)
		player->exp = player->exp + 50;
		expgive = 1;
	}

	if (spider->hp > 0)
	{
		if (attack == 1)
			if (ability == 1)
			if ((xspider - xspell) * (xspider - xspell) + (yspider + 0.25 - yspell) * (yspider + 0.25 - yspell) <= 1 + 0.3)
			{
					if (spider->hp < frost->damage)
						spider->hp = 0;
					else
						spider->hp = spider->hp - frost->damage;
				attack = 0;
				xspell = xpers;
				yspell = ypers;

				if (player->exp >= 0 && player->exp < player->maxexp)
				{
					if (ability == 1)
						player->exp = player->exp + 4;
				}
				else
				{
					player->exp = 0;
					level++;
				}
			}
	}
	else
	{
		if (expgive == 0)
			player->exp = player->exp + 50;
		expgive = 1;
	}

	if (spider->hp > 0)
	{
		if (attack == 1)
			if (ability == 2)
			if ((xspider - xspell) * (xspider - xspell) + (yspider + 0.25 - yspell) * (yspider + 0.25 - yspell) <= 1 + 0.5)
			{				
					if (spider->hp < fireb->damage)
						spider->hp = 0;
					else
						spider->hp = spider->hp - fireb->damage;
				attack = 0;
				xspell = xpers;
				yspell = ypers;

				if (player->exp >= 0 && player->exp < player->maxexp)
				{
					if (ability == 1)
						player->exp = player->exp + 2;
					if (ability == 2)
						player->exp = player->exp + 4;
					if (ability == 3)
						player->exp = player->exp + 1;
				}
				else
				{
					player->exp = 0;
					level++;
				}
			}
	}
	else
	{
		if (expgive == 0)
			player->exp = player->exp + 50;
		expgive = 1;
	}

	if ((xspell - xpers) * (xspell - xpers) + (yspell - ypers) * (yspell - ypers) >= RADIUS*RADIUS)
	{
		xspell = xpers;
		yspell = ypers;
		attack = 0;
	}

	//////////////////////////////////////////////// SPIDER MOVE

	/*GLdouble xsp = 0;
	GLdouble ysp = 0;
	if (movingsp == 0)
	{
		xOspider = xspider;
		yOspider = yspider;
		if (xspider > 0)
		{
			xsp = -5;
			ysp = 5;
		}
		if (xspider < 0)
		{
			xsp = 0;
			ysp = -5;
		}
		if (xspider == 0)
		{
			xsp = 5;
			ysp = 5;
		}
	}

	if (movingsp == 1)
	{
		xsp = xmos;
		ysp = ymos;
		if (xspider<79 && xspider>-79 && yspider<79 && yspider>-79)
		{
			if (fabs(xsp) < 1)
				if (ysp > yspider)
					yspider = yspider + STEPSP;
				else
					yspider = yspider - STEPSP;
			if (fabs(ysp) < 1)
				if (xsp > xspider)
					xspider = xspider + STEPSP;
				else
					xspider = xspider - STEPSP;
			if (xsp > 0)
			{
				if (ysp > 0)
				{
					if (xsp > ysp)
					{
						xspider = xspider + STEPSP;
						yspider = yspider + (ysp / xsp) / (1 / STEPSP);
					}
					else
					{
						xspider = xspider + (xsp / ysp) / (1 / STEPSP);
						yspider = yspider + STEPSP;
					}
					if ((xspider >= xsp + xOspider && fabs(xsp) > 1) || (yspider >= ysp + yOspider && fabs(ysp) > 1))
						movingsp = 0;
				}
				else
				{
					if (xsp > -ysp)
					{
						xspider = xspider + STEPSP;
						yspider = yspider + (ysp / xsp) / (1 / STEPSP);
					}
					else
					{
						xspider = xspider + (xsp / (-ysp)) / (1 / STEPSP);
						yspider = yspider - STEPSP;
					}
					if ((xspider >= xsp + xOspider && fabs(xsp) > 1) || (yspider >= -ysp + yOspider && fabs(ysp) > 1))
						movingsp = 0;
				}
			}
			else /////////////////////////////////////////// X<0
			{
				if (ysp > 0)
				{
					if (-xsp > ysp)
					{
						xspider = xspider - STEPSP;
						yspider = yspider - (ysp / xsp) / (1 / STEPSP);
					}
					else
					{
						xspider = xspider + (xsp / ysp) / (1 / STEPSP);
						yspider = yspider + STEPSP;
					}
					if ((xspider >= -xsp + xOspider && fabs(xsp) > 1) || (yspider >= ysp + yOspider && fabs(ysp) > 1))
						movingsp = 0;
				}
				else
				{
					if (-xsp > -ysp)
					{
						xspider = xspider - STEPSP;
						yspider = yspider - (ysp / xsp) / (1 / STEPSP);
					}
					else
					{
						xspider = xspider - (xsp / ysp) / (1 / STEPSP);
						yspider = yspider - STEPSP;
					}
					if ((xspider <= xsp + xOspider && fabs(xsp) > 1) || (yspider <= ysp + yOspider && fabs(ysp) > 1))
						movingsp = 0;
				}
			}
		}
	}
	*/
	////////////////////////////////////////////// SPIDER ATTACK
	/*
	GLdouble xatsp = xpers;
	GLdouble yatsp = ypers;

	xmos = xpers;
	ymos = ypers;

	if (attacksp == 1)
	{
		xatsp = xmos;
		yatsp = ymos;
		if (xatsp > 0)
		{
			if (yatsp > 0)
			{
				if (xatsp > yatsp)
				{
						xspellsp = xspellsp + FROSTBOLT_SPEED;
						yspellsp = yspellsp + (yatsp / xatsp) / (1 / FROSTBOLT_SPEED);
				}
				else
				{
						xspellsp = xspellsp + (xatsp / yatsp) / (1 / FROSTBOLT_SPEED);
						yspellsp = yspellsp + FROSTBOLT_SPEED;
				}
			}
			else
			{
				if (xatsp > -yatsp)
				{
						xspellsp = xspellsp + FROSTBOLT_SPEED;
						yspellsp = yspellsp + (yatsp / xatsp) / (1 / FROSTBOLT_SPEED);
				}
				else
				{
						xspellsp = xspellsp + (xatsp / (-yatsp)) / (1 / FROSTBOLT_SPEED);
						yspellsp = yspellsp - FROSTBOLT_SPEED;
				}
			}
		}
		else /////////////////////////////////////////// X<0
		{
			if (yatsp > 0)
			{
				if (-xatsp > yatsp)
				{
						xspellsp = xspellsp - FROSTBOLT_SPEED;
						yspellsp = yspellsp - (yatsp / xatsp) / (1 / FROSTBOLT_SPEED);
				}
				else
				{
						xspellsp = xspellsp + (xatsp / yatsp) / (1 / FROSTBOLT_SPEED);
						yspellsp = yspellsp + FROSTBOLT_SPEED;
				}
			}
			else
			{
				if (-xatsp > -yatsp)
				{
						xspellsp = xspellsp - FROSTBOLT_SPEED;
						yspellsp = yspellsp - (yatsp / xatsp) / (1 / FROSTBOLT_SPEED);
				}
				else
				{
						xspellsp = xspellsp - (xatsp / yatsp) / (1 / FROSTBOLT_SPEED);
						yspellsp = yspellsp - FROSTBOLT_SPEED;
				}
			}
		}
	}
	if (player->hp>0)
		if (attacksp == 1)
			if ((xmanek - xspellsp) * (xmanek - xspellsp) + (ymanek + 0.25 - yspellsp) * (ymanek + 0.25 - yspellsp) <= 2)
			{
					if (player->hp < frost->damage)
						player->hp = 0;
					else
						player->hp = player->hp - frost->damage;
				attack = 0;
				xspellsp = xpers;
				yspellsp = ypers;

				if (ability == 1)
					if (player->exp < player->maxexp - 7)
					{
							player->exp = player->exp + 4;
					}
					else
					{
						player->exp = 2 - (player->maxexp - player->exp);
						level++;
					}
				if (ability == 2)
					if (player->exp < player->maxexp - 7)
					{
						player->exp = player->exp + 8;
					}
					else
					{
						player->exp = 4 - (player->maxexp - player->exp);
						level++;
					}
			}


	if ((xspellsp - xpers) * (xspellsp - xpers) + (yspellsp - ypers) * (yspellsp - ypers) >= RADIUS*RADIUS)
	{
		xspellsp = xspider;
		yspellsp = yspider;
		attacksp = 0;
	}*/

	gluLookAt(xpers, ypers, 5, xpers, ypers, 0, 0, 1, 0);
}

void floor_pers(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(1.5);
	for (int i = -79; i < 79; i++)
	{
		for (int j = -79; j < 79; j++)
		{
				glBegin(GL_POLYGON);
				glColor3f(0.5, 0.3, 0.1);
				glVertex3f(i, j, 0.0);
				glVertex3f(i, 1 + j, 0.0);
				glVertex3f(1 + i, 1 + j, 0.0);
				glVertex3f(1 + i, j, 0.0);
				glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.5, 0.4, 0.1);
			glVertex3f(0.9 + i, 0.9 + j, 0.01);
			glVertex3f(0.8 + i, 0.9 + j, 0.01);
			glVertex3f(0.8 + i, 0.8 + j, 0.01);
			glVertex3f(0.9 + i, 0.8 + j, 0.01);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.0, 0.7, 0.0);
			glVertex3f(-0.9 + i, -0.65 + j, 0.01);
			glVertex3f(-0.55 + i, -0.65 + j, 0.01);
			glVertex3f(-0.55 + i, -0.8 + j, 0.01);
			glVertex3f(-0.9 + i, -0.8 + j, 0.01);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.6, 0.4, 0.2);
			glVertex3f(-0.4 + i, -0.15 + j, 0.01);
			glVertex3f(-0.05 + i, -0.15 + j, 0.01);
			glVertex3f(-0.05 + i, -0.3 + j, 0.01);
			glVertex3f(-0.4 + i, -0.3 + j, 0.01);
			glEnd();

			glBegin(GL_POLYGON);
			glColor3f(0.6, 0.4, 0.2);
			glVertex3f(-0.9 + i, -0.65 + j, 0.01);
			glVertex3f(-0.55 + i, -0.65 + j, 0.01);
			glVertex3f(-0.55 + i, -0.8 + j, 0.01);
			glVertex3f(-0.9 + i, -0.8 + j, 0.01);
			glEnd();

			/*glBegin(GL_LINE_STRIP);
			glColor3f(0.0, 0.0, 0.0);
			glLineWidth(0.5);
			glVertex3f(-79.5 + i, -79.5 + j, 0.0);
			glVertex3f(-79.5 + i, -78.5 + j, 0.0);
			glVertex3f(-78.5 + i, -78.5 + j, 0.0);
			glVertex3f(-78.5 + i, -79.5 + j, 0.0);
			glVertex3f(-79.5 + i, -79.5 + j, 0.0);
			glEnd();*/
		}
	}

	////////////////////////////// FROSTBOLT
	if (ability == 1)
	if (attack == 1)
	{
		glBegin(GL_QUADS);
		glColor3f(0.3, 0.3, 1.0);
		glVertex3f(xspell - 0.3, yspell - 0.3, 0.01);
		glVertex3f(xspell - 0.3, yspell + 0.3, 0.01);
		glVertex3f(xspell + 0.3, yspell + 0.3, 0.01);
		glVertex3f(xspell + 0.3, yspell - 0.3, 0.01);
		glEnd();
	}

	/////////////////////////////// FIREBALL
	if (ability == 2)
	if (attack == 1)
	{
		glBegin(GL_QUADS);
		glColor3f(0.8, 0.35, 0.0);
		glVertex3f(xspell - 0.5, yspell - 0.7, 0.01);
		glVertex3f(xspell - 0.5, yspell + 0.7, 0.01);
		glVertex3f(xspell + 0.5, yspell + 0.7, 0.01);
		glVertex3f(xspell + 0.5, yspell - 0.7, 0.01);

		glVertex3f(xspell - 0.7, yspell - 0.5, 0.01);
		glVertex3f(xspell - 0.7, yspell + 0.5, 0.01);
		glVertex3f(xspell + 0.7, yspell + 0.5, 0.01);
		glVertex3f(xspell + 0.7, yspell - 0.5, 0.01);

		glVertex3f(xspell - 0.5, yspell - 0.7, 0.011);
		glVertex3f(xspell - 0.5, yspell + 0.7, 0.011);
		glVertex3f(xspell + 0.5, yspell + 0.7, 0.011);
		glVertex3f(xspell + 0.5, yspell - 0.7, 0.011);

		glVertex3f(xspell - 0.7, yspell - 0.5, 0.011);
		glVertex3f(xspell - 0.7, yspell + 0.5, 0.011);
		glVertex3f(xspell + 0.7, yspell + 0.5, 0.011);
		glVertex3f(xspell + 0.7, yspell - 0.5, 0.011);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xspell - 0.5, yspell - 0.7, 0.01);
		glVertex3f(xspell - 0.5, yspell + 0.7, 0.01);
		glVertex3f(xspell + 0.5, yspell + 0.7, 0.01);
		glVertex3f(xspell + 0.5, yspell - 0.7, 0.01);
		glVertex3f(xspell - 0.5, yspell - 0.7, 0.01);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3f(xspell - 0.7, yspell - 0.5, 0.01);
		glVertex3f(xspell - 0.7, yspell + 0.5, 0.01);
		glVertex3f(xspell + 0.7, yspell + 0.5, 0.01);
		glVertex3f(xspell + 0.7, yspell - 0.5, 0.01);
		glVertex3f(xspell - 0.7, yspell - 0.5, 0.01);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3f(xspell - 0.5, yspell - 0.7, 0.011);
		glVertex3f(xspell - 0.5, yspell + 0.7, 0.011);
		glVertex3f(xspell + 0.5, yspell + 0.7, 0.011);
		glVertex3f(xspell + 0.5, yspell - 0.7, 0.011);
		glVertex3f(xspell - 0.5, yspell - 0.7, 0.011);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3f(xspell - 0.7, yspell - 0.5, 0.011);
		glVertex3f(xspell - 0.7, yspell + 0.5, 0.011);
		glVertex3f(xspell + 0.7, yspell + 0.5, 0.011);
		glVertex3f(xspell + 0.7, yspell - 0.5, 0.011);
		glVertex3f(xspell - 0.7, yspell - 0.5, 0.011);
		glEnd();
	}

	////////////////////////////// EARTHBALL
	if (ability == 3)
		if (attack == 1)
		{
			glBegin(GL_QUADS);
			glColor3f(0.2, 0.2, 0.2);
			glVertex3f(xspell - 0.2, yspell - 0.2, 0.01);
			glVertex3f(xspell - 0.2, yspell + 0.2, 0.01);
			glVertex3f(xspell + 0.2, yspell + 0.2, 0.01);
			glVertex3f(xspell + 0.2, yspell - 0.2, 0.01);
			glEnd();
		}

	//////////////////////////// MAGIC ORB
	if (ability == 4)
		if (attack == 1)
	{
		glBegin(GL_QUADS);
		glColor3f(0.3, 0.3, 0.8);
		glVertex3f(xspell - 0.7, yspell - 0.8, 0.01);
		glVertex3f(xspell - 0.7, yspell + 0.8, 0.01);
		glVertex3f(xspell + 0.7, yspell + 0.8, 0.01);
		glVertex3f(xspell + 0.7, yspell - 0.8, 0.01);

		glVertex3f(xspell - 0.8, yspell - 0.7, 0.01);
		glVertex3f(xspell - 0.8, yspell + 0.7, 0.01);
		glVertex3f(xspell + 0.8, yspell + 0.7, 0.01);
		glVertex3f(xspell + 0.8, yspell - 0.7, 0.01);

		glVertex3f(xspell - 0.9, yspell - 0.6, 0.011);
		glVertex3f(xspell - 0.9, yspell + 0.6, 0.011);
		glVertex3f(xspell + 0.9, yspell + 0.6, 0.011);
		glVertex3f(xspell + 0.9, yspell - 0.6, 0.011);

		glVertex3f(xspell - 0.6, yspell - 0.9, 0.011);
		glVertex3f(xspell - 0.6, yspell + 0.9, 0.011);
		glVertex3f(xspell + 0.6, yspell + 0.9, 0.011);
		glVertex3f(xspell + 0.6, yspell - 0.9, 0.011);
		glEnd();
	}

	////////////////////////////// INVENTORY
	/*if (invent == 1)
	{
		glBegin(GL_QUADS);
		glColor3f(0.3, 0.1, 0.0);
		glVertex3f(xpers - 20, ypers - 15, 0.05);
		glVertex3f(xpers + 20, ypers - 15, 0.05);
		glVertex3f(xpers + 20, ypers + 15, 0.05);
		glVertex3f(xpers - 20, ypers + 15, 0.05);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.5, 0.3, 0.2);
		glVertex3f(xpers - 18, ypers + 12, 0.06);
		glVertex3f(xpers - 13, ypers + 12, 0.06);
		glVertex3f(xpers - 13, ypers + 9, 0.06);
		glVertex3f(xpers - 18, ypers + 9, 0.06);
		glEnd();
	}*/

	/////////////////////////////////// BODY
	{
		glBegin(GL_QUADS);
		glColor3f(0.3, 0.3, 0.3);

		glVertex3f(xpers - 0.05, ypers, 0.03);
		glVertex3f(xpers - 0.4, ypers, 0.03);
		glVertex3f(xpers - 0.4, ypers - 0.8, 0.03);
		glVertex3f(xpers - 0.05, ypers - 0.8, 0.03);

		glVertex3f(xpers + 0.05, ypers, 0.03);
		glVertex3f(xpers + 0.4, ypers, 0.03);
		glVertex3f(xpers + 0.4, ypers - 0.8, 0.03);
		glVertex3f(xpers + 0.05, ypers - 0.8, 0.03);

		glVertex3f(xpers + 0.4, ypers + 0.01, 0.03);
		glVertex3f(xpers - 0.4, ypers + 0.01, 0.03);
		glVertex3f(xpers - 0.45, ypers + 0.8, 0.03);
		glVertex3f(xpers + 0.45, ypers + 0.8, 0.03);

		glVertex3f(xpers + 0.45, ypers + 0.75, 0.03);
		glVertex3f(xpers + 0.7, ypers + 0.75, 0.03);
		glVertex3f(xpers + 0.7, ypers - 0.1, 0.03);
		glVertex3f(xpers + 0.45, ypers - 0.1, 0.03);

		glVertex3f(xpers - 0.45, ypers + 0.75, 0.03);
		glVertex3f(xpers - 0.7, ypers + 0.75, 0.03);
		glVertex3f(xpers - 0.7, ypers - 0.1, 0.03);
		glVertex3f(xpers - 0.45, ypers - 0.1, 0.03);

		glColor3f(0.9, 0.6, 0.3);
		glVertex3f(xpers - 0.3, ypers + 0.8, 0.03);
		glVertex3f(xpers - 0.3, ypers + 1.4, 0.03);
		glVertex3f(xpers + 0.3, ypers + 1.4, 0.03);
		glVertex3f(xpers + 0.3, ypers + 0.8, 0.03);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);

		glVertex3f(xpers - 0.05, ypers, 0.03);
		glVertex3f(xpers - 0.4, ypers, 0.03);
		glVertex3f(xpers - 0.4, ypers - 0.8, 0.03);
		glVertex3f(xpers - 0.05, ypers - 0.8, 0.03);
		glVertex3f(xpers - 0.05, ypers, 0.03);

		glVertex3f(xpers + 0.05, ypers, 0.03);
		glVertex3f(xpers + 0.4, ypers, 0.03);
		glVertex3f(xpers + 0.4, ypers - 0.8, 0.03);
		glVertex3f(xpers + 0.05, ypers - 0.8, 0.03);
		glVertex3f(xpers + 0.05, ypers, 0.03);

		glVertex3f(xpers + 0.4, ypers + 0.01, 0.04);
		glVertex3f(xpers - 0.4, ypers + 0.01, 0.04);
		glVertex3f(xpers - 0.45, ypers + 0.8, 0.04);
		glVertex3f(xpers + 0.45, ypers + 0.8, 0.04);
		glVertex3f(xpers + 0.4, ypers + 0.01, 0.04);

		glVertex3f(xpers + 0.45, ypers + 0.75, 0.03);
		glVertex3f(xpers + 0.7, ypers + 0.75, 0.03);
		glVertex3f(xpers + 0.7, ypers - 0.1, 0.03);
		glVertex3f(xpers + 0.45, ypers - 0.1, 0.03);
		glVertex3f(xpers + 0.45, ypers + 0.75, 0.03);

		glVertex3f(xpers - 0.45, ypers + 0.8, 0.03);
		glVertex3f(xpers - 0.7, ypers + 0.75, 0.03);
		glVertex3f(xpers - 0.7, ypers - 0.1, 0.03);
		glVertex3f(xpers - 0.45, ypers - 0.1, 0.03);
		glVertex3f(xpers - 0.45, ypers + 0.8, 0.03);

		glVertex3f(xpers - 0.3, ypers + 0.8, 0.03);
		glVertex3f(xpers - 0.3, ypers + 1.4, 0.03);
		glVertex3f(xpers + 0.3, ypers + 1.4, 0.03);
		glVertex3f(xpers + 0.3, ypers + 0.8, 0.03);
		glVertex3f(xpers - 0.3, ypers + 0.8, 0.03);

		glEnd();
	}

	/////////////////////////////////// CUBE
	/*
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f( xpers - 0.5,  ypers - 0.5, 0);
	glVertex3f( xpers + 0.5,  ypers - 0.5, 0);
	glVertex3f( xpers + 0.5,  ypers - 0.5, 1);
	glVertex3f( xpers - 0.5,  ypers - 0.5, 1);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f( xpers + 0.5,  ypers + 0.5, 0);
	glVertex3f( xpers + 0.5,  ypers - 0.5, 0);
	glVertex3f( xpers + 0.5,  ypers - 0.5, 1);
	glVertex3f( xpers + 0.5,  ypers + 0.5, 1);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f( xpers - 0.5, ypers + 0.5, 0);
	glVertex3f( xpers + 0.5,  ypers + 0.5, 0);
	glVertex3f( xpers + 0.5,  ypers + 0.5, 1);
	glVertex3f( xpers - 0.5,  ypers + 0.5, 1);

	glColor3f(1.0, 0.7, 0.3);
	glVertex3f( xpers - 0.5, ypers - 0.5, 1);
	glVertex3f( xpers + 0.5, ypers - 0.5, 1);
	glVertex3f( xpers + 0.5, ypers + 0.5, 1);
	glVertex3f( xpers - 0.5, ypers + 0.5, 1);

	glColor3f(1.0, 0.0, 1.0);
	glVertex3f( xpers - 0.5, ypers - 0.5, 0);
	glVertex3f( xpers - 0.5, ypers + 0.5, 0);
	glVertex3f( xpers - 0.5, ypers + 0.5, 1);
	glVertex3f( xpers - 0.5, ypers - 0.5, 1);

	glColor3f(0.0, 1.0, 1.0);
	glVertex3f( xpers + 0.5, ypers + 0.5, 0);
	glVertex3f( xpers + 0.5, ypers - 0.5, 0);
	glVertex3f( xpers + 0.5, ypers - 0.5, 0);
	glVertex3f( xpers + 0.5, ypers + 0.5, 0);
	glEnd();*/

	//////////////////////////////////BOTTOM
	if (1==1)
	{
		glBegin(GL_QUADS);
		glColor3f(0.35, 0.3, 0.15);
		glVertex3f(xpers - 20, ypers - 7.8, 0.02);
		glVertex3f(xpers - 20, ypers - 15, 0.02);
		glVertex3f(xpers + 20, ypers - 15, 0.02);
		glVertex3f(xpers + 20, ypers - 7.8, 0.02);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers - 10, ypers - 8.5, 0.03);
		glVertex3f(xpers + 10, ypers - 8.5, 0.03);
		glVertex3f(xpers + 10, ypers - 9.2, 0.03);
		glVertex3f(xpers - 10, ypers - 9.2, 0.03);
		glVertex3f(xpers - 10, ypers - 8.5, 0.03);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers - 10, ypers - 9.7, 0.03);
		glVertex3f(xpers + 10, ypers - 9.7, 0.03);
		glVertex3f(xpers + 10, ypers - 10.4, 0.03);
		glVertex3f(xpers - 10, ypers - 10.4, 0.03);
		glVertex3f(xpers - 10, ypers - 9.7, 0.03);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(2);
		glVertex3f(xpers - 10, ypers - 11.6, 0.03);
		glVertex3f(xpers + 10, ypers - 11.6, 0.03);
		glVertex3f(xpers + 10, ypers - 10.9, 0.03);
		glVertex3f(xpers - 10, ypers - 10.9, 0.03);
		glVertex3f(xpers - 10, ypers - 11.6, 0.03);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.6, 0.0, 0.0);
		glVertex3f(xpers - 9.95, ypers - 8.5, 0.04);
		glVertex3f(xpers - 9.95 + 19.9 * player->hp / player->maxhp, ypers - 8.5, 0.04);
		glVertex3f(xpers - 9.95 + 19.9 * player->hp / player->maxhp, ypers - 9.2, 0.04);
		glVertex3f(xpers - 9.95, ypers - 9.2, 0.04);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers - 9.95, ypers - 8.5, 0.04);
		glVertex3f(xpers + 9.95, ypers - 8.5, 0.04);
		glVertex3f(xpers + 9.95, ypers - 9.2, 0.04);
		glVertex3f(xpers - 9.95, ypers - 9.2, 0.04);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 0.8);
		glVertex3f(xpers - 10.0, ypers - 9.7, 0.04);
		glVertex3f(xpers - 9.95 + 19.9 * player->mana / player->maxmana, ypers - 9.7, 0.04);
		glVertex3f(xpers - 9.95 + 19.9 * player->mana / player->maxmana, ypers - 10.4, 0.04);
		glVertex3f(xpers - 10.0, ypers - 10.4, 0.04);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers - 10.0, ypers - 9.7, 0.04);
		glVertex3f(xpers + 10.0, ypers - 9.7, 0.04);
		glVertex3f(xpers + 10.0, ypers - 10.4, 0.04);
		glVertex3f(xpers - 10.0, ypers - 10.4, 0.04);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(xpers - 10.0, ypers - 10.9, 0.04);
		glVertex3f(xpers - 9.95 + 19.9 * player->exp / player->maxexp, ypers - 10.9, 0.04);
		glVertex3f(xpers - 9.95 + 19.9 * player->exp / player->maxexp, ypers - 11.6, 0.04);
		glVertex3f(xpers - 10.0, ypers - 11.6, 0.04);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers - 10.0, ypers - 10.9, 0.04);
		glVertex3f(xpers + 10.0, ypers - 10.9, 0.04);
		glVertex3f(xpers + 10, ypers - 11.6, 0.04);
		glVertex3f(xpers - 10.0, ypers - 11.6, 0.04);
		glEnd();

		/////////////////////////////// ABILITIES
		{
			glBegin(GL_QUADS);
			glColor3f(0.0, 0.0, 0.0);
			glVertex3f(xpers - 9.8, ypers - 11.8, 0.04);
			glVertex3f(xpers - 7, ypers - 11.8, 0.04);
			glVertex3f(xpers - 7, ypers - 14, 0.04);
			glVertex3f(xpers - 9.8, ypers - 14, 0.04);

			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(xpers - 9.5, ypers - 12.1, 0.05);
			glVertex3f(xpers - 7.3, ypers - 12.1, 0.05);
			glVertex3f(xpers - 7.3, ypers - 13.7, 0.05);
			glVertex3f(xpers - 9.5, ypers - 13.7, 0.05);

			glColor3f(0.1, 0.1, 1.0);
			glVertex3f(xpers - 8.8, ypers - 12.5, 0.06);
			glVertex3f(xpers - 8, ypers - 12.5, 0.06);
			glVertex3f(xpers - 8, ypers - 13.3, 0.06);
			glVertex3f(xpers - 8.8, ypers - 13.3, 0.06);

			if (level >= 2)
			{
				glColor3f(0.0, 0.0, 0.0);
				glVertex3f(xpers - 6.5, ypers - 11.8, 0.04);
				glVertex3f(xpers - 3.7, ypers - 11.8, 0.04);
				glVertex3f(xpers - 3.7, ypers - 14, 0.04);
				glVertex3f(xpers - 6.5, ypers - 14, 0.04);

				glColor3f(1.0, 1.0, 1.0);
				glVertex3f(xpers - 6.2, ypers - 12.1, 0.05);
				glVertex3f(xpers - 4, ypers - 12.1, 0.05);
				glVertex3f(xpers - 4, ypers - 13.7, 0.05);
				glVertex3f(xpers - 6.2, ypers - 13.7, 0.05);

				glColor3f(0.8, 0.35, 0.0);
				glVertex3f(xpers - 5.6, ypers - 12.5, 0.06);
				glVertex3f(xpers - 4.6, ypers - 12.5, 0.06);
				glVertex3f(xpers - 4.6, ypers - 13.3, 0.06);
				glVertex3f(xpers - 5.6, ypers - 13.3, 0.06);
			}

			if (level >= 3)
			{
				glColor3f(0.0, 0.0, 0.0);
				glVertex3f(xpers - 3.2, ypers - 11.8, 0.04);
				glVertex3f(xpers - 0.4, ypers - 11.8, 0.04);
				glVertex3f(xpers - 0.4, ypers - 14, 0.04);
				glVertex3f(xpers - 3.2, ypers - 14, 0.04);

				glColor3f(1.0, 1.0, 1.0);
				glVertex3f(xpers - 2.9, ypers - 12.1, 0.05);
				glVertex3f(xpers - 0.7, ypers - 12.1, 0.05);
				glVertex3f(xpers - 0.7, ypers - 13.7, 0.05);
				glVertex3f(xpers - 2.9, ypers - 13.7, 0.05);

				glColor3f(0.2, 0.2, 0.2);
				glVertex3f(xpers - 2, ypers - 12.7, 0.06);
				glVertex3f(xpers - 1.6, ypers - 12.7, 0.06);
				glVertex3f(xpers - 1.6, ypers - 13.1, 0.06);
				glVertex3f(xpers - 2, ypers - 13.1, 0.06);
				glEnd();
			}

			if (level >= 5)
			{
				glBegin(GL_QUADS);
				glColor3f(0.0, 0.0, 0.0);
				glVertex3f(xpers + 0.1, ypers - 11.8, 0.04);
				glVertex3f(xpers + 2.9, ypers - 11.8, 0.04);
				glVertex3f(xpers + 2.9, ypers - 14, 0.04);
				glVertex3f(xpers + 0.1, ypers - 14, 0.04);

				glColor3f(1.0, 1.0, 1.0);
				glVertex3f(xpers + 0.4, ypers - 12.1, 0.05);
				glVertex3f(xpers + 2.6, ypers - 12.1, 0.05);
				glVertex3f(xpers + 2.6, ypers - 13.7, 0.05);
				glVertex3f(xpers + 0.4, ypers - 13.7, 0.05);

				glColor3f(0.3, 0.3, 0.8);
				glVertex3f(xpers + 0.8, ypers - 12.3, 0.06);
				glVertex3f(xpers + 2.2, ypers - 12.3, 0.06);
				glVertex3f(xpers + 2.2, ypers - 13.5, 0.06);
				glVertex3f(xpers + 0.8, ypers - 13.5, 0.06);
				glEnd();
			}

			if (ability == 1)
			{
				glBegin(GL_QUADS);
				glColor3f(0.7, 0.7, 0.3);
				glVertex3f(xpers - 9.9, ypers - 11.7, 0.04);
				glVertex3f(xpers - 6.9, ypers - 11.7, 0.04);
				glVertex3f(xpers - 6.9, ypers - 14.1, 0.04);
				glVertex3f(xpers - 9.9, ypers - 14.1, 0.04);
				glEnd();
			}
			if (ability == 2)
			{
				glBegin(GL_QUADS);
				glColor3f(0.7, 0.7, 0.3);
				glVertex3f(xpers - 6.6, ypers - 11.7, 0.04);
				glVertex3f(xpers - 3.6, ypers - 11.7, 0.04);
				glVertex3f(xpers - 3.6, ypers - 14.1, 0.04);
				glVertex3f(xpers - 6.6, ypers - 14.1, 0.04);
				glEnd();
			}
			if (ability == 3)
			{
				glBegin(GL_QUADS);
				glColor3f(0.7, 0.7, 0.3);
				glVertex3f(xpers - 3.3, ypers - 11.7, 0.04);
				glVertex3f(xpers - 0.3, ypers - 11.7, 0.04);
				glVertex3f(xpers - 0.3, ypers - 14.1, 0.04);
				glVertex3f(xpers - 3.3, ypers - 14.1, 0.04);
				glEnd();
			}
			if (ability == 4)
			{
				glBegin(GL_QUADS);
				glColor3f(0.7, 0.7, 0.3);
				glVertex3f(xpers - 0, ypers - 11.7, 0.04);
				glVertex3f(xpers + 3, ypers - 11.7, 0.04);
				glVertex3f(xpers + 3, ypers - 14.1, 0.04);
				glVertex3f(xpers - 0, ypers - 14.1, 0.04);
				glEnd();
			}

		}
	}

	//////////////////////////////// MANEKEN
	if (maneken->hp>0)
	{
		glBegin(GL_QUADS);
		glColor3f(0.7, 0.5, 0.1);
		glVertex3f(xmanek - 0.5, ymanek - 0.3, 0.02);
		glVertex3f(xmanek - 0.5, ymanek - 0.5, 0.02);
		glVertex3f(xmanek + 0.5, ymanek - 0.5, 0.02);
		glVertex3f(xmanek + 0.5, ymanek - 0.3, 0.02);

		glVertex3f(xmanek - 0.1, ymanek - 0.3, 0.02);
		glVertex3f(xmanek - 0.1, ymanek, 0.02);
		glVertex3f(xmanek + 0.1, ymanek, 0.02);
		glVertex3f(xmanek + 0.1, ymanek - 0.3, 0.02);

		glVertex3f(xmanek - 0.45, ymanek + 0.8, 0.02);
		glVertex3f(xmanek - 0.45, ymanek, 0.02);
		glVertex3f(xmanek + 0.45, ymanek, 0.02);
		glVertex3f(xmanek + 0.45, ymanek + 0.8, 0.02);

		glVertex3f(xmanek + 0.45, ymanek + 0.75, 0.02);
		glVertex3f(xmanek + 0.45, ymanek + 0.5, 0.02);
		glVertex3f(xmanek + 0.85, ymanek + 0.5, 0.02);
		glVertex3f(xmanek + 0.85, ymanek + 0.75, 0.02);

		glVertex3f(xmanek - 0.45, ymanek + 0.75, 0.02);
		glVertex3f(xmanek - 0.45, ymanek + 0.5, 0.02);
		glVertex3f(xmanek - 0.85, ymanek + 0.5, 0.02);
		glVertex3f(xmanek - 0.85, ymanek + 0.75, 0.02);
		glEnd();

		////////////////////////// HP / MANA

		glBegin(GL_QUADS);
		glColor3f(0.6, 0.0, 0.0);
		glVertex3f(xpers - 10.0 + 20.0 * maneken->hp / maneken->maxhp, ypers + 14.0, 0.05);
		glVertex3f(xpers - 10.0, ypers + 14.0, 0.05);
		glVertex3f(xpers - 10.0, ypers + 13.5, 0.05);
		glVertex3f(xpers - 10.0 + 20.0 * maneken->hp / maneken->maxhp, ypers + 13.5, 0.05);

		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers + 10, ypers + 14.0, 0.05);
		glVertex3f(xpers - 10.0, ypers + 14.0, 0.05);
		glVertex3f(xpers - 10.0, ypers + 13.5, 0.05);
		glVertex3f(xpers + 10, ypers + 13.5, 0.05);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xpers + 10, ypers + 14, 0.05);
		glVertex3f(xpers - 10, ypers + 14, 0.05);
		glVertex3f(xpers - 10, ypers + 13.5, 0.05);
		glVertex3f(xpers + 10, ypers + 13.5, 0.05);
		glVertex3f(xpers + 10, ypers + 14, 0.05);

		glEnd();
	}

	///////////////////////////////// SPIDER
	if (spider->hp>0)
	{
		glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(xspider-0.4, yspider-0.4, 0.02);
		glVertex3f(xspider-0.4, yspider+0.4, 0.02);
		glVertex3f(xspider+0.4, yspider+0.4, 0.02);
		glVertex3f(xspider+0.4, yspider-0.4, 0.02);
		glEnd();
	}

	glutPostRedisplay();

	glPopMatrix();
	glLoadIdentity();
	glutSwapBuffers();
	if (GOD_MOD == 1)
	{
		if (player->mana < player->maxmana)
			player->mana = player->mana + 2;
		if (player->hp < player->maxhp)
			player->hp = player->hp + 2;
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, wid, hei);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -15, 15, -20, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xpers, ypers, 5, xpers, ypers, 0, 0, 1, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		if (invent == 0)
			invent = 1;
		else
			invent = 0;
		break;
	case 'g':
		if (GOD_MOD == 0)
			GOD_MOD = 1;
		else
			GOD_MOD = 0;
		break;
	case ' ':
		if (attack == 1)
			if (ability == 4)
			{
				xpers = xspell;
				ypers = yspell;
				attack = 0;
			}
				break;
	case '1':
		if (attack == 0)
			if (level>=1)
		ability = 1;
		break;
	case '2':
		if (attack == 0)
			if (level >= 2)
		ability = 2;
		break;
	case '3':
		if (attack == 0)
			if (level >= 3)
		ability = 3;
		break;
	case '4':
		if (attack == 0)
			if (level >= 5)
		ability = 4;
		break;
	case '9':
		if (attack == 0)
			if (level >= 6)
				ability = 9;
		break;
	case 'u':
		// heal 10
		for (int i = 0; i < 10; i++)
		{
			if (player->hp < player->maxhp)
			player->hp = player->hp + 1;
		}
		break;
	case 'y':
		// damage 10
		for (int i = 0; i < 10; i++)
		{
			if (player->hp > 0)
			player->hp = player->hp - 1;
		}
		break;
	case 'h':
		// -10 mana
		for (int i = 0; i < 10; i++)
		{
			if (player->mana > 0)
				player->mana = player->mana - 1;
		}
		break;
	case 'j':
		// + 10 mana
		for (int i = 0; i < 10; i++)
		{
			if (player->mana < player->maxmana)
				player->mana = player->mana + 1;
		}
		break;
	default:
		break;
	}
}



int main(int argc, char **argv)
{
	player->level = level;
	player->mana = 70;
	player->maxmana = 80 + player->level * 10;
	player->hp = 10;
	player->maxhp = 80 + player->level * 10;
	player->exp = 0;
	player->maxexp = 100 + player->level * 10;
	player->damage = 10;

	spider->level = level;
	spider->mana = 10;
	spider->maxmana = 10 + spider->level * 1;
	spider->hp = 200;
	spider->maxhp = 80 + spider->level * 10;
	spider->exp = 0;
	spider->maxexp = 100 + spider->level * 1;
	spider->damage = 20;

	frost->manacost = 8;
	frost->damage = 15;

	fireb->manacost = 16;
	fireb->damage = 30;

	earthball->manacost = 4;
	earthball->damage = 7;

	magic_orb->manacost = 20;
	magic_orb->damage = 0;

	maneken->level = 1;
	maneken->mana = 100;
	maneken->maxmana = 100;
	maneken->hp = 5000;
	maneken->maxhp = 5000;
	maneken->exp = 1;
	maneken->maxexp = 100;
	maneken->damage = 1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(wid, hei);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("TIPADIABLO");
	init();
	glutIdleFunc(calculate);
	glutDisplayFunc(floor_pers);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	free(player);
	free(maneken);
	free(fireb);
	free(frost);
	free(earthball);
	return 0;
}