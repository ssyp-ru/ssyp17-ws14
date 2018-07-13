#ifndef a30072044
#define a30072044

#include <stdio.h>
#include <math.h>
#include "include\GL\freeglut.h"
 
const GLdouble randomZ[8] = {1.2, 1.2, 1.3, 1.3, 1.4, 1.4, 1.5, 1.6};
const GLdouble randomX[7] = {-0.07, -0.05, -0.02, 0, 0.02, 0.05, 0.07};

typedef struct Raketka{
	GLdouble X = 1000, Y = 1000;
	const GLdouble Mass = 0.6, R = 5;
}Raketka;

typedef struct Plate {
	const GLdouble X = 10, Y = 0, Z = -30,
	W = 10, H = 30,
	SpdX = 0, SpdY = 0, SpdZ = 0,
	Mass = 10;
} Plate; //стол

typedef struct Sphere {
	GLdouble X = 5, Y = 40, Z = 20,
	SpdX = 0, SpdY = 0.0, SpdZ = 0,
	AclX = 0, AclY = -0.0098, AclZ = 0,
	Mass = 0.1, R = 1.4;
} Sphere; //шарик

void Collison(Sphere *ball, Plate *table, char *next_player, GLint *touch);

void Shot(Sphere *ball, Raketka *raketka, char *next_player, GLint *touch);

void BOT(Sphere *ball, char *next_player, GLint *touch);

void Setka(Sphere *ball, char *next_player);

void Lose(Sphere *ball, Plate *table, char *next_player, GLint *touch);


#endif