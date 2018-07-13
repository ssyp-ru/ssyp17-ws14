#include "Class.h"
void Game::SetPlayer(Player* player) {
	cur = player;
}
Player* Game::GetCurPlayer() { return cur; }
Camera::Camera() {};
Camera::~Camera() {};
void Camera::Look() {
	glLoadIdentity();
	gluLookAt(X, Y, Z, centerX, centerY, centerZ, headX, headY, headZ);
	glTranslated(move, 0, move);
	glRotated(Angle, 0, 0, 1);
}
void Camera::SetX(GLdouble x) { X += x; }
void Camera::SetY(GLdouble y) { Y += y; }
void Camera::SetZ(GLdouble z) { Z += z; }
void Camera::SetCenterX(GLdouble x) { centerX += x; }
void Camera::SetCenterY(GLdouble y) { centerY += y; }
void Camera::SetCenterZ(GLdouble z) { centerZ += z; }
void Camera::SetHeadX(GLdouble x) { headX += x; }
void Camera::SetHeadY(GLdouble y) { headY += y; }
void Camera::SetHeadZ(GLdouble z) { headZ += z; }
void Camera::SetAngle(GLdouble angle) { Angle += angle; }
void Camera::SetMove(GLdouble move1) { move += move1; }
void Camera::Return(void) {
	X = 26, Y = 0, Z = 15,
		centerX = 16, centerY = 0, centerZ = 9,
		headX = -2, headY = 0, headZ = 1, Angle = 0.0, move = 0.0;
}
void Wall::Draw(GLdouble X, GLdouble Y, GLboolean Up_Down, GLboolean Uper) {
	glPushMatrix();
	GLfloat specular1[] = { 1.0, 0.5, 0.3, 1.0 };
	GLfloat specular2[] = { 1.0, 0.5, 0.3, 0.5 };
	GLfloat shininess1[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, specular2);
	if (!Up_Down && !Uper) {
		glTranslated(X, Y, 0.2);
		glScaled(11.8, 1, 1);
		glutSolidCube(1);
	}
	else if (!Uper) {

		glTranslated(X, Y, 0.2);
		glRotated(90, 0, 0, 1);
		glScaled(15, 1, 1);
		glutSolidCube(1);
	}
	if (!Up_Down && Uper) {
		glTranslated(X, Y, 0.2);
		glScaled(29, 1, 2);
		glutSolidCube(1);
	}
	else if (Uper) {

		glTranslated(X, Y, 0.2);
		glRotated(90, 0, 0, 1);
		glScaled(15, 1, 2);
		glutSolidCube(1);
	}
	glPopMatrix();
}
void Leg::Draw(GLdouble X, GLdouble Y) {
	glPushMatrix();
	GLfloat specular1[] = { 1.0, 0.5, 0.3, 1.0 };
	GLfloat specular2[] = { 1.0, 0.5, 0.3, 0.5 };
	GLfloat shininess1[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, specular2);
	glTranslated(X, Y, -3.5);
	glScaled(1, 1, 5);
	glutSolidCube(1);
	glPopMatrix();
}
void table::Draw() {
	glPushMatrix();
	GLfloat specular[] = { 0.0, 0.5, 0.3, 1.0 };
	GLfloat shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, specular);
	glTranslated(0, 0, -0.5);
	glScalef(29, 15, 1);
	glutSolidCube(1);
	glPopMatrix();
	Wall::Draw(6.5, 7, false, false);
	Wall::Draw(-6.5, 7, false, false);
	Wall::Draw(6.5, -7, false, false);
	Wall::Draw(-6.5, -7, false, false);
	Wall::Draw(14, 0, true, false);
	Wall::Draw(-14, 0, true, false);
	Wall::Draw(0, 8, false, true);
	Wall::Draw(0, -8, false, true);
	Wall::Draw(15, 0, true, true);
	Wall::Draw(-15, 0, true, true);
	Leg::Draw(13, -7);
	Leg::Draw(13, 7);
	Leg::Draw(0, -7);
	Leg::Draw(0, 7);
	Leg::Draw(-13, -7);
	Leg::Draw(-13, 7);
}
Sphere::Sphere(GLdouble x, GLdouble y, GLdouble r, GLdouble g, GLdouble b) {
	X = x;
	Y = y;
	R = r;
	G = g;
	B = b;
}
void Sphere::SetAngle(GLdouble angle) {
	Angle = angle;
}
void Sphere::Draw(void) {
	GLfloat specular[] = { R, G, B, 1.0 };
	GLfloat shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, specular);
	glutSolidSphere(Radius, 40, 16);
	glPopMatrix();
}
void Sphere::Move(void) {
	glPushMatrix();
}
void Sphere::Go(void) {
	if (SpdX > 0.0001)
		AclX = -0.0001;
	else {
		if (SpdX < -0.0001)
			AclX = 0.0001;
		else {
			AclX = 0;
			SpdX = 0;
		}
	}
	if (SpdY > 0.0001)
		AclY = -0.0001;
	else {
		if (SpdY < -0.0001)
			AclY = 0.0001;
		else {
			AclY = 0;
			SpdY = 0;
		}
	}
	SpdX += AclX;
	SpdY += AclY;
	glTranslated(X + SpdX, Y + SpdY, Z);
	Y += SpdY;
	X += SpdX;
}
void Sphere::SetSpd(GLdouble x, GLdouble y) {
	SpdX = x;
	SpdY = y;
}
void Sphere::Place(void) {
	glTranslated(X, Y, Z);
}
void Sphere::SetXYZ(GLdouble x, GLdouble y, GLdouble z) {
	X = x;
	Y = y;
	Z = z;
}
void Sphere::ChngX(GLdouble x) {
	X += x;
}
void Sphere::ChngY(GLdouble y) {
	Y += y;
}
void Sphere::Fall(GLboolean b) { fall = b; }
GLboolean Sphere::GetFall(void) { return fall; }
GLdouble Sphere::GetX(void) { return X; }
GLdouble Sphere::GetY(void) { return Y; }
GLdouble Sphere::GetR(void) { return Radius; }
GLdouble Sphere::GetSpdX(void) { return SpdX; }
GLdouble Sphere::GetSpdY(void) { return SpdY; }
GLdouble Sphere::GetMass(void) { return Mass; }
GLdouble Sphere::GetPX(void) { return Mass*SpdX; }
GLdouble Sphere::GetPY(void) { return Mass*SpdY; }
Ki::Ki() {}
void Ki::Draw(void) {
	glPushMatrix();
	GLfloat specular[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, specular);
	glTranslated(X, Y, 0.8);
	glRotated(Angle, 0, 0, 1);
	glRotated(80, 0, 1, 0);
	glTranslated(0, 0, (GLdouble)(Power + 0.6));
	glutSolidCylinder(0.1, 15, 40, 16);
	glPopMatrix();
}
void Ki::ChngAngle(GLdouble angle) {
	Angle += angle;
}
void Ki::SetAngle(GLdouble angle) {
	Angle = angle;
}
void Ki::SetXY(GLdouble x, GLdouble y) {
	X = x;
	Y = y;
}
void Ki::SetBall(Sphere* sphere) {
	sphere1 = sphere;
	SetXY(X1, Y1);
}
void Ki::ChngPower(int power) {
	Power = abs(Power + power) % 5;
}
void Ki::SetPower(int power) {
	Power = power;
}
Sphere* Ki::GetCurrentBall() { return sphere1; }
GLdouble Ki::GetAngle() { return Angle; }
GLint Ki::GetPower() { return Power; }
void Ki::ChngSpd(GLdouble x, GLdouble y) { SpdX = x; SpdY = y; }
Hole::Hole(GLdouble x, GLdouble y) {
	X = x;
	Y = y;
}
void Hole::Draw(void) {
	glPushMatrix();
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess[] = { 500.0 };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, specular);
	glTranslated(X, Y, -0.9999);
	glutSolidCylinder(0.6, 1, 40, 16);
	glPopMatrix();
}
GLdouble Hole::GetX() { return X; }
GLdouble Hole::GetY() { return Y; }
void Light::Place(void) {
	GLfloat light_position[] = { 7,3.5,4.0,1.0 };
	GLfloat white_light[] = { 1.0,1.0,1.0,1.0 };
	GLfloat spot_direction[] = { -1.0, 0.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	GLfloat light_position1[] = { -7,-3.5,4.0,1.0 };
	GLfloat white_light1[] = { 1.0,1.0,1.0,1.0 };
	GLfloat spot_direction1[] = { 1.0, 0.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light1);
}