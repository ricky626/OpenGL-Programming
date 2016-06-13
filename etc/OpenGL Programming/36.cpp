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

	//glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // 출력 함수의 지정


	int SubMenu1, SubMenu2, SubMenu3;
	int MainMenu;


	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("올리기", 1);
	glutAddMenuEntry("내리기", 2);

	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("정방향", 11);
	glutAddMenuEntry("역방향", 22);

	SubMenu3 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("GL_LINEAR", 111);
	glutAddMenuEntry("GL_EXP", 222);
	glutAddMenuEntry("GL_EXP2", 333);


	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Density", SubMenu1);
	glutAddSubMenu("위치 변경", SubMenu2);
	glutAddSubMenu("모드 변경", SubMenu3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}

Object Screen = { 0, };

GLfloat fog_color[4] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat density = 0.7;
GLfloat startZ = 10.0;
GLfloat endZ = 30.0;

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void MenuFunc(int button)
{

	switch (button) {
	case 1:
		if (density < 1.0)
			density += 0.1;
		break;
	case 2:
		if (density > 0)
			density -= 0.1;
		break;

	case 11:
		break;
	case 22:
		break;

	case 111:
		glFogf(GL_FOG_MODE, GL_LINEAR);
		break;
	case 222:
		glFogf(GL_FOG_MODE, GL_EXP);
		break;
	case 333:
		glFogf(GL_FOG_MODE, GL_EXP2);
		break;

	}
	glutPostRedisplay();
}

// 윈도우 출력 함수
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//카메라

	//glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

	glRotated(Screen.xRot + 30, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);


	glFogf(GL_FOG_START, startZ); // start는 world coordinate상에서 안개 시작 위치를 의미핚다.
	glFogf(GL_FOG_END, endZ); // end는 world coordinate상에서 안개 끝 위치를 의미핚다.
	glFogf(GL_FOG_DENSITY, density); // fog mode가 GL_EXP, GL_EXP2일 경우 밀도의 설정이 가능


		glPushMatrix();
			glColor3f(1, 0, 0);
				glutSolidCube(200);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.0, -100.0);
			glColor3f(1, 1, 0);
			glutSolidCube(150);
		glPopMatrix();

		glPushMatrix();
		glTranslatef( 0.0, 0.0, 100.0);
			glColor3f(0, 0, 1);
			glutSolidCube(150);
		glPopMatrix();

	glPopMatrix();//카메라

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	// 투영 행렬 스택 재설정 // 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(60.0f, w / h, 1.0, 2000.0); //투영 변환 ( 원근 투영 )

	//glTranslatef(0.0, 0.0, -700.0); //관측(뷰잉) 변환 //카메라 설정 // 투영 공갂을 안쪽으로 밀어서 시야에 들어오도록 한다.
	//카메라의 디폴트 위치는 원점, 디폴트 방향은 z축의 음의 방향

	glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE, GL_LINEAR);

	glFogfv(GL_FOG_COLOR, fog_color); // fog_color는 안개의 색을 의미핚다. 
	glFogf(GL_FOG_START, 10); // start는 world coordinate상에서 안개 시작 위치를 의미핚다.
	glFogf(GL_FOG_END, 30); // end는 world coordinate상에서 안개 끝 위치를 의미핚다.
	glFogf(GL_FOG_DENSITY, density); // fog mode가 GL_EXP, GL_EXP2일 경우 밀도의 설정이 가능
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
	if (key == '1')	Screen.xRot -= 2;
	else if (key == '2') Screen.xRot += 2;
	else if (key == '3') Screen.yRot -= 2;
	else if (key == '4') Screen.yRot += 2;
	else if (key == '5') Screen.zRot -= 2;
	else if (key == '6') Screen.zRot += 2;
	else if (key == '9') Screen.zTran -= 5;
	else if (key == '0') Screen.zTran += 5;

	else if (key == 'q' || key == 'Q')
	{
		if (density > 0)
			density -= 0.1f;
	}
	else if (key == 'w' || key == 'W')
	{
		if (density < 1.0)
			density += 0.1f;
	}
	else if (key == 'z')
		startZ += 3;
	else if (key == 'Z')
		startZ -= 3;
	else if (key == 'a')
		endZ += 3;
	else if (key == 'A')
		endZ -= 3;
	printf("density %f\n", density);
	printf("startZ: %d endZ: %d\n", (int)startZ, (int)endZ);

	glutPostRedisplay();
}

void TimerFunction(int value)
{

	glutTimerFunc(10, TimerFunction, 1);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}

	glutPostRedisplay();
}