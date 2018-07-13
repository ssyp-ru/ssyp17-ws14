#pragma once
#include "include\GL\freeglut.h"
#include <cmath>
#include <iostream>
#include "Define.h"
class Wall {
public:
	static void Wall::Draw(GLdouble X, GLdouble Y, GLboolean Up_Down, GLboolean Uper);
};
class Leg {
public:
	static void Leg::Draw(GLdouble X, GLdouble Y);
};
class table {
public:
	static void table::Draw();
};
class Sphere {
private:
	GLdouble X = 0, Y = 0, Radius = 0.6,
		SpdX = 0, SpdY = 0, SpdZ = 0,
		AclX = 0, AclY = 0,
		Mass = 1, Angle = 270,
		Z = 0.6,
		R = 1, G = 1, B = 1;
	GLboolean fall = false;
public:
	Sphere::Sphere(GLdouble x, GLdouble y, GLdouble r, GLdouble g, GLdouble b);
	void Sphere::SetAngle(GLdouble angle);
	void Sphere::Draw(void);
	void Sphere::Move(void);
	void Sphere::Go(void);
	void Sphere::SetSpd(GLdouble x, GLdouble y);
	void Sphere::Place(void);
	void Sphere::SetXYZ(GLdouble x, GLdouble y, GLdouble z);
	void Sphere::ChngX(GLdouble x);
	void Sphere::ChngY(GLdouble y);
	void Sphere::Fall(GLboolean b);
	GLboolean Sphere::GetFall(void);
	GLdouble Sphere::GetX(void);
	GLdouble Sphere::GetY(void);
	GLdouble Sphere::GetR(void);
	GLdouble Sphere::GetSpdX(void);
	GLdouble Sphere::GetSpdY(void);
	GLdouble Sphere::GetMass(void);
	GLdouble Sphere::GetPX(void);
	GLdouble Sphere::GetPY(void);
};
class Ki {
private:
	GLdouble SpdX, SpdY,  X = 0, Y = 0;
	GLdouble Angle = 0.0;
	GLint Power = 1;
	Sphere* sphere1;
public:
	Ki::Ki();
	void Ki::Draw(void);
	void Ki::ChngAngle(GLdouble angle);
	void Ki::SetAngle(GLdouble angle);
	void Ki::SetXY(GLdouble x, GLdouble y);
	void Ki::SetBall(Sphere* sphere);
	void Ki::ChngPower(int power);
	void Ki::SetPower(int power);
	Sphere* Ki::GetCurrentBall();
	GLdouble Ki::GetAngle();
	GLint Ki::GetPower();
	void Ki::ChngSpd(GLdouble x, GLdouble y);
};
class Hole {
private:
	GLdouble X, Y;
public:
	Hole::Hole(GLdouble x, GLdouble y);
	void Hole::Draw(void);
	GLdouble Hole::GetX();
	GLdouble Hole::GetY();
};
struct Player {
	GLbyte score = 0;
};
class Game {
private:
	Player* cur;
public:
	void SetPlayer(Player* player);
	Player* GetCurPlayer();
};
class Camera {
private:
	GLdouble X = 26, Y = 0, Z = 15,
		centerX = 16, centerY = 0, centerZ = 9,
		headX = -2, headY = 0, headZ = 1, Angle = 0.0, move = 0.0;
public:
	Camera::Camera();
	Camera::~Camera();
	void Camera::Look();
	void Camera::SetX(GLdouble x);
	void Camera::SetY(GLdouble y);
	void Camera::SetZ(GLdouble z);
	void Camera::SetCenterX(GLdouble x);
	void Camera::SetCenterY(GLdouble y);
	void Camera::SetCenterZ(GLdouble z);
	void Camera::SetHeadX(GLdouble x);
	void Camera::SetHeadY(GLdouble y);
	void Camera::SetHeadZ(GLdouble z);
	void Camera::SetAngle(GLdouble angle);
	void Camera::SetMove(GLdouble move1);
	void Camera::Return(void);
};
class Light {
public:
	static void Place(void);
};
class Display {
public:
	static void move(void);
	static void Balls_Collision();
	static void Place_Balld();
	static void Strike();
	static void GameOverd(void);
	static void reshape(int w, int h);
};
class Control {
public:
	static void GameOver();
	static void Place_Ball();
	static GLdouble ThCos_cos(GLdouble a, GLdouble b, GLdouble c);
	static void init(void);
	static void Switch();
	static GLdouble Distance(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	static void Restart();
};
class AllCollison {
public:
	static void fall(Sphere* sphere1, Hole* hole);
	static void Wall_collison(Sphere* sphere1);
	static void Collison(Sphere* sphere1, Sphere* sphere2);
};
class Keyboard {
public:
	static void PreviousBall(void);
	static void NextBall(void);
	static void look(unsigned char key, int x, int y);
	static void ki_control(unsigned char key, int x, int y);
	static void Place_Ballk(unsigned char key, int x, int y);
};
class AI{
private:
	Sphere *cur, *chosen;
public:
	void SetBall();
	void Strike();
	void ChoseBall();
	void RotateKi();
	void Power();
};
