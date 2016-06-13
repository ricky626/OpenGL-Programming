#include <GL/glut.h>  
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
///////////////////////////
//  �ݹ� �Լ� ����  //
///////////////////////////
GLvoid drawScene(GLvoid);

GLvoid Mouse(int button, int state, int x, int y);//���콺
GLvoid Keyboard(unsigned char key, int x, int y);//Ű����
GLvoid Reshape(int w, int h);

//GLvoid Time(int sec);//Ÿ�̸�

//////////////////////////
//  ���� �Լ� ���� //
//////////////////////////
void line();
void init();
void sin();
void cos();
void spring();
void print();
void rotation();
void move();
void moveSum();
void plusMove();
void minusMove();
void zoomIn();
void zoomOut();
//////////////////////////
//  ���� ����  //
//////////////////////////
GLfloat coordinatePoint[1000][2];//�� ����
GLfloat xPos = 0.0f, yPos = 0.0f;//��ǥ
GLfloat moveXpos = 0.0f, moveYpos = 0.0f;//�� ��ǥ �̵��ϴ� �Ÿ�
GLint state = 0;//Ű���� ����
GLint scale = 1;//������ ��ȭ��
GLfloat xposSum = 0, yposSum = 0;//�� ��ǥ �̵��Ÿ� ����
/////////////////////////////////////////
//   ����         //
/////////////////////////////////////////
void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100);  // �������� ��ġ���� 
	glutInitWindowSize(800, 800);  // �������� ũ�� ����
	glutCreateWindow("Practice12");  // ������ ���� (������ �̸�)
	//�ݹ��Լ� ���
	glutDisplayFunc(drawScene);  // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape);

	glutMouseFunc(Mouse);//���콺
	//glutTimerFunc(1000,Time,1);//Ÿ�̸�
	glutKeyboardFunc(Keyboard);//Ű����
	glutMainLoop();//GLUT �̺�Ʈ ���μ��� ���� ����
}
//////////////////////////////
//  ������ ��� �Լ�  //
//////////////////////////////
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // �������� 'Magenta' �� ����
	glClear(GL_COLOR_BUFFER_BIT);  // ������ ������ ��ü�� ĥ�ϱ�

	//�Լ� ȣ��
	line();
	switch (state)
	{
	case  1://COS
		init();
		cos();
		print();
		break;//end c

	case 2://SIN
		init();
		sin();
		print();
		break;//end i

	case 3://SPRING
		init();
		spring();
		print();
		break;// end p

	case 4://ROTATION
		print();
		break;// end r

	case 5://UP
		move();
		print();
		break;//end l

	case 6://DOWN
		move();
		print();
		break;//end .

	case 7://LEFT
		move();
		print();
		break;//end ,

	case 8://RIGHT
		move();
		print();
		break;//end /
	case 9://SCALE-ZOOM IN
		print();
		break;//end s
	case 10://SCALE-ZOOM OUT
		print();
		break;//end a
	}
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

////////////////////////////////////
//  COORDINATE      //
////////////////////////////////////
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-10, 10, -10, 10, -1.0, 1.0);
}

///////////////////////////////////////////////////
//     KEYBOARD      //
///////////////////////////////////////////////////
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'c'://COS
		state = 1;
		break;//end c

	case'i'://SIN
		state = 2;
		break;//end i

	case 'p'://SPRING
		state = 3;
		break;// end p

	case 'r'://ROTATION
		//minusMove();
		rotation();
		//plusMove();
		state = 4;
		break;//end r

	case 'l'://UP
		moveXpos = 0;
		moveYpos = 0.5;
		state = 5;
		break;//end l

	case '.'://DOWN
		moveXpos = 0;
		moveYpos = -0.5;
		state = 6;
		break;//end .

	case ','://LEFT
		moveXpos = -0.5;
		moveYpos = 0;
		state = 7;
		break;//endl ,

	case '/'://RIGHT
		moveXpos = 0.5;
		moveYpos = 0;
		state = 8;
		break;//end /

	case 's'://SCALE-ZOOM IN
		state = 9;
		zoomIn();
		break;//end s
	case 'a'://SCALE-ZOOM OUT
		state = 10;
		zoomOut();
		break;//end a
	}
	glutPostRedisplay();
}
///////////////////////////////////////////////////
//     MOUSE       //
///////////////////////////////////////////////////
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}
//////////////////////
//  TIMER  //
//////////////////////
//GLvoid Time(int sec)
//{
// glutPostRedisplay();
// glutTimerFunc(1000,Time,1);
//}
/////////////////////////////////////////////////////////////////////
//       FUNCTION          // 
/////////////////////////////////////////////////////////////////////
////////////
// LINE  //
////////////
void line()
{

	//Y ��
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);//����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, -800.0f, 1.0f);//���� ��ǥ
	glVertex3f(0.0f, 800.0f, 1.0f);//���� ��ǥ
	glEnd();

	//X ��
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);//����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);
	glVertex3f(-800.0f, 0.0f, 1.0f);//���� ��ǥ
	glVertex3f(800.0f, 0.0f, 1.0f);//���� ��ǥ
	glEnd();
}
//////////
// INIT //
//////////
void init()
{
	//X, Y �ʱ�ȭ
	xPos = -10.0f;
	yPos = 0.0f;
	//�̵��� �ʱ�ȭ
	moveXpos = 0.0f;
	moveYpos = 0.0f;
	//������ �ʱ�ȭ
	scale = 1;
	//�׷��� �� ���� �ʱ�ȭ
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] = 0.0f;
		coordinatePoint[i][1] = 0.0f;
	}
}
////////////
// SIN   //
////////////
void sin()
{
	for (int i = 0; i<1000; ++i)
	{
		xPos += 0.1;
		yPos = sin(xPos);
		coordinatePoint[i][0] = xPos;
		coordinatePoint[i][1] = yPos;
	}
}
////////////
// COS   //
////////////
void cos()
{
	for (int i = 0; i<1000; ++i)
	{
		xPos += 0.1;
		yPos = cos(xPos);
		coordinatePoint[i][0] = xPos;
		coordinatePoint[i][1] = yPos;
	}
}
////////////////
//   PRINT   //
////////////////
void print()
{
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i<1000; ++i)
		glVertex3f(coordinatePoint[i][0], coordinatePoint[i][1], 1.0f);//���� ��ǥ


	glEnd();
}
//////////////////
// ROTATION //
//////////////////
void rotation()
{
	float DEGINRAD = 3.14159 / 180;
	float degInRad = 10.0f*DEGINRAD;

	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] = coordinatePoint[i][0] * cos(degInRad) - coordinatePoint[i][1] * sin(degInRad);
		coordinatePoint[i][1] = coordinatePoint[i][0] * sin(degInRad) + coordinatePoint[i][1] * cos(degInRad);
	}
}
//////////////
// SPRING //
//////////////
void spring()
{
	float radius = 1;//������

	float DEGINRAD = 3.14159 / 180;
	float degInRad = 0.0f;
	float Nums = 0;//x������
	float x_left = 5.0;//�߽���ǥ
	float y_left = 0.0;//�߽���ǥ
	for (int i = 0; i<1000; ++i)
	{
		degInRad = i*DEGINRAD;
		coordinatePoint[i][0] = (cos(degInRad)*radius) + x_left + Nums;
		coordinatePoint[i][1] = (sin(degInRad)*radius) + y_left;
		Nums -= 0.01;
	}
}
//////////////
// MOVE //
//////////////
void move()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] += moveXpos;
		coordinatePoint[i][1] += moveYpos;
	}
	moveSum();
}
//////////////
// MOVESUM //
//////////////
void moveSum()
{
	xposSum += moveXpos;
	yposSum += moveYpos;
}
////////////////
// PLUSMOVE  //
////////////////
void plusMove()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] += xposSum;
		coordinatePoint[i][1] += yposSum;
	}
}
/////////////////
// MINUSMOVE  //
/////////////////
void minusMove()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] -= xposSum;
		coordinatePoint[i][1] -= yposSum;
	}
}
////////////
// SIZE  //
////////////
void size()
{
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] *= scale;
		coordinatePoint[i][1] *= scale;
	}
}
//////////////
//  ZOOMIN  //
//////////////
void zoomIn()
{
	minusMove();
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] *= 1.5f;
		coordinatePoint[i][1] *= 1.5f;
	}
	plusMove();
}
///////////////
//  ZOOMOUT  //
///////////////
void zoomOut()
{
	minusMove();
	for (int i = 0; i<1000; ++i)
	{
		coordinatePoint[i][0] /= 1.5f;
		coordinatePoint[i][1] /= 1.5f;
	}
	plusMove();
}
//////////////
// CIRCLE //
//////////////

void circle()
{
	float radius = 1;//������

	float DEGINRAD = 3.14159 / 180;
	float x_left = 5.0;//�߽���ǥ
	float y_left = 0.0;//�߽���ǥ
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i<1980; i++)
	{
		float degInRad = i*DEGINRAD;
		glVertex2f(cos(degInRad)*radius + x_left, sin(degInRad)*radius + y_left);
	}
	glEnd();
}