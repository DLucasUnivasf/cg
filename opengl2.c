#include <math.h>
#include <windows.h>
#include <GL/glut.h>

GLfloat dx, dy, step;
GLfloat ang, ang_step;
GLfloat px, py;

void Inicializa (void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (-7.0f, 13.0f, -3.0f, 17.0f);

    dx = dy = ang = px = 0.0;
    py = 1.0;
    ang_step = 2;
    step = 0.5;
}

void DesenhaLabirinto()
{
    glLineWidth(3.0);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(-0.75, 0.5);
    glVertex2f(-0.75, 3.5);

    glVertex2f(0.75, 0.5);
    glVertex2f(0.75, 5.0);

    glVertex2f(-0.75, 3.5);
    glVertex2f(-4.75, 3.5);

    glVertex2f(-4.75, 3.5);
    glVertex2f(-4.75, 10.5);

    glVertex2f(-4.75, 10.5);
    glVertex2f(5.25, 10.5);

    glVertex2f(5.25, 10.5);
    glVertex2f(5.25, 7.5);

    glVertex2f(5.25, 7.5);
    glVertex2f(6.25, 7.5);

    glVertex2f(6.25, 7.5);
    glVertex2f(6.25, 12.5);

    glVertex2f(6.25, 12.5);
    glVertex2f(11.25, 12.5);

    glEnd();
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    DesenhaLabirinto();

    glRotatef(ang, 0.0f, 0.0f, 1.0f);
    glTranslatef(dx, dy, 0.0);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    glFlush();
}

void Teclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void SetasTeclado(unsigned char key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        dy += step;
    else if (key == GLUT_KEY_DOWN)
        dy -= step;
    else if (key == GLUT_KEY_LEFT)
        ang += ang_step;

    else if (key == GLUT_KEY_RIGHT)
        ang -= ang_step;

    glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    /*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h)
		gluOrtho2D (0.0f, 20.0f, 0.0f, 20.0f*h/w);
	else
		gluOrtho2D (0.0f, 20.0f*w/h, 0.0f, 20.0f);
    */
}

int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(SetasTeclado);
    Inicializa();

    glutMainLoop();
}
