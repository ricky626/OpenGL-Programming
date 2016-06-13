
#include <gl/glut.h> 			// includes gl.h glu.h
#include <math.h>
#include <iostream>

void Keyboard(unsigned char key, int x, int y);

GLfloat zTran = 0;
GLfloat CirTranX = 0, CirTranY = 0, CirTranZ = 0;
GLfloat CirRotX = 0, CirRotY = 0, CirRotZ = 0;
using namespace std;

void SetupRC()
{
	// clear ������ ���������� ����
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	// �׸����� ������� ���� 
	glColor3f(1.0f, 0.0f, 0.0f);


}


void DrawScene(void)
{
	GLfloat x, y, z, angle;

	// �����츦 ������ ������ clear�Ѵ�.
	glClear(GL_COLOR_BUFFER_BIT);

	// ����� �����ϰ� ȸ���Ѵ�.
	glPushMatrix();
		glTranslatef(0.0, 0.0, zTran);

		glPushMatrix();
			glColor3ub(180, 180, 0);

			//glTranslatef(0.0, 0.0, zTran);

			//glRotatef(10, 1, 0, 0);
			glScalef(3.0, 2.0, 2.0);
		
			glBegin(GL_QUADS);
				glVertex3f(-100.0, -100.0, -100.0);
				glVertex3f(-100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, 100.0);
				glVertex3f(100.0, -100.0, -100.0);
			glEnd();
		
		glPopMatrix();

		glPushMatrix();
			glColor3f(1, 0, 0);
		
		
		
			glTranslatef(CirTranX, -200, CirTranZ);	

			glRotatef(CirRotX, 1.0f, 0.0f, 0.0f);
			glRotatef(CirRotY, 0.0f, 1.0f, 0.0f);
			glRotatef(CirRotZ, 0.0f, 0.0f, 1.0f);

		
		
			glScalef(2.0, 2.0, 2.0);
		
				glutWireSphere(20, 10, 10);

		glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// �������� ���� ���� ����
	glViewport(0, 0, w, h);

	// ���� ��� ���� �缳�� // �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1000.0); //���� ��ȯ ( ���� ���� ) 

	glTranslatef(0.0, 0.0, -700.0); //����(����) ��ȯ //ī�޶� ���� // ���� ���A�� �������� �о �þ߿� �������� �Ѵ�.
	//ī�޶��� ����Ʈ ��ġ�� ����, ����Ʈ ������ z���� ���� ����

	//glTranslatef(0.0f, 0.0f, -500.0f);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x')
	{
		if (CirTranX > -300)
			CirTranX -= 5;
		CirRotZ += 5;
	}
	else if (key == 'X') 
	{
		if (CirTranX < 300)
			CirTranX += 5;
		CirRotZ -= 5;
	}
	else if (key == 'y')
	{
		CirRotY += 5;
	}

	else if (key == 'Y')
	{
		CirRotY -= 5;
	}

	else if (key == 'z') 
	{
		if (CirTranZ > -200)
			CirTranZ -= 5;
		CirRotX -= 5;
	}
	else if (key == 'Z') 
	{
		if (CirTranZ < 100)
			CirTranZ += 5;
		CirRotX += 5;
	}

	else if (key == 'i' || key == 'I')
	{
		CirTranX = CirTranY = CirTranZ = 0;
		CirRotX = CirRotY = CirRotZ = 0;
	}
	else if (key == 'f')
	{
		zTran += 5;
	}
	else if (key == 'F')
	{
		zTran -= 5;
	}

	
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitDisplayMode (GLUT_RGB);
	glutInitWindowSize(800, 600); 	// �������� ũ�� ����
	glutCreateWindow("example");

	SetupRC();

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}

