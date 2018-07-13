#pragma once
#include <vector>
#include "Class.h"
std::vector<Sphere*> sp;
Player *player1 = new Player(), *player2 = new Player();
Game *game = new Game();
Camera* camera = new Camera();
Ki* ki = new Ki();
std::vector<Hole*> holes;
AI* ai = new AI();
const GLdouble Pi = 3.1415;
const int counts = 11;
int current = 0;
int goal = 0;
bool check_collision = true, check_fall = false, bot_on2 = false, bot_on1 = false;