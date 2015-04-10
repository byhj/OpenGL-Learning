#include <GL/freeglut.h>

void init()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("ch1-window");
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
