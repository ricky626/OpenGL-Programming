#include <gl/glut.h>
#include <vector>
#include "define_1-7.h"
#include <ctime>
#include <cmath>

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
void Timerfunction(int value);

void main(int argc, char * argv[])
{
	srand(time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Pratice 1-8");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(50, Timerfunction, 1);
	glutMainLoop();
}

vector<INFO>   m_iVec;
INFO         m_tInfo;
INFO         m_Init;
INFO         m_Sub;
bool         Mousecheck = false;
int check = 0;



GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (Mousecheck)
	{
		glColor4f(0.f, 1.f, 0.f, 1.f);
		glPointSize(4);
		glBegin(GL_POINTS);

		for (vector<INFO>::iterator iter = m_iVec.begin();
			iter != m_iVec.end(); ++iter)
		{

			glVertex2f(iter->fX + cosf(iter->fAngle) * (iter->fR),
				iter->fY - sinf(iter->fAngle) * (iter->fR));

			
		}

		if (check == 1)
		{
			glVertex2f(m_Sub.fX + cosf(m_Sub.fAngle) * (m_Sub.fR),
				m_Sub.fY - sinf(m_Sub.fAngle) * (m_Sub.fR));
		}

		glEnd();
	}
	glFlush();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		m_tInfo.fX = x;
		m_tInfo.fY = y;
		m_tInfo.fR = 0;
		m_tInfo.fDistance = 0.f;

		if (!Mousecheck)
		{
			m_iVec.push_back(m_tInfo);
			glutTimerFunc(50, Timerfunction, 2);

			Mousecheck = true;
			glutTimerFunc(50, Timerfunction, 1);
		}

		glutPostRedisplay();
	}
}


void Timerfunction(int value)
{
	if (value == 1)
	{
		//m_tInfo.fAngle += 0.1f;	
		//m_tInfo.fR += 0.2f;

		for (vector<INFO>::iterator iter = m_iVec.begin();
			iter != m_iVec.end(); ++iter)
		{
			if (iter->fAngle < PI * 4 && check == 0)
			{
				iter->fAngle += 0.1f;
				
				iter->fR += 0.2f;
				m_Sub.fX = iter->fX;
				m_Sub.fY = iter->fY;
				m_Sub.fAngle = 0;
				m_Sub.fR = 0;
			}
			else if (iter->fAngle >= PI * 4 && check == 0)
			{
				check = 1;
				m_Sub.fX = iter->fX;
				m_Sub.fY = iter->fY;
				m_Sub.fAngle = 0;
				m_Sub.fR = 0;
			}
			else if (m_Sub.fAngle < PI * 4 && check == 1)
			{
				m_Sub.fAngle -= 0.1f;
				m_Sub.fR -= 0.2f;
			}
			else if (m_Sub.fAngle < PI * 4 && check == 1)
			{
				check = 2;
			}
/*
			else if (angle >= PI * 4 && check == 2)
			{
				iter->fAngle -= 0.1f;
				iter->fR -= 0.2f;
			}*/

		}
		
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, 1);
	}

	if (value == 2)
	{
		/*m_Init.fX = m_tInfo.fX;
		m_Init.fY = m_tInfo.fY;
		m_tInfo.fR = 0;
		m_tInfo.fDistance = 0.f;
		for (vector<INFO>::iterator iter = m_iVec.begin();
		iter != m_iVec.end(); ++iter)
		{
		iter->fX = m_Init.fX;
		iter->fY = m_Init.fY;
		}*/

		m_iVec.push_back(m_tInfo);

		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, 2);
	}

}