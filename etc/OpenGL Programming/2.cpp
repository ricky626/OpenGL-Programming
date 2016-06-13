#include <GL/glut.h> // includes gl.h glu.h
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA );
	// ���÷��� ��� ���� glutInitWindowPosition ( 100, 100 );
	// �������� ��ġ���� glutInitWindowSize ( 250, 250 ); 
	// �������� ũ�� ���� glutCreateWindow ( "Example2" ); 
	// ������ ���� (������ �̸�)  glutDisplayFunc ( drawScene ); // ��� �Լ��� ����


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	int check = 0;

	// �������� 'blue' �� ���� glClear( GL_COLOR_BUFFER_BIT );
	// ������ ������ ��ü�� ĥ�ϱ� glColor4f(0.0f, 1.0f, 0.0f, 1.0f); 
	// �׸��� ���� 'green' ���� ���� glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	// �簢�� �׸��� glFlush(); // ȭ�鿡 ����ϱ�

	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (check == 0)
			{
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				check = 1;
			}
			else if (check == 1)
			{
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				check = 0;
			}
			glRectd(j * 100, i * 100, j * 100 + 100, i * 100 + 100);
		}
		if (check == 0)
			check = 1;
		else if (check == 1)
			check = 0;
	}


	glColor4f(0.0f, 0.5f, 0.5f, 1.0f);
	glRectd(0, 0, 100, 100);

	glColor4f(0.0f, 0.5f, 0.0f, 1.0f);
	glRectd(700, 0, 800, 100);


	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRectd(0, 700, 100, 500);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRectd(700, 500, 800, 600);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRectd(350, 250, 450, 350);

	glFlush(); //ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);

}
