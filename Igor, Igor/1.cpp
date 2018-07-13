#include "stdio.h"
#include "stdlib.h"
#include "GL/freeglut.h"
#include "GL/glut.h"
#include "time.h"


#define LEVEL_SIZE 4
#define ROOM_SIZE 17
#define PX_SIZE 40
#define PX_SIZE_MAP 2
#define PC_RESOLUTION_X 1366
#define PC_RESOLUTION_Y 768
#define ROOM_SIZE 17

bool check_states = false;
bool check_map = false;
int battle_ground[ROOM_SIZE][ROOM_SIZE];
int ****level = (int****)malloc(sizeof(int***)*LEVEL_SIZE);
int current_room_x = 0;
int current_room_y = 0;
bool fight_mode = false;
bool mob_spawn = false;
int for_battle[ROOM_SIZE][ROOM_SIZE];
int whose_turn = 1;
int mouse_x = 0;
int mouse_y = 0;

typedef struct hero
{
	int player_pos_x;
	int player_pos_y;
	int battle_x;
	int battle_y;
	int hp;
	int maxhp;
	int mana;
	int maxmana;
	int speed;
	int level;
	int xp;
	int xpmax;
	int sp;//speed points
	int fire;
	int otr;
	bool skip;
	bool check_die;
}hero;

typedef struct spider
{
	int pole_pos_x;
	int pole_pos_y;
	int battle_x;
	int battle_y;
	int hp;
	int maxhp;
	int mana;
	int maxmana;
	int speed;
	int dm;
	bool check_die;
}spider;

int counter_for_waves = 0;
hero* player = (hero*)malloc(sizeof(hero));
spider* sp1 = (spider*)malloc(sizeof(spider));

void fill_sp1()
{
	sp1->pole_pos_x = 1;
	sp1->pole_pos_y = 1;
	sp1->hp = 40;
	sp1->maxhp = 40;
	sp1->mana = 20;
	sp1->maxmana = 20;
	sp1->dm = 5;
	sp1->speed = 4;
	sp1->battle_x = 15;
	sp1->battle_y = 8;
	sp1->check_die = false;
}

 void fill_hero() {
	player->battle_x = 1;
	player->battle_y = 8;
	player->hp = 100;
	player->maxhp = 100;
	player->mana = 100;
	player->maxmana = 100;
	player->speed = 2;
	player->level = 1;
	player->xp = 70;
	player->xpmax = 100;
	player->skip = false;
	player->fire = 0;
	player->otr = 0;
	player->check_die = false;
	player->sp = player->speed;
}
/*
Описание способностей:
1)Стан героя + обычная атака, он пропускает ход
2)Простая атака
3)Наложение на героя эффекта горения
4)Наложение на героя эффекта отравления
*/

void level_up() {
	 while (player->xp >= 100) {
		player->xp -= 100;
		player->level += 1;
	 }
 }

void get_xp(int x) {
	player->xp += x;
	level_up();
}

void check_die()
{
	if (sp1->hp <= 0) {
		sp1->check_die = true;
	}
	if (player->hp <= 0) {
		player->check_die = true;
	}
	if (player->check_die == true)
	{
		battle_ground[player->battle_y][player->battle_x] = -1;
		glutDestroyWindow(1);
	}
	if (sp1->check_die==true)
	{
		battle_ground[sp1->battle_y][sp1->battle_x] = -5;
		whose_turn = 1;
		level[current_room_y][current_room_x][sp1->pole_pos_y][sp1->pole_pos_x]=0;
		get_xp(50);
		glutPostRedisplay();
	}
}

void use(int abil, int dm) 
{
	if (abil == 1)
	{
		player->hp -= dm;
		player->skip = true;
	}
	else if (abil == 2) {
		player->hp -= dm;
	}
	else if (abil == 3) {
		player->fire -= 4;
	}
	else if (abil == 4) {
		player->otr = 4;
	}
	glutPostRedisplay();
}

void player_turn()
{
	check_die();
	if (battle_ground[player->battle_y - 1][player->battle_x] == -4  ||
		battle_ground[player->battle_y + 1][player->battle_x] == -4  ||
		battle_ground[player->battle_y][player->battle_x + 1] == -4  ||
		battle_ground[player->battle_y][player->battle_x - 1] == -4 )
	{
		if (battle_ground[mouse_y][mouse_x] == -4)
		{
			sp1->hp = sp1->hp - 20;
			mouse_x = 0;
			mouse_y = 0;
			check_die();
			glutPostRedisplay();
		}
	}

	if (player->mana+20 <= player->maxmana)
	{
		player->mana = player->mana + 20;
	}
	else
	{
		player->mana = player->maxmana;
	}
	if (player->skip == true)
	{
		whose_turn = 2;
	}
	if (player->fire > 0)
	{
		player->fire--;
		player->hp -= 5;
	}
	if (player->otr > 0)
	{
		player->otr--;
		player->hp = player->hp-3;
	}
	check_die();
}

/*
//0 - spider; 1 - player
void next_turn(int who)
{
	if (who == 0)
	{
		player_turn();
	}
}
*/

void spiderII() 
{
	if (sp1->hp <= 0)
	{
		sp1->check_die = true;
		check_die();
	}
	else
	{
		if (sp1->mana + 5 <= sp1->maxmana)
		{
			sp1->mana += 5;
		}
		else
		{
			sp1->mana = sp1->maxmana;
		}
		bool checke = false;
		if (battle_ground[sp1->battle_y - 1][sp1->battle_x] == -3 ||
			battle_ground[sp1->battle_y + 1][sp1->battle_x] == -3 ||
			battle_ground[sp1->battle_y][sp1->battle_x + 1] == -3 ||
			battle_ground[sp1->battle_y][sp1->battle_x - 1] == -3)
		{
			if (sp1->mana >= 15)
			{
				sp1->mana = sp1->mana - 15;
				use(4, sp1->dm);
			}
			else
			{
				use(2, sp1->dm);
			}
		}
		else
		{
			do {
				int ix = rand() % 13 + 2;
				int iy = rand() % 13 + 2;
				int ras = 0;
				if (sp1->battle_x <= ix)
				{
					ras = ix - sp1->battle_x;
				}
				else
				{
					ras = sp1->battle_x - ix;
				}

				if (sp1->battle_y <= iy)
				{
					ras += (iy - sp1->battle_y);
				}
				else
				{
					ras += (sp1->battle_y - iy);
				}
				if (battle_ground[iy][ix] == -1 && ras <= sp1->speed)
				{
					battle_ground[sp1->battle_y][sp1->battle_x] = -1;
					battle_ground[iy][ix] = -4;
					sp1->battle_x = ix;
					sp1->battle_y = iy;
					checke = true;

				}
			} while (checke == false);
		}
	}
	glutPostRedisplay();
	//check_die();
	whose_turn = 1;
	player_turn();
}

void generate_battle()
{
	for (int i = 0; i < ROOM_SIZE; i++)
	{
		for (int j = 0; j < ROOM_SIZE; j++)
		{
			if (i == 0 || i == ROOM_SIZE - 1 || j == 0 || j == ROOM_SIZE - 1)
			{
				battle_ground[i][j] = -2;
			}
			else
			{
				battle_ground[i][j] = -1;
			}
		}
	}
	player->battle_x = 1;
	player->battle_y = 8;
	battle_ground[player->battle_y][player->battle_x] = -3;
	battle_ground[ROOM_SIZE / 2][ROOM_SIZE - 2] = -4;
}

void generate_into(int **room)
{

	int shab = rand() % 6;
	if (shab == 0) {
		for (int i = 2; i < ROOM_SIZE - 2; i++)
		{
			for (int j = 2; j < ROOM_SIZE - 2; j++)
			{
				int c = rand() % 2;
				if (c == 0)
				{
					room[j][i] = 3;
				}
			}
		}
	}
	else if (shab == 1)
	{
		for (int i = 5; i < 14; i++)
		{
			for (int j = 5; j < 14; j++)
			{
				room[j][i] = 3;
			}
		}
	}
	else if (shab == 2)
	{
		for (int i = 2; i < 6; i++)
		{
			for (int j = 2; j < 6; j++)
			{
				room[j][i] = 3;
			}
		}
		for (int i = 11; i < 15; i++)
		{
			for (int j = 11; j < 15; j++)
			{
				room[j][i] = 3;
			}
		}
		for (int i = 11; i < 15; i++)
		{
			for (int j = 2; j < 6; j++)
			{
				room[j][i] = 3;
			}
		}
		for (int i = 2; i < 6; i++)
		{
			for (int j = 11; j < 15; j++)
			{
				room[j][i] = 3;
			}
		}
	}
	else if (shab == 4)
	{
		for (int i = 6; i < 8; i++)
		{
			for (int j = 6; j < 8; j++)
			{
				room[j][i] = 3;
			}
		}
	}
	else if (shab == 5)
	{
		for (int i = 2; i < 15; i++)
		{
			for (int j = 2; j < 15; j++) {
				int c = rand() % 5;
				if (c == 0) {
					room[j][i] = 3;
				}
			}
		}
	}
}

void ADVANCED_ROOM_GENERATION(int **room, bool top, bool bottom, bool right, bool left)
{
	int vspom = (ROOM_SIZE - 1) / 2;
	if (top)
	{
		for (int j = vspom - 2; j < vspom + 3; j++)
		{
			room[j][0] = 0;
		}
	}
	if (bottom)
	{
		for (int j = vspom - 2; j < vspom + 3; j++)
		{
			room[j][ROOM_SIZE - 1] = 0;
		}
	}
	if (right)
	{
		for (int i = vspom - 2; i < vspom + 3; i++)
		{
			room[ROOM_SIZE - 1][i] = 0;
		}
	}
	if (left)
	{
		for (int i = vspom - 2; i < vspom + 3; i++)
		{
			room[0][i] = 0;
		}
	}
}

void SIMPLE_ROOM_GENERATE(int **room)
{
	for (int i = 0; i < ROOM_SIZE; i++)
	{
		for (int j = 0; j < ROOM_SIZE; j++)
		{
			if ((i == 0) || (j == 0) || (i == ROOM_SIZE - 1) || (j == ROOM_SIZE - 1))
			{
				room[j][i] = 1;
			}
			else
			{
				room[j][i] = 0;
			}
		}
	}

}

void generate_mobs(int **room)
{
	for (int i = 1; i < ROOM_SIZE-1;i++) {
		for (int j = 1; j < ROOM_SIZE-1;j++) {
			if (rand() % 100 == 1) {
				if (room[i][j] != 3) {
					room[i][j] = 4;
				}
			}
		}
	}
}

void FULL_ROOM(int ****level, int x, int y, bool top, bool bottom, bool right, bool left)
{
	SIMPLE_ROOM_GENERATE(level[x][y]);
	ADVANCED_ROOM_GENERATION(level[x][y], top, bottom, right, left);
	generate_into(level[x][y]);
	generate_mobs(level[x][y]);
}

void tree(int ****level, int x, int y)
{
	if (y > 0 && y < LEVEL_SIZE - 1)
	{
		if (level[x][y + 1][0][0] != 1)
		{
			if (rand() % 2 == 0)
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, true, false, false);
				FULL_ROOM(level, x, y + 1, true, false, false, false);
				tree(level, x, y + 1);
			}
		}
		else if (level[x][y - 1][0][0] != 1)
		{
			if (rand() % 2 == 0)
			{
				ADVANCED_ROOM_GENERATION(level[x][y], true, false, false, false);
				FULL_ROOM(level, x, y - 1, false, true, false, false);
				tree(level, x, y - 1);
			}
		}
	}
	if (x > 0 && x < LEVEL_SIZE - 1)
	{
		if (level[x + 1][y][0][0] != 1)
		{
			if (rand() % 2 == 0)
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, false, true, false);
				FULL_ROOM(level, x + 1, y, false, false, false, true);
				tree(level, x + 1, y);
			}
		}
		else if (level[x - 1][y][0][0] != 1)
		{
			if (rand() % 2 == 0)
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, false, false, true);
				FULL_ROOM(level, x - 1, y, false, false, true, false);
				tree(level, x - 1, y);
			}
		}
	}
}

/*void EDIT_ERRORS()
{
	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int j = 0; j < LEVEL_SIZE; j++)
		{
			if (j>0 && level[i][j-1][0][0]!=1)
			{
				if (level[i][j][6][0] != 1)
				{
					for (int n = 6; n < 11; n++)
					{
						level[i][j][n][0] = 1;
					}
				}
			}
			if (j<LEVEL_SIZE-1 && level[i][j+1][0][0] != 1 )
			{
				if (level[i][j][6][ROOM_SIZE-1] != 1)
				{
					for (int n = 6; n < 11; n++)
					{
						level[i][j][n][ROOM_SIZE-1] = 1;
					}
				}
			}
			if (i>0 && level[i-1][j][0][0]!=1 )
			{
				if (level[i][j][0][6] != 1)
				{
					for (int n = 6; n < 11; n++)
					{
						level[i][j][0][n] = 1;
					}
				}
			}
			if (i<LEVEL_SIZE-1 && level[i+1][j][0][0]!= 1 )
			{
				if (level[i][j][ROOM_SIZE-1][6] != 1)
				{
					for (int n = 6; n < 11; n++)
					{
						level[i][j][ROOM_SIZE-1][n] = 1;
					}
				}
			}
		}
	}
}*/

void GENERATE_LEVEL(int ****level)
{
	SIMPLE_ROOM_GENERATE(level[0][0]);
	int x = 0;
	int y = 0;
	for (int i = 0; i < (LEVEL_SIZE - 1) * 2; i++)
	{
		int c = rand() % 2;
		if (c == 0)
		{
			if (x == LEVEL_SIZE - 1)
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, true, false, false);
				y++;
				if (level[x][y][0][0] == 1)
				{
					ADVANCED_ROOM_GENERATION(level[x][y], true, false, false, false);
				}
				else
				{
					FULL_ROOM(level, x, y, true, false, false, false);
				}
				tree(level, x, y);
			}
			else
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, false, true, false);
				x++;
				if (level[x][y][0][0] == 1)
				{
					ADVANCED_ROOM_GENERATION(level[x][y], false, false, false, true);
				}
				else
				{
					FULL_ROOM(level, x, y, false, false, false, true);
				}
				tree(level, x, y);
			}
		}
		else
		{
			if (y == LEVEL_SIZE - 1)
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, false, true, false);
				x++;
				if (level[x][y][0][0] == 1)
				{
					ADVANCED_ROOM_GENERATION(level[x][y], false, false, false, true);
				}
				else
				{
					FULL_ROOM(level, x, y, false, false, false, true);
				}
				tree(level, x, y);
			}
			else
			{
				ADVANCED_ROOM_GENERATION(level[x][y], false, true, false, false);
				y++;
				if (level[x][y][0][0] == 1)
				{
					ADVANCED_ROOM_GENERATION(level[x][y], true, false, false, false);
				}
				else
				{
					FULL_ROOM(level, x, y, true, false, false, false);
				}
				tree(level, x, y);
			}
		}
	}
	level[0][0][3][3] = 4;
	sp1->pole_pos_x = 3;
	sp1->pole_pos_y = 3;
}

void FREE_ROOM(int **room)
{
	for (int i = 0; i < ROOM_SIZE; i++)
	{
		free(room[i]);
	}
	free(room);
	printf("Successful");
}

void FREE_LEVEL(int ****level)
{

	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int j = 0; j < LEVEL_SIZE; j++)
		{
			FREE_ROOM(level[j][i]);
		}
	}

	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		free(level[i]);
	}

	free(level);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, ROOM_SIZE*PX_SIZE, ROOM_SIZE*PX_SIZE, 0.0, -20.0, 20.0);
	//glLoadIdentity();
	//gluLookAt(10.0, 10.0, 0.0, 0.0, 0.0, -20.0, 0.0, 1.0, 0.0);
}

/*void bfs(int y, int x) {
	for (int i = 0; i < ROOM_SIZE; i++)
	{
		for (int j = 0; j < ROOM_SIZE; j++)
		{
			for_battle[i][j] = 0;
		}
	}
	int distances[ROOM_SIZE][ROOM_SIZE];
	for (int i = 0; i < ROOM_SIZE; i++)
		for (int j = 0; j < ROOM_SIZE; j++)
			distances[i][j] = -1;
	typedef struct {
		int x, y;
	} pair;
	pair queue[ROOM_SIZE*ROOM_SIZE];
	int cursorRead = 0, cursorWrite = 0;
	queue[cursorWrite++] = pair{ x, y };
	distances[x][y] = 0;
	while (cursorWrite != cursorRead)
	{
		const pair& cur = queue[cursorRead++];
		if (distances[cur.x][cur.y] >= player->speed)
			continue;
		int currentDistance = distances[cur.x][cur.y];
		if (distances[cur.x - 1][cur.y] != -1) {
			queue[cursorWrite++] = pair{ cur.x - 1, cur.y };
			distances[cur.x - 1][cur.y] = currentDistance + 1;
		}
		if (distances[cur.x + 1][cur.y] != -1) {
			queue[cursorWrite++] = pair{ cur.x + 1, cur.y };
			distances[cur.x + 1][cur.y] = currentDistance + 1;
		}
		if (distances[cur.x][cur.y - 1] != -1) {
			queue[cursorWrite++] = pair{ cur.x, cur.y - 1 };
			distances[cur.x][cur.y - 1] = currentDistance + 1;
		}
		if (distances[cur.x][cur.y + 1] != -1) {
			queue[cursorWrite++] = pair{ cur.x, cur.y + 1 };
			distances[cur.x][cur.y + 1] = currentDistance + 1;
		}
	}
	for (int i = 0; i < ROOM_SIZE; i++)
		for (int j = 0; j < ROOM_SIZE; j++)
			if (distances[i][j] != -1)
				for_battle[i][j] = 1;
}*/

void draw_exits(int i, int j)
{
	glColor3f(0.0, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();
}

void draw_ground(int i, int j)
{
	if (fight_mode == true)
	{
		if (for_battle[i][j] == 1)
		{
			glColor3f(0.0, 0.9, 0.3);
		}
		else
		{
			glColor3f(0.0, 1.0, 0.0);
		}
	}
	else
	{
		glColor3f(0.0, 1.0, 0.0);
	}
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, -10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, -10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, -10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, -10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, -10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, -10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, -10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, -10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, -10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();	
}

void draw_walls(int i, int j)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();
	//
	//
	/*glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 20);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 20);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 20);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 20);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 20);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 20);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 20);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 20);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 20);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();*/
}

void draw_player(int i, int j)
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();
}

void draw_boxes(int i, int j)
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();
}

void draw_spider(int i, int j)
{
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(((j* PX_SIZE) + (PX_SIZE / 2)), ((i* PX_SIZE) + (PX_SIZE / 2)), 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 0);
	glVertex3d(((j* PX_SIZE) + (PX_SIZE / 2)), ((i * PX_SIZE) + (PX_SIZE / 2)), 10);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(j * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(((j* PX_SIZE) + (PX_SIZE / 2)), ((i * PX_SIZE) + (PX_SIZE / 2)), 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d((j + 1)* PX_SIZE, (i + 1) * PX_SIZE, 0);
	glVertex3d(((j* PX_SIZE) + (PX_SIZE / 2)), ((i * PX_SIZE) + (PX_SIZE / 2)), 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 0);
	glEnd();
}

void draw_lines(int i, int j)
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex3d(j * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d((j + 1) * PX_SIZE, i * PX_SIZE, 10);
	glVertex3d((j + 1) * PX_SIZE, (i + 1) * PX_SIZE, 10);
	glEnd();
}

void draw_states() 
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 11);
	glVertex3d((4 * PX_SIZE)+1, 0, 11);
	glVertex3d((4 * PX_SIZE)+1, 3 * PX_SIZE, 11);
	glVertex3d(0, 3 * PX_SIZE, 11);
	glEnd();

	int lng = (120 / player->maxhp)*player->hp;
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(20, 10, 12);
	glVertex3d(20+lng, 10, 12);
	glVertex3d(20+lng, 30, 12);
	glVertex3d(20, 30, 12);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(20, 10, 13);
	glVertex3d(120, 10, 13);
	glVertex3d(120, 30, 13);
	glVertex3d(20, 30, 13);
	glEnd();

	lng = (120 / player->maxmana)*player->mana;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3d(20, 40, 12);
	glVertex3d(20 + lng, 40, 12);
	glVertex3d(20 + lng, 60, 12);
	glVertex3d(20, 60, 12);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(20, 40, 13);
	glVertex3d(120, 40, 13);
	glVertex3d(120, 60, 13);
	glVertex3d(20, 60, 13);
	glEnd();

	lng = (120 / player->xpmax)*player->xp;
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(20, 70, 12);
	glVertex3d(20 + lng, 70, 12);
	glVertex3d(20 + lng, 90, 12);
	glVertex3d(20, 90, 12);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(20, 70, 13);
	glVertex3d(120, 70, 13);
	glVertex3d(120, 90, 13);
	glVertex3d(20, 90, 13);
	glEnd();

	lng = (80 / player->speed)*player->sp;
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3d(5, 10, 12);
	glVertex3d(15, 10, 12);
	glVertex3d(15, 10+lng, 12);
	glVertex3d(5, 10+lng, 12);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3d(5, 10, 13);
	glVertex3d(15, 10, 13);
	glVertex3d(15, 90, 13);
	glVertex3d(5, 90, 13);
	glEnd();

	//spider
	if (fight_mode == true && sp1->check_die==false)
	{
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3d(13 * PX_SIZE, 0, 11);
		glVertex3d(17 * PX_SIZE, 0, 11);
		glVertex3d(17 * PX_SIZE, 3 * PX_SIZE, 11);
		glVertex3d(13 * PX_SIZE, 3 * PX_SIZE, 11);
		glEnd();

		lng = (120 / sp1->maxhp)*sp1->hp;
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 10, 12);
		glVertex3d(PX_SIZE*ROOM_SIZE - (20 + lng),10, 12);
		glVertex3d(PX_SIZE*ROOM_SIZE - (20 + lng), 30, 12);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 30, 12);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 10, 13);
		glVertex3d(PX_SIZE*ROOM_SIZE - 140, 10, 13);
		glVertex3d(PX_SIZE*ROOM_SIZE - 140, 30, 13);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 30, 13);
		glEnd();

		lng = (120 / sp1->maxmana)*sp1->mana;
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 40, 12);
		glVertex3d(PX_SIZE*ROOM_SIZE - (20 + lng), 40, 12);
		glVertex3d(PX_SIZE*ROOM_SIZE - (20 + lng), 60, 12);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 60, 12);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 40, 13);
		glVertex3d(PX_SIZE*ROOM_SIZE - 140, 40, 13);
		glVertex3d(PX_SIZE*ROOM_SIZE - 140, 60, 13);
		glVertex3d(PX_SIZE*ROOM_SIZE - 40, 60, 13);
		glEnd();
	}
}

void draw_map()
{
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3d(0.0, 0.0, 11);
	glVertex3d(LEVEL_SIZE*ROOM_SIZE*PX_SIZE_MAP, 0.0, 11);
	glVertex3d(LEVEL_SIZE*ROOM_SIZE*PX_SIZE_MAP, LEVEL_SIZE*ROOM_SIZE*PX_SIZE_MAP, 11);
	glVertex3d(0.0, LEVEL_SIZE*ROOM_SIZE*PX_SIZE_MAP, 11);
	glEnd();
	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int j = 0; j < LEVEL_SIZE; j++)
		{
			for (int k = 0; k < ROOM_SIZE; k++)
			{
				for (int l = 0; l < ROOM_SIZE; l++)
				{
					if (level[i][j][k][l] == 0)
					{
						glColor3f(0.0, 1.0, 0.0);
						
					}
					if(level[i][j][k][l] == 1)
					{
						glColor3f(1.0, 0.0, 0.0);
					}
					if (level[i][j][k][l] ==2 || level[i][j][k][l] == -10)
					{
						glColor3f(0.0, 0.0, 0.0);

					}
					if (level[i][j][k][l] == 3)
					{
						glColor3f(0.0, 0.0, 1.0);
					}
					if (level[i][j][k][l] == 4)
					{
						glColor3f(0.0, 1.0, 1.0);
					}
					glBegin(GL_POLYGON);
					glVertex3d(j*ROOM_SIZE *PX_SIZE_MAP+ (l * PX_SIZE_MAP), i*ROOM_SIZE*PX_SIZE_MAP + (k * PX_SIZE_MAP), 12);
					glVertex3d(j*ROOM_SIZE*PX_SIZE_MAP + (l + 1) * PX_SIZE_MAP, i*ROOM_SIZE*PX_SIZE_MAP + (k*  PX_SIZE_MAP), 12);
					glVertex3d(j*ROOM_SIZE*PX_SIZE_MAP + (l + 1) * PX_SIZE_MAP, i*ROOM_SIZE*PX_SIZE_MAP + ((k + 1) * PX_SIZE_MAP), 12);
					glVertex3d(j*ROOM_SIZE*PX_SIZE_MAP + (l * PX_SIZE_MAP), i*ROOM_SIZE*PX_SIZE_MAP + ((k + 1) * PX_SIZE_MAP), 12);
					glEnd();

					
				}
			}
		}
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	int x = current_room_x;
	int y = current_room_y;
	if (fight_mode == false)
	{
		if (check_map == true)
		{
			draw_map();
		}
		for (int i = 0; i < ROOM_SIZE; i++)
		{
			for (int j = 0; j < ROOM_SIZE; j++)
			{
				if ((level[y][x][i][j] == 0) && ((i == 0 && j > 5 && j < 12) || (j == 0 && i > 5 && i < 12) || (i == ROOM_SIZE - 1 && j > 5 && j < 12) || (j == ROOM_SIZE - 1 && i > 5 && i < 12)))
				{
					draw_exits(i, j);
				}
				else
				{
					if (level[y][x][i][j] == 0)
					{
						draw_ground(i, j);
					}
					if (level[y][x][i][j] == 1)
					{
						draw_walls(i, j);

					}
					if (level[y][x][i][j] == 2)
					{
						draw_player(i, j);
					}
					if (level[y][x][i][j] == 3)
					{
						draw_boxes(i, j);
					}
					if (level[y][x][i][j] == 4)
					{
						draw_spider(i, j);
					}

				}
			}
		}
	}
	else
	{
		//bfs(player->battle_x,player->battle_y);
		for (int i = 0; i < ROOM_SIZE; i++)
		{
			for (int j = 0; j < ROOM_SIZE; j++)
			{
				if (battle_ground[i][j] == -1)
				{
					draw_ground(i, j);
					draw_lines(i, j);
				}
				if (battle_ground[i][j] == -2)
				{
					draw_walls(i, j);
				}
				if (battle_ground[i][j] == -3)
				{
					draw_player(i, j);
				}
				if (battle_ground[i][j] == -4)
				{
					draw_spider(i, j);
				}
				if (battle_ground[i][j] == -5)
				{
					draw_exits(i, j);
				}
				
			}
		}
	}
	if (check_states == true) {
		draw_states();
	}
	//glLoadIdentity();
	glPopMatrix();
	glutSwapBuffers();
}

bool check_turn(unsigned char key)
{
	switch (key)
	{
	case 'w':
	{
		if (level[current_room_y][current_room_x][player->player_pos_y - 1][player->player_pos_x] == 0 || level[current_room_y][current_room_x][player->player_pos_y - 1][player->player_pos_x] == 4)
			return true;
		else
			return false;
	}
	case 'd':
	{
		if (level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x + 1] == 0 || level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x + 1] == 4)
			return true;
		else
			return false;
	}
	case 's':
	{
		if (level[current_room_y][current_room_x][player->player_pos_y + 1][player->player_pos_x] == 0 || level[current_room_y][current_room_x][player->player_pos_y + 1][player->player_pos_x] == 4)
			return true;
		else
			return false;
	}
	case 'a':
	{
		if (level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x - 1] == 0 || level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x - 1] == 4)
			return true;
		else
			return false;
	}
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if (check_turn(key) == true)
	{
		switch (key)
		{/*
			case 'w':
			{
			current_room_y--;
			glutPostRedisplay();
			break;
			}
			case 'd':
			{
			current_room_x++;
			glutPostRedisplay();
			break;
			}
			case 's':
			{
			current_room_y++;
			glutPostRedisplay();
			break;
			}
			case 'a':
			{
			current_room_x--;
			glutPostRedisplay();
			break;
			}*/

		case 'w':
		{
			if (level[current_room_y][current_room_x][player->player_pos_y - 1][player->player_pos_x] == 4)
			{
				fill_sp1();
				sp1->pole_pos_x = player->player_pos_x;
				sp1->pole_pos_y = player->player_pos_y-1;
				generate_battle();
				fight_mode = true;
				glutPostRedisplay();
				break;
			}
			else if (player->player_pos_y - 1 == 0 && level[current_room_y][current_room_x][player->player_pos_x][player->player_pos_y] == 0 && current_room_y > 0)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				current_room_y--;
				player->player_pos_y = ROOM_SIZE - 2;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y - 1][player->player_pos_x] == 0)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				player->player_pos_y--;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
				break;
			}
		}
		case 'a':
		{
			if (player->player_pos_x - 1 == 0 && level[current_room_y][current_room_x][player->player_pos_x][player->player_pos_y] == 0 && current_room_x > 0)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				current_room_x--;
				player->player_pos_x = ROOM_SIZE - 2;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x - 1] == 0)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				player->player_pos_x--;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
				break;
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x - 1] == 4)
			{
				fill_sp1();
				sp1->pole_pos_x = player->player_pos_x - 1;
				sp1->pole_pos_y = player->player_pos_y;
				generate_battle();
				fight_mode = true;
				glutPostRedisplay();
				break;
			}
			break;
		}
		case 's':
		{
			if (player->player_pos_y == ROOM_SIZE - 2 && level[current_room_y][current_room_x][player->player_pos_x][player->player_pos_y] == 0 && current_room_y < LEVEL_SIZE - 1)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				current_room_y++;
				glutPostRedisplay();
				player->player_pos_y = 1;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y + 1][player->player_pos_x] == 0)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				player->player_pos_y++;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
				break;
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y + 1][player->player_pos_x] == 4)
			{
				fill_sp1();
				sp1->pole_pos_x = player->player_pos_x;
				sp1->pole_pos_y = player->player_pos_y+1;
				generate_battle();
				fight_mode = true;
				glutPostRedisplay();
				break;
			}
			break;
		}
		case 'd':
		{
			if (player->player_pos_x == ROOM_SIZE - 2 && level[current_room_y][current_room_x][player->player_pos_x][player->player_pos_y] == 0 && current_room_x < LEVEL_SIZE - 1)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				current_room_x++;
				player->player_pos_x = 1;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x + 1] == 0)
			{
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 0;
				player->player_pos_x++;
				level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x] = 2;
				glutPostRedisplay();
				break;
			}
			else if (level[current_room_y][current_room_x][player->player_pos_y][player->player_pos_x + 1] == 4)
			{
				fill_sp1();
				sp1->pole_pos_x = player->player_pos_x+1;
				sp1->pole_pos_y = player->player_pos_y;
				generate_battle();
				fight_mode = true;
				glutPostRedisplay();
				break;
			}
			break;
		}
		default:
			break;
		}
	}
	if (key == '\x1b')
	{
		glutDestroyWindow(1);
	}
	if (fight_mode == true && key == ' ' && sp1->check_die==false)
	{
		player->sp = player->speed;
		whose_turn = 2;
		spiderII();
	}
	if (key == 'i') 
	{
		glutPostRedisplay();
		if (check_states == true) {
				
			check_states = false;
				
		}
		else {
			check_states = true;
		}
	}
	if (key == 'm')
	{
		if (check_map == true) {

			check_map = false;

		}
		else {
			check_map = true;
		}
		glutPostRedisplay();
	}
}

void LEVEL_GENERATION(int ****level)
{
	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int j = 0; j < LEVEL_SIZE; j++)
		{
			SIMPLE_ROOM_GENERATE(level[j][i]);
		}
	}
}

void gotomouse(int x, int y) {
	int ix = x / PX_SIZE;
	int iy = y / PX_SIZE;
	int ras = 0;
	
	if (player->battle_x <= ix)
	{
		ras = ix - player->battle_x;
	}
	else
	{
		ras = player->battle_x - ix;
	}

	if (player->battle_y <= iy)
	{
		ras += (iy - player->battle_y);
	}
	else
	{
		ras += (player->battle_y - iy);
	}
	if (battle_ground[iy][ix] == -1 && ras <= player->speed && player->sp >= ras)
	{
		battle_ground[player->battle_y][player->battle_x] = -1;
		battle_ground[iy][ix] = -3;
		player->battle_x = ix;
		player->battle_y = iy;
		player->sp = player->sp - ras;
	}
	mouse_x = ix;
	mouse_y = iy;
	if (battle_ground[mouse_y][mouse_x] == -5)
	{
		fight_mode = false;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (whose_turn == 1)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
		{
			if (state == GLUT_DOWN)
			{
				gotomouse(x, y);
			}
		}
		}
	}
}

int main(int argc, char **argv)
{
	fill_hero();
	fill_sp1();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(PX_SIZE*ROOM_SIZE, PX_SIZE*ROOM_SIZE);
	glutInitWindowPosition((PC_RESOLUTION_X - (PX_SIZE*ROOM_SIZE)) / 2, (PC_RESOLUTION_Y - (PX_SIZE*ROOM_SIZE)) / 2 - PX_SIZE);
	glutCreateWindow("Dunrai");
	init();

	

	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		level[i] = (int***)malloc(sizeof(int**)*LEVEL_SIZE);
	}

	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int j = 0; j < LEVEL_SIZE; j++)
		{
			level[i][j] = (int**)malloc(sizeof(int*)*ROOM_SIZE);
			for (int n = 0; n < ROOM_SIZE; n++)
			{
				level[i][j][n] = (int*)malloc(sizeof(int)*ROOM_SIZE);
			}
		}
	}

	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int j = 0; j < LEVEL_SIZE; j++)
		{
			for (int n = 0; n < ROOM_SIZE; n++)
			{
				for (int m = 0; m < ROOM_SIZE; m++)
				{
					level[i][j][n][m] = -10;
				}
			}
		}
	}
	GENERATE_LEVEL(level);
	player->player_pos_x = 1;
	player->player_pos_y = 1;
	level[0][0][1][1] = 2;
	//LEVEL_GENERATION(level);
	//ADVANCED_ROOM_GENERATION(level[1][1], true, true, true, true);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	free(player);
	free(sp1);
	FREE_LEVEL(level);
	return 0;
}