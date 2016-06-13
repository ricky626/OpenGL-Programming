#include <GL/glut.h> // includes gl.h glu.h
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[])
{
	//초기화 함수들 glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA );
	// 디스플레이 모드 설정 glutInitWindowPosition ( 100, 100 );
	// 윈도우의 위치지정 glutInitWindowSize ( 250, 250 ); 
	// 윈도우의 크기 지정 glutCreateWindow ( "Example2" ); 
	// 윈도우 생성 (윈도우 이름)  glutDisplayFunc ( drawScene ); // 출력 함수의 지정


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	int check = 0;

	// 바탕색을 'blue' 로 지정 glClear( GL_COLOR_BUFFER_BIT );
	// 설정된 색으로 젂체를 칠하기 glColor4f(0.0f, 1.0f, 0.0f, 1.0f); 
	// 그리기 색을 'green' 으로 지정 glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	// 사각형 그리기 glFlush(); // 화면에 출력하기

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

	glFlush(); //화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);

}
