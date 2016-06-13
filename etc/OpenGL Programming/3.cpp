#include <GL/glut.h> // includes gl.h glu.h
#include <time.h>
#include <stdlib.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

typedef struct POLY
{
	int x;
	int y;
}POLY;

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(900, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


int check[9] = { 0, };
int xx[9] = { 0, 300, 600, 0, 300, 600, 0, 300, 600 };
int yy[9] = { 0, 0, 0, 200, 200, 200, 400, 400, 400 };
float redcolor = 1.0f;

POLY poly[9] = { 0, };

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


	for (int i = 0; i < 9; i++)
	{	
		poly[i].x = xx[i]; // 0 300 600
		poly[i].y = yy[i]; // 0 200 400

		check[i] = (rand() % 4) + 2;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
	glVertex2i(300, 0); glVertex2i(300, 600); glVertex2i(600, 0); glVertex2i(600, 600);

	glVertex2i(0, 200); glVertex2i(900, 200); glVertex2i(0, 400); glVertex2i(900, 400);
	glEnd();

	

	for (int i = 0; i < 9; i++)
	{
		glColor4f(redcolor-=0.1f, 0.0f, 0.0f, 1.0f);
		if (check[i] == 2) // 직선
		{
			glBegin(GL_LINES);
				glVertex2i(poly[i].x + 75, poly[i].y + 50);
				glVertex2i(poly[i].x + 175, poly[i].y + 150);
			glEnd();
		}
		else if (check[i] == 3) //삼각형
		{
			glBegin(GL_POLYGON);
				glVertex2i(poly[i].x + 150, poly[i].y + 50);
				glVertex2i(poly[i].x + 200, poly[i].y + 100);
				glVertex2i(poly[i].x + 50, poly[i].y + 150);
			glEnd();
		}
		else if (check[i] == 4) //사각형
		{
			glRectd(poly[i].x + 70, poly[i].y + 70, poly[i].x + 175, poly[i].y + 175);
		}
		else if (check[i] == 5) //오각형
		{
			glBegin(GL_POLYGON);
			glVertex2i(poly[i].x + 100, poly[i].y + 50);
			glVertex2i(poly[i].x + 150, poly[i].y + 50);
			glVertex2i(poly[i].x + 175, poly[i].y + 100);
			glVertex2i(poly[i].x + 125, poly[i].y + 150);
			glVertex2i(poly[i].x + 75, poly[i].y + 100);
			glEnd();
		}

		glBegin(GL_POLYGON);

		
		glEnd();
	}




	glFlush(); //화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 900, 600, 0, -1.0, 1.0);

}
