#include "Class.h"
#include "Value.h"
#include "include\GL\freeglut.h"
#include <cstdlib>
#include <cmath>
void AllCollison::fall(Sphere* sphere1, Hole* hole) {
	if (Control::Distance(X1, Y1, hole->GetX(), hole->GetY()) <= 0.9) {
		check_fall = false;
		if (game->GetCurPlayer() == player1)
			sphere1->SetXYZ(-18, -8.5 + goal * 1.2, 2);
		else
			sphere1->SetXYZ(18, -8.5 + goal * 1.2, 2);
		sphere1->SetSpd(0, 0);
		sphere1->Fall(true);
		goal++;
	}

}
void AllCollison::Wall_collison(Sphere* sphere1) {
	if (abs(X1) >= 13)
		sphere1->SetSpd(-V1X, V1Y);
	if (abs(Y1) >= 6 &&
		abs(X1) >= 0.4 &&
		abs(X1) <= 12.8) {
		sphere1->SetSpd(V1X, -V1Y);
	}

}
void AllCollison::Collison(Sphere* sphere1, Sphere* sphere2) {
	GLdouble DISTANCE_CENTRE = Control::Distance(X1, Y1, X2, Y2);
	if (DISTANCE_CENTRE <= sphere1->GetR() * 2) {
		check_collision = true;
		int x1 = 1, x2 = 1, y1 = 1, y2 = 1;
		if (X1 > X1 + sphere1->GetSpdX())
			x1 = -1;
		if (Y1 > Y1 + sphere1->GetSpdY())
			y1 = -1;
		if (X2 > X2 + sphere2->GetSpdX())
			x2 = -1;
		if (Y2 > Y2 + sphere2->GetSpdY())
			y2 = -1;
		GLdouble Vector2f1 = Control::Distance(X1, Y1, X1 + sphere1->GetSpdX(), Y1 + sphere1->GetSpdY());
		GLdouble Vector2f2 = Control::Distance(X2, Y2, X2 + sphere2->GetSpdX(), Y2 + sphere2->GetSpdY());
		GLdouble temp_alpha = Control::ThCos_cos(DISTANCE_CENTRE,
			Vector2f1,
			Control::Distance(X2, Y2, X1 + sphere1->GetSpdX(), Y1 + sphere1->GetSpdY()));
		GLdouble temp_lenght = Vector2f1*temp_alpha;
		GLdouble chng_speedx2 = x1*temp_lenght*abs(X1 - X2) / DISTANCE_CENTRE;
		GLdouble chng_speedy2 = y1*temp_lenght*abs(Y1 - Y2) / DISTANCE_CENTRE;
		GLdouble temp_beta = Control::ThCos_cos(DISTANCE_CENTRE,
			Vector2f2,
			Control::Distance(X1, Y1, X2 + sphere2->GetSpdX(), Y2 + sphere2->GetSpdY()));
		GLdouble temp_lenght1 = Vector2f2*temp_beta;
		GLdouble chng_speedx1 = x2*temp_lenght1*abs(X1 - X2) / DISTANCE_CENTRE;
		GLdouble chng_speedy1 = y2*temp_lenght1*abs(Y1 - Y2) / DISTANCE_CENTRE;
		sphere1->SetSpd((V1X + chng_speedx1) / 1.4, (V1Y + chng_speedy1) / 1.4);
		sphere2->SetSpd((V2X + chng_speedx2) / 1.4, (V2Y + chng_speedy2) / 1.4);
		glutPostRedisplay();
	}

}
void AI::RotateKi() {
	GLdouble angle = Pi / 2 - asin(abs(cur->GetX() - chosen->GetX())
		/ Control::Distance(cur->GetX(), cur->GetY(),
			chosen->GetX(), chosen->GetY()));
	ki->SetAngle(-angle / Pi * 180);
}
void AI::Power()
{
	ki->SetPower(3);
}
void AI::ChoseBall() {
	GLint next = abs(current++) % counts;
	chosen = sp[next];
	if (chosen->GetFall())
		ChoseBall();
}
void AI::SetBall() {
	GLint next = abs(current++) % counts;
	cur = sp[next];
	Keyboard::NextBall();
}
void AI::Strike() {
	Keyboard::ki_control('r', 0, 0);
}
void Display::move(void) {
		glutPostRedisplay();
		int k = 0, end = 0;
		for (int i = 0; i < counts; i++) {
			if (sp[i]->GetSpdX() == 0 && sp[i]->GetSpdY() == 0)
				k++;
			if (sp[i]->GetFall())
				end++;
		}
		if (k == counts && end != counts) {
			if (check_fall) {
				Control::Switch();
				check_fall = false;
			}
			if (!check_collision && goal != counts - 1) {
				Control::Place_Ball();
				return;
			}
			glutDisplayFunc(Strike);
			glutKeyboardFunc(Keyboard::ki_control);
		}

	}
void Display::Balls_Collision(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < counts; i++) {
			AllCollison::Wall_collison(sp[i]);
			for (int c = 0; c < counts && c != i; c++) {
				AllCollison::Collison(sp[i], sp[c]);
			}
			for (int g = 0; g < 6; g++)
				AllCollison::fall(sp[i], holes[g]);
			sp[i]->Move();
			sp[i]->Go();
			sp[i]->Draw();
		}
		for (int i = 0; i < 6; i++)
			holes[i]->Draw();
		table::Draw();
		camera->Look();
		glutSwapBuffers();
	}
void Display::Place_Balld(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < counts; i++) {
			sp[i]->Move();
			sp[i]->Place();
			sp[i]->Draw();
		}
		for (int i = 0; i < 6; i++)
			holes[i]->Draw();
		table::Draw();
		camera->Look();
		Light::Place();
		glutSwapBuffers();
	}
void Display::Strike(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < counts; i++) {

			sp[i]->Move();
			sp[i]->Place();
			sp[i]->Draw();
		}
		for (int i = 0; i < 6; i++)
			holes[i]->Draw();
		if (game->GetCurPlayer() == player2 && bot_on2) {
			ai -> SetBall();
			ai -> ChoseBall();
			ai -> RotateKi();
			ai -> Power();
			ai -> Strike();
		}
		if (game->GetCurPlayer() == player1 && bot_on1) {
			ai->SetBall();
			ai->ChoseBall();
			ai->RotateKi();
			ai->Power();
			ai->Strike();
		}
		ki->Draw();
		table::Draw();
		camera->Look();
		Light::Place();
		glutSwapBuffers();

	}
void Display::GameOverd(void) {
		for (int i = 0; i < 6; i++)
			holes[i]->Draw();
		table::Draw();
		camera->Look();
		Light::Place();
		glutSwapBuffers();
	}
void Display::reshape(int w, int h) {
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
		glMatrixMode(GL_MODELVIEW);
		camera->Look();
		glClearColor(0, 0, 0, 0);
		Light::Place();
	}
void Control::GameOver(void) {
	glutDisplayFunc(Display::GameOverd);
	glutKeyboardFunc(Keyboard::look);

}
void Control::Place_Ball(void) {
	ki->GetCurrentBall()->SetXYZ(ki->GetCurrentBall()->GetX(), ki->GetCurrentBall()->GetY(), 0.6);
	glutKeyboardFunc(Keyboard::Place_Ballk);
	glutDisplayFunc(Display::Place_Balld);

}
GLdouble Control::ThCos_cos(GLdouble a, GLdouble b, GLdouble c) {
	if (a == 0 || b == 0)
		return 1;
	return (a*a + b*b - c*c) / (2 * a*b);

}
void Control::init(void) {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	sp.push_back(new Sphere(3, 0, 1, 1, 1));
	sp.push_back(new Sphere(-3, 0, 1, 1, 1));
	sp.push_back(new Sphere(-4.2, 0.7, 1, 1, 1));
	sp.push_back(new Sphere(-4.2, -0.7, 1, 1, 1));
	sp.push_back(new Sphere(-5.4, 0, 1, 1, 1));
	sp.push_back(new Sphere(-5.4, -1.3, 1, 1, 1));
	sp.push_back(new Sphere(-5.4, 1.3, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, 0.7, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, -0.7, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, 1.9, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, -1.9, 1, 1, 1));
	holes.push_back(new Hole(13, -7));
	holes.push_back(new Hole(13, 7));
	holes.push_back(new Hole(0, -7));
	holes.push_back(new Hole(0, 7));
	holes.push_back(new Hole(-13, -7));
	holes.push_back(new Hole(-13, 7));
	game->SetPlayer(player1);
	Light::Place();
}
void Control::Switch(void) {
	if (game->GetCurPlayer() == player1)
		game->SetPlayer(player2);
	else
		game->SetPlayer(player1);
}
GLdouble Control::Distance(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	return sqrt(abs(x1 - x2)*abs(x1 - x2) + abs(y1 - y2)*abs(y1 - y2));
}
void Control::Restart(){
	for (int i = counts - 1; i >= 0; i--) {
		delete sp[i];
		sp.pop_back();
	}
	sp.push_back(new Sphere(3, 0, 1, 1, 1));
	sp.push_back(new Sphere(-3, 0, 1, 1, 1));
	sp.push_back(new Sphere(-4.2, 0.7, 1, 1, 1));
	sp.push_back(new Sphere(-4.2, -0.7, 1, 1, 1));
	sp.push_back(new Sphere(-5.4, 0, 1, 1, 1));
	sp.push_back(new Sphere(-5.4, -1.3, 1, 1, 1));
	sp.push_back(new Sphere(-5.4, 1.3, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, 0.7, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, -0.7, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, 1.9, 1, 1, 1));
	sp.push_back(new Sphere(-6.6, -1.9, 1, 1, 1));
	game->SetPlayer(player1);
	check_collision = true;
	check_fall = false;
	goal = 0;
}
void Keyboard::PreviousBall(void) {
	int end = 0;
	for (int i = 0; i < counts; i++)
		if (sp[i]->GetFall())
			end++;
	if (end == counts) {
		Control::GameOver();
		return;
	}
	GLint previous = abs(current--) % counts;
	ki->SetBall(sp[previous]);
	if (ki->GetCurrentBall()->GetFall())
		PreviousBall();

}
void Keyboard::NextBall(void) {
	int end = 0;
	for (int i = 0; i < counts; i++)
		if (sp[i]->GetFall())
			end++;
	if (end == counts) {
		Control::GameOver();
		return;
	}
	GLint next = abs(current++) % counts;
	ki->SetBall(sp[next]);
	if (ki->GetCurrentBall()->GetFall())
		NextBall();
}
void Keyboard::look(unsigned char key, int x, int y) {
	switch (key) {
	case '8':
		camera->SetX(-1);
		camera->SetCenterX(-1);
		glutPostRedisplay();
		break;
	case '2':
		camera->SetX(1);
		camera->SetCenterX(1);
		glutPostRedisplay();
		break;
	case '4':
		camera->SetY(-1);
		camera->SetCenterY(-1);
		glutPostRedisplay();
		break;
	case '6':
		camera->SetY(1);
		camera->SetCenterY(1);
		glutPostRedisplay();
		break;
	case '7':
		camera->SetAngle(1);
		glutPostRedisplay();
		break;
	case '9':
		camera->SetAngle(-1);
		glutPostRedisplay();
		break;
	case '1':
		camera->SetMove(1);
		glutPostRedisplay();
		break;
	case '3':
		camera->SetMove(-1);
		glutPostRedisplay();
		break;
	case '0':
		camera->Return();
		glutPostRedisplay();
		break;
	case 'b':
		bot_on2 ? bot_on2 = false : bot_on2= true;
		break;
	case 'v':
		bot_on1 ? bot_on1 = false : bot_on1 = true;
		break;
	case 'o':
		Control::Restart();
		glutDisplayFunc(Display::Strike);
		glutKeyboardFunc(Keyboard::ki_control);
		break;
	}
}
void Keyboard::ki_control(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		ki->ChngAngle(-1);
		glutPostRedisplay();
		break;
	case 'd':
		ki->ChngAngle(1);
		glutPostRedisplay();
		break;
	case 's':
		ki->ChngPower(1);
		glutPostRedisplay();
		break;
	case 'w':
		ki->ChngPower(-1);
		glutPostRedisplay();
		break;
	case 'e':
		NextBall();
		glutPostRedisplay();
		break;
	case 'q':
		PreviousBall();
		glutPostRedisplay();
		break;
	case 'r':
		check_collision = false;
		check_fall = true;
		(ki->GetCurrentBall())->SetSpd((GLdouble)(-POWER*cos(ANGLE) / 3),
			(GLdouble)(-POWER*sin(ANGLE)) / 3);
		glutDisplayFunc(Display::Balls_Collision);
		glutKeyboardFunc(Keyboard::look);
		ki->SetPower(0);
		break;
	case 'b':
		bot_on2? bot_on2 = false : bot_on2 = true;
		break;
	case 'v':
		bot_on1 ? bot_on1 = false : bot_on1 = true;
		break;
	case '8':
		camera->SetX(-1);
		camera->SetCenterX(-1);
		glutPostRedisplay();
		break;
	case '2':
		camera->SetX(1);
		camera->SetCenterX(1);
		glutPostRedisplay();
		break;
	case '4':
		camera->SetY(-1);
		camera->SetCenterY(-1);
		glutPostRedisplay();
		break;
	case '6':
		camera->SetY(1);
		camera->SetCenterY(1);
		glutPostRedisplay();
		break;
	case '7':
		camera->SetAngle(1);
		glutPostRedisplay();
		break;
	case '9':
		camera->SetAngle(-1);
		glutPostRedisplay();
		break;
	case '1':
		camera->SetMove(1);
		glutPostRedisplay();
		break;
	case '3':
		camera->SetMove(-1);
		glutPostRedisplay();
		break;
	case '0':
		camera->Return();
		glutPostRedisplay();
		break;
	case 'o':
		Control::Restart();
		glutDisplayFunc(Display::Strike);
		glutKeyboardFunc(Keyboard::ki_control);
		break;
	}
}
void Keyboard::Place_Ballk(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		ki->GetCurrentBall()->ChngY(-0.6);
		glutPostRedisplay();
		break;
	case 'd':
		ki->GetCurrentBall()->ChngY(0.6);
		glutPostRedisplay();
		break;
	case 's':
		ki->GetCurrentBall()->ChngX(0.6);
		glutPostRedisplay();
		break;
	case 'w':
		ki->GetCurrentBall()->ChngX(-0.6);
		glutPostRedisplay();
		break;
	case 'e':
		check_collision = true;
		check_fall = false;
		Control::Switch();
		ki->GetCurrentBall()->Fall(false);
		glutDisplayFunc(Display::Strike);
		glutKeyboardFunc(ki_control);
		break;
	case 'b':
		bot_on2 ? bot_on2 = false : bot_on2 = true;
		break;
	case 'v':
		bot_on1 ? bot_on1 = false : bot_on1 = true;
		break;
	case '8':
		camera->SetX(-1);
		camera->SetCenterX(-1);
		glutPostRedisplay();
		break;
	case '2':
		camera->SetX(1);
		camera->SetCenterX(1);
		glutPostRedisplay();
		break;
	case '4':
		camera->SetY(-1);
		camera->SetCenterY(-1);
		glutPostRedisplay();
		break;
	case '6':
		camera->SetY(1);
		camera->SetCenterY(1);
		glutPostRedisplay();
		break;
	case '7':
		camera->SetAngle(1);
		glutPostRedisplay();
		break;
	case '9':
		camera->SetAngle(-1);
		glutPostRedisplay();
		break;
	case '1':
		camera->SetMove(1);
		glutPostRedisplay();
		break;
	case '3':
		camera->SetMove(-1);
		glutPostRedisplay();
		break;
	case '0':
		camera->Return();
		glutPostRedisplay();
		break;
	case 'o':
		Control::Restart();
		glutDisplayFunc(Display::Strike);
		glutKeyboardFunc(Keyboard::ki_control);
		break;
	}

}

