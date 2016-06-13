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
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)

	//glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);
	glutDisplayFunc(DrawScene); // ��� �Լ��� ����


	int SubMenu1, SubMenu2, SubMenu3;
	int MainMenu;


	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("�ø���", 1);
	glutAddMenuEntry("������", 2);

	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("������", 11);
	glutAddMenuEntry("������", 22);

	SubMenu3 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry("GL_LINEAR", 111);
	glutAddMenuEntry("GL_EXP", 222);
	glutAddMenuEntry("GL_EXP2", 333);


	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu("Density", SubMenu1);
	glutAddSubMenu("��ġ ����", SubMenu2);
	glutAddSubMenu("��� ����", SubMenu3);

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

// ������ ��� �Լ�
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();//ī�޶�

	//glTranslatef(Screen.xTran, Screen.yTran, Screen.zTran + 80);

	glRotated(Screen.xRot + 30, 1, 0, 0);
	glRotated(Screen.yRot, 0, 1, 0);
	glRotated(Screen.zRot, 0, 0, 1);


	glFogf(GL_FOG_START, startZ); // start�� world coordinate�󿡼� �Ȱ� ���� ��ġ�� �ǹ�����.
	glFogf(GL_FOG_END, endZ); // end�� world coordinate�󿡼� �Ȱ� �� ��ġ�� �ǹ�����.
	glFogf(GL_FOG_DENSITY, density); // fog mode�� GL_EXP, GL_EXP2�� ��� �е��� ������ ����


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

	glPopMatrix();//ī�޶�

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// �������� ���� ���� ����
	glViewport(0, 0, w, h);

	// ���� ��� ���� �缳�� // �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(60.0f, w / h, 1.0, 2000.0); //���� ��ȯ ( ���� ���� )

	//glTranslatef(0.0, 0.0, -700.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����

	glOrtho(-500.0, 500.0, -500.0, 500.0, -500.0, 500.0);

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE, GL_LINEAR);

	glFogfv(GL_FOG_COLOR, fog_color); // fog_color�� �Ȱ��� ���� �ǹ�����. 
	glFogf(GL_FOG_START, 10); // start�� world coordinate�󿡼� �Ȱ� ���� ��ġ�� �ǹ�����.
	glFogf(GL_FOG_END, 30); // end�� world coordinate�󿡼� �Ȱ� �� ��ġ�� �ǹ�����.
	glFogf(GL_FOG_DENSITY, density); // fog mode�� GL_EXP, GL_EXP2�� ��� �е��� ������ ����
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