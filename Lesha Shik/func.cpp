#include <stdio.h>
#include <math.h>
#include <time.h>
#include "structs.h"

void Collison(Sphere *ball, Plate *table, char *next_player, GLint *touch) {
	if (ball->Y <= table->Y + ball->R && ball->X >= -10 - ball->R && ball->X <= 15 + ball->R && ball->Z >= -40 + ball->R && ball->Z <= 30 - ball->R){
		ball->SpdX = (GLfloat)0.6 * ball->SpdX; /*(ball->Mass * ball->SpdX) / (ball->Mass + table->Mass);*/
		ball->SpdY = (GLfloat)-0.8 * ball->SpdY; /*(ball->Mass * ball->SpdY) / (ball->Mass + table->Mass);*/
		ball->SpdZ = (GLfloat)0.6 * ball->SpdZ; /*(ball->Mass * ball->SpdZ) / (ball->Mass + table->Mass);*/

		(*touch)++;
		if (*next_player == 'b' && ball->Z >= -5 && *touch >= 0){
			glutCreateWindow("You Lose Wrong Side");
			Sleep(1000);
			glutDestroyWindow(1);
		}
		if (*touch >= 2){
			if (ball->Z >= -5)
				glutCreateWindow("You Lose Double Touch");
			else
			if (ball->Z <= -5)
				glutCreateWindow("You Win Double Touch");
			Sleep(1000);
			glutDestroyWindow;
		}
		if (*touch < 0)
			*touch = 1;
	}//остановка шарика на столе
	if (ball->Y <= table->Y + ball->R && ball->SpdY <= 0 && ball->X >= -10 - ball->R && ball->X <= 15 + ball->R && ball->Z >= -40 + ball->R && ball->Z <= 30 - ball->R){
		ball->AclY = 0;
		ball->SpdY = 0;
	}
}

void Shot(Sphere *ball, Raketka *raketka, char *next_player, GLint *touch){
	if (raketka->X - 10 <= ball->X + ball->R && raketka->X + 10 >= ball->X - ball->R && raketka->Y - 10 <= ball->Y + ball->R && raketka->Y + 10 >= ball->Y - ball->R){
		if (ball->SpdX != 0.0)
			ball->SpdX *= -1.2;
		else
			if (ball->X >= 5)
				ball->SpdX = -0.1;
			else
				ball->SpdX = 0.1;
		ball->SpdY = 0.8;
		if (ball->SpdZ != 0.0)
			if (ball->Z <= -15)
				ball->SpdZ *= -3;
			else
				ball->SpdZ *= -2.2;
		else
			ball->SpdZ = -0.4;
		ball->SpdY = 0.4;
		*next_player = 'b';
		*touch = 0;
	}
}

void BOT(Sphere *ball, char *next_player, GLint *touch){
	GLint I;
	if (ball->X >= 5) 
		I = rand() % (4);
	else
		I = rand() % (4) + 3;
	ball->SpdX = randomX[I];
	ball->SpdZ *= -randomZ[I];//-1.3;
	ball->SpdY = 0.5;
	*next_player = 'p';
	*touch = 0;
}

void Setka(Sphere *ball, char *next_player){
	if (ball->Z <= 0 && ball->Z >= -10 && ball->Y <= 5){
		if (*next_player == 'p')
			glutCreateWindow("You Win Setka");
		else
			glutCreateWindow("You Lose Setka");
		Sleep(1000);
		glutDestroyWindow;
	}
}

void Lose(Sphere *ball, Plate *table, char *next_player, GLint *touch){
	if ((ball->Y <= table->Y + ball->R && (ball->X <= -10 || ball->X >= 15 || ball->Z <= -40 || ball->Z >= 30)) || ball->AclY == 0){
		if (*next_player == 'b')
			if (((ball->X <= -10 || ball->X >= 15 || ball->Z <= -40) && *touch == 1))
				glutCreateWindow("You Win1");
			else
				if (*touch == 0)
					glutCreateWindow("You Lose1");
		if (*next_player == 'p')
			if (((ball->X <= -10 || ball->X >= 15 || ball->Z >= 30) && *touch == 1))
				glutCreateWindow("You Lose2");
			else
				if (*touch == 0)
					glutCreateWindow("You Win2");
		Sleep(1000);
		glutDestroyWindow(2);
	}
}


