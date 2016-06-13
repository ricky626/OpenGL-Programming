#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
void DrawScene();
void Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void MenuFunc(int button);

typedef struct Object
{
	float xTran;
	float yTran;
	float zTran;

	float xRot;
	float yRot;
	float zRot;
}Object;

void main(int argc, char *argv[])
{

	srand((unsigned)time(NULL));
	//초기화 함수들 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example4"); // 윈도우 생성 (윈도우 이름)

	glutTimerFunc(20, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // 출력 함수의 지정

	int SubMenu1, SubMenu2, SubMenu3, SubMenu4, SubMenu5;
	int MainMenu;
	
	
	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);

	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("On", 11);
	glutAddMenuEntry("Off", 22);

	SubMenu3 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("Flat", 111);
	glutAddMenuEntry("Smooth", 222);

	SubMenu4 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("그린다", 1111);
	glutAddMenuEntry("안그린다", 2222);

	SubMenu5 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("그린다", 11111);
	glutAddMenuEntry("안그린다", 22222);

	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("은면제거", SubMenu1);
	glutAddSubMenu("컬링", SubMenu2);
	glutAddSubMenu("쉐이딩", SubMenu3);
	glutAddSubMenu("윗면", SubMenu4);
	glutAddSubMenu("앞면", SubMenu5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();
}

float Vertex[][3]
{
	{ -100, 100, -100 },
	{ -100, 100, 100 },
	{ 100, 100, 100 },
	{ 100, 100, -100 },
	{ -100, -100, -100 },
	{ -100, -100, 100 },
	{ 100, -100, 100 },
	{ 100, -100, -100 }
};

float colors[][3] = {
	{ 1.0, 0.0, 0.0 },      // red  
	{ 1.0, 1.0, 0.0 },      // yellow  
	{ 0.0, 1.0, 0.0 },      // green  
	{ 0.0, 0.0, 1.0 },      // blue
	{ 0.5, 0.5, 0.0 },      // gold
	{ 1.0, 0.0, 1.0 }        // magenta  
};

Object Screen = { 0, 0, 0, 30, 45, 0};
bool upDraw = true;
bool check = true;

// 윈도우 출력 함수
void DrawScene() // 뒷면을 봐야함
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
		glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

		glRotated(Screen.xRot, 1, 0, 0);
		glRotated(Screen.yRot, 0, 1, 0);
		glRotated(Screen.zRot, 0, 0, 1);



		glPushMatrix();
		

			glBegin(GL_QUADS);


					//제일 윗면
					if (upDraw)
					{
						glColor3fv(colors[0]);
						glVertex3fv(Vertex[1]);
						glColor3fv(colors[1]);
						glVertex3fv(Vertex[2]);
						glColor3fv(colors[2]);
						glVertex3fv(Vertex[3]);
						glColor3fv(colors[3]);
						glVertex3fv(Vertex[0]);
					}

					//밑면
					glColor3fv(colors[0]);
						glVertex3fv(Vertex[6]);
					glColor3fv(colors[1]);
						glVertex3fv(Vertex[5]);
					glColor3fv(colors[2]);
						glVertex3fv(Vertex[4]);
					glColor3fv(colors[3]);
						glVertex3fv(Vertex[7]);

					//옆면
						if (check)
						{
							glColor3fv(colors[0]);
								glVertex3fv(Vertex[5]);
							glColor3fv(colors[1]);
								glVertex3fv(Vertex[6]);
							glColor3fv(colors[2]);
								glVertex3fv(Vertex[2]);
							glColor3fv(colors[3]);
								glVertex3fv(Vertex[1]);
						}
				

					//옆면
					glColor3fv(colors[0]);
						glVertex3fv(Vertex[2]);
					glColor3fv(colors[1]);
						glVertex3fv(Vertex[6]);
					glColor3fv(colors[2]);
						glVertex3fv(Vertex[7]);
					glColor3fv(colors[3]);
						glVertex3fv(Vertex[3]);

					//옆면
					glColor3fv(colors[0]);
						glVertex3fv(Vertex[4]);
					glColor3fv(colors[1]);
						glVertex3fv(Vertex[7]);
					glColor3fv(colors[2]);
						glVertex3fv(Vertex[3]);
					glColor3fv(colors[3]);
						glVertex3fv(Vertex[0]);

					//옆면
					glColor3fv(colors[0]);
						glVertex3fv(Vertex[5]);
					glColor3fv(colors[1]);
						glVertex3fv(Vertex[1]);
					glColor3fv(colors[2]);
						glVertex3fv(Vertex[0]);
					glColor3fv(colors[3]);
						glVertex3fv(Vertex[4]);
				
				
			glEnd();


		glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정 // 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1000.0); //투영 변환 ( 원근 투영 ) 

	glTranslatef(0.0, 0.0, -700.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}

void SpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		
	}

	else if (key == GLUT_KEY_RIGHT)
	{

	}

	glutPostRedisplay();
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == '1')		 Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;

	glutPostRedisplay();
}

void TimerFunction(int value)
{
	if (value == 1)
	{
		Screen.yRot -= 2;
	}

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();	
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}

	glutPostRedisplay();
}

void MenuFunc(int button)
{

	switch (button) {
	case 1:
		glEnable(GL_DEPTH_TEST);
		break;
	case 2:
		glDisable(GL_DEPTH_TEST);
		break;

	case 11:
		glEnable(GL_CULL_FACE);
		break;
	case 22:
		glDisable(GL_CULL_FACE);
		break;

	case 111:
		glShadeModel(GL_FLAT);
		break;
	case 222:
		glShadeModel(GL_SMOOTH);
		break;

	case 1111:
		upDraw = true;
		break;
	case 2222:
		upDraw = false;
		break;

	case 11111:
		check = true;
		break;
	case 22222:
		check = false;
		break;
	}
	glutPostRedisplay();
}