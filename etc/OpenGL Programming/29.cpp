#include <GL/glut.h> // includes gl.h glu.h
#include <math.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void TimerFunction(int value);
void DoKeyboard(unsigned char key, int x, int y);

int ctrlIndex = 0;
int ctrlCnt = 0;
void main(int argc, char *argv[])
{

	//초기화 함수들 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Text10"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutKeyboardFunc(DoKeyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();




}
// 윈도우 출력 함수

GLfloat ctrlpoints[4][3] = { 0 };

GLvoid drawScene(GLvoid)
{


	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'White' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 젂체를 칠하기 

	// 컨트롤 포인트 설정

	// 곡선 제어점 설정:  매개변수 u의 최소값은 0, 최대값은 1, 
	//       제어점간의 데이터 개수는 3, 제어점은 4개를 사용
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);

	glEnable(GL_MAP1_VERTEX_3);

	// 제어점 사이의 곡선위의 점들을 계산한다.  제어점 사이를 30개로 나누어 그 점들을 연결한다. ==è 곡선위의 점 계산
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++) {
		if (ctrlCnt >= 4){
			glEvalCoord1f((GLfloat)i / 30.0);
		}
	}
	glEnd();

	glDisable(GL_MAP1_VERTEX_3);

	// 제어점에 점을 그린다.
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		if (ctrlCnt >= 4){
			glVertex3fv(&ctrlpoints[i][0]);

		}
	}
	glEnd();


	glutPostRedisplay();



	glFlush(); // 화면에 출력하기

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

}

void TimerFunction(int value)
{

	glutPostRedisplay();

	glutTimerFunc(200, TimerFunction, 1); // 타이머함수 재 설정

}
void DoKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
	case 'R':
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 3; ++j){
				ctrlpoints[i][j] = 0;
			}
		}
		glutPostRedisplay();
		break;
	default:
		break;

	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y)
{
	++ctrlCnt;
	if (4 == ctrlIndex)
		ctrlIndex = 0;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		ctrlpoints[ctrlIndex][0] = x;
		ctrlpoints[ctrlIndex][1] = 600 - y;
		ctrlpoints[ctrlIndex][2] = 0;
		++ctrlIndex;


	}
	glutPostRedisplay();

}