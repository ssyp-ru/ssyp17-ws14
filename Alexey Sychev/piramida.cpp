#include "Windows.h"
#include "stdlib.h"
#include "stdio.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "time.h"

double xp = 0, yp =0, zp = 0;
double xcam = 0.6, ycam = 0.8, zcam = 0.3;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Установить проекцию
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-300.0, 300.0, -300.0, 300.0, -300.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(xcam, ycam, zcam, 2.0, 1.0, 0.0 , 7.5, 1.0, 3.0);
}

struct room
{
	int up;
	int down;
	int right;
	int left;
	int value;
};

room** a = (room**)malloc(sizeof(room) * 5);

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '4':
		glRotated(-0.5, 0, 0, 1);
		glutPostRedisplay();
		break;
	case '6':
		glRotated(0.5, 0, 0, 1);
		glutPostRedisplay();
		break;
	case 'W':
	case 'w':
		//glLoadIdentity();
		//glRotatef(1, 1.0, 0.0, 0.0);
		
		xp = xp + 0.01;
		glTranslated(-xp, 0, 0);
		xp = 0;
		glutPostRedisplay();
		break;
	case 'D':
	case 'd':
		//glLoadIdentity();
		//glRotatef(1, 1.0, 0.0, 0.0);

		yp = yp + 0.01;
		glTranslated(0, yp, 0);
		yp = 0;
		glutPostRedisplay();
		break;
	case 'A':
	case 'a':
		//glLoadIdentity();
		//glRotatef(1, 1.0, 0.0, 0.0);

		yp = yp + 0.01;
		glTranslated(0, -yp, 0);
		yp = 0;
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		xp = xp + 0.01;
		glTranslated(xp, 0, 0);
		xp = 0;
		//glRotatef(-1, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '8':
		zp = zp + 0.01;
		glTranslated(0, 0, -zp);
		zp = 0;
		//glRotatef(-1, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '5':
		zp = zp + 0.01;
		glTranslated(0, 0, zp);
		zp = 0;
		//glRotatef(1, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '2':
		glRotated(-1, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void generaL(room **mass, int size)
{
	//Создание границ

	//Заполнение 1 строки стенками
	// step 1&2
	(mass[0][0]).left = 1;
	(mass[size - 1][0]).right = 1;
	for (int i = 0; i < size; ++i)
	{
		(mass[i][0]).down = 1;
		(mass[i][0]).up = 1;

		//Присваивание чисел элементам 1 строки массива их множеств
		(mass[i][0]).value = i + 1;
	}
	//step 3
	//Боковые стенки на 1 строке
	for (int i = 0; i < size; ++i)
	{
		if (rand() % 2 + 1 == 1)
		{
			if (i != 0)
			{
				for (int r = 0; r < i && (mass[i - r - 1][0]).right != 1; ++r)
					(mass[i - r - 1][0]).value = (mass[i - r][0]).value;
			}
			(mass[i][0]).right = 1;
		}
	}
	// step 4
	//Нижние стенки на 1 строке
	for (int i = 0; i < size; i++)
	{
		if (rand() % 2 + 0 == 1)
		{
			(mass[i][0]).down = 0;
		}
	}
	for (int count = 0, i = 0; i < size; i++)
	{
		if ((mass[i][0]).down == 1)
		{
			count = 1;
		}
		if (i < size - 1)
		{
			if (count == 1 && (mass[i + 1][0]).down == 1)
			{
				if (count == 1 && (mass[i + 1][0]).right == 1)
				{
					(mass[i][0]).down = 0;
					while ((mass[i][0]).right != 1) i++;
				}
			}
		}
	}

	//step 5(1&2)
	for (int j = 1; j < size; j++)
	{
		for (int i = 0; i < size; ++i)
		{
			//Заполнение 2 - предпоследней строк
			(mass[0][j]).left = 1;
			(mass[size - 1][j]).right = 1;
			(mass[i][j]).down = 1;
			//Присваивание чисел элементам от 2 до предпоследней строк массива их множеств
			(mass[i][j]).value = i + 1;
		}
	}
	//step 3
	for (int j = 1; j < size - 1; j++)
	{
		for (int i = 0; i < size; i++)
		{
			if (rand() % 2 + 1 == 1)
			{
				if (i != 0)
				{
					for (int r = 0; r < i && (mass[i - r - 1][j]).right != 1; ++r)
						(mass[i - r - 1][j]).value = (mass[i - r][j]).value;
				}
				(mass[i][j]).right = 1;
			}
		}
	}
	// step 4
	//Нижние стенки на 2 до предпоследней строк строке

	for (int j = 1; j < size - 1; ++j)
	{
		for (int i = 0; i < size; ++i)
		{
			if (rand() % 2 + 0 == 1)
			{
				(mass[i][j]).down = 0;
			}
		}
		for (int count = 0, i = 0; i < size; ++i)
		{
			if ((mass[i][j]).down == 1) count = 1;
			if (i < size - 1)
			{
				if (count == 0 && (mass[i + 1][j]).down == 1)
				{
					if (count == 0 && (mass[i + 1][j]).right == 1)
					{

						(mass[i][j]).down = 0;
						while ((mass[i][j]).right != 1) ++i;

					}
				}
			}
		}
	}
	//step 1&2

	(mass[0][size - 1]).left = 1;
	(mass[size - 1][size - 1]).right = 1;
	for (int i = 0; i < size; ++i)
	{
		(mass[i][size - 1]).down = 1;

		//Присваивание чисел элементам последней строки массива их множеств
		(mass[i][size - 1]).value = i + 1;
	}
	(mass[3][0]).right = 0;
	//step 3

	for (int i = 0; i < size; ++i)
	{
		if (rand() % 2 + 1 == 1)
		{
			if (i != 0)
			{
				for (int r = 0; r < i && (mass[i - r - 1][size - 1]).right != 1; ++r)
					(mass[i - r - 1][size - 1]).value = (mass[i - r][size - 1]).value;
			}
			(mass[i][size - 1]).right = 1;
		}
	}

	// step 4
	//Нижние стенки на последней строке
	//Оставить как есть

	//Изменение value каждой комнаты на 0
}

void display(void)
{
	//Очистить экран glClear(GL_COLOR_BUFFER'_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_QUADS);

	glVertex3f(0, 2, 0);
	glVertex3f(2.5, 2, 0);
	glVertex3f(2.5, -0.5, 0);
	glVertex3f(0, -0.5, 0);

	glEnd();

	//красный

	for (int j = 0; j != 5; j++)
	{
		for (int i = 0; i != 5; i++)
		{
			glBegin(GL_QUADS);
			glColor3f(1.0, 0.7, 0.3);

			if ((a[i][j]).up == 1)
			{
				glVertex3f(0 + 0.5*(i), 2 - 0.5*(j), 0.0);
				glVertex3f(0 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 2 - 0.5*(j), 0.0);
			}
			if ((a[i][j]).down == 1)
			{
				glVertex3f(0 + 0.5*(i), 1.5 - 0.5*(j), 0.0);
				glVertex3f(0 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 1.5 - 0.5*(j), 0.0);
			}
			if ((a[i][j]).left == 1)
			{
				glVertex3f(0 + 0.5*(i), 2 - 0.5*(j), 0.0);
				glVertex3f(0 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
				glVertex3f(0 + 0.5*(i), 1.5 - 0.5*(j), 0.0);
			}
			if ((a[i][j]).right == 1)
			{
				glVertex3f(0.5 + 0.5*(i), 2 - 0.5*(j), 0.0);
				glVertex3f(0.5 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 1.5 - 0.5*(j), 0.0);
			}
			glEnd();


			glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 1.0);

			if ((a[i][j]).up == 1)
			{
				glVertex3f(0 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 2 - 0.5*(j), 0.3);
			}
			if ((a[i][j]).down == 1)
			{
				glVertex3f(0 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
			}
			if ((a[i][j]).left == 1)
			{
				glVertex3f(0 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
			}
			if ((a[i][j]).right == 1)
			{
				glVertex3f(0.5 + 0.5*(i), 2 - 0.5*(j), 0.3);
				glVertex3f(0.5 + 0.5*(i), 1.5 - 0.5*(j), 0.3);
			}
			glEnd();
		}
	}

	glFlush();
}

//Установить начальные характеристики окна,
//открыть окно с заголовком «cube».
//Зарегистрировать дисплейную функцию обратного вызова
//Войти в главный цикл
int main(int argc, char **argv)
{
	//srand(time(NULL));
	for (int i = 0; i != 5; ++i)
	{
		a[i] = (room*)malloc(sizeof(room) * 5);
	}

	for (int i = 0; i != (5); i++)
	{
		for (int j = 0; j != (5); j++)
		{
			(a[j][i]).down = 0;
			(a[j][i]).left = 0;
			(a[j][i]).right = 0;
			(a[j][i]).up = 0;
			(a[j][i]).value = 0;
		}
	}

	generaL(a, 5);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Labirint");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	//system("pause");
	return 0;
}