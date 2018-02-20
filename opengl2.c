#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>

#define PI 3.14159265

GLfloat dx, dy, step;
GLfloat ang, ang_step;

void Inicializa (void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (-7.0f, 13.0f, -3.0f, 17.0f);

    dx = dy = ang = 0.0;
    ang_step = 2;
    step = 0.3;
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

    glVertex2f(0.75, 5.0);
    glVertex2f(-3.25, 5.0);

    glVertex2f(-4.75, 3.5);
    glVertex2f(-4.75, 10.5);

    glVertex2f(-3.25, 5.0);
    glVertex2f(-3.25, 9.0);

    glVertex2f(-4.75, 10.5);
    glVertex2f(5.25, 10.5);

    glVertex2f(-3.25, 9.0);
    glVertex2f(3.75, 9.0);

    glVertex2f(5.25, 10.5);
    glVertex2f(5.25, 7.5);

    glVertex2f(3.75, 9.0);
    glVertex2f(3.75, 6.0);

    glVertex2f(5.25, 7.5);
    glVertex2f(6.25, 7.5);

    glVertex2f(3.75, 6.0);
    glVertex2f(7.75, 6.0);

    glVertex2f(6.25, 7.5);
    glVertex2f(6.25, 12.5);

    glVertex2f(7.75, 6.0);
    glVertex2f(7.75, 11.0);

    glVertex2f(6.25, 12.5);
    glVertex2f(11.25, 12.5);

    glVertex2f(7.75, 11.0);
    glVertex2f(11.25, 11.0);

    glEnd();
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaLabirinto();

    glTranslatef(dx, dy, 0.0);
    glRotatef(ang, 0.0f, 0.0f, 1.0f);

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
    if (ang < 0) ang += 360;
    ang = fmod(ang, 360);
    if (key == GLUT_KEY_UP)
    {
        if (ang >= 0 && ang <= 90)
        {
            dy += cos(fabs(ang)*PI/180) * step;
            dx -= sin(fabs(ang)*PI/180) * step;
        }
        else if (ang > 90 && ang <= 180)
        {
            dy -= -cos(fabs(ang)*PI/180) * step;
            dx -= sin(fabs(ang)*PI/180) * step;
        }
        else if (ang > 180 && ang <= 270)
        {
            dy -= -cos(fabs(ang)*PI/180) * step;
            dx += -sin(fabs(ang)*PI/180) * step;
            printf("%f %f\n", -sin(fabs(ang)*PI/180) * step, -cos(fabs(ang)*PI/180) * step);
        }
        else if (ang > 270 && ang <= 360)
        {
            dy += cos(fabs(ang)*PI/180) * step;
            dx += -sin(fabs(ang)*PI/180) * step;
        }
    }
    else if (key == GLUT_KEY_DOWN)
    {
        if (ang >= 0 && ang <= 90)
        {
            dy -= cos(ang*PI/180) * step;
            dx += sin(ang*PI/180) * step;
            printf("%f %f\n", sin(ang*PI/180) * step, cos(ang*PI/180) * step);
        }
        else if (ang > 90 && ang <= 180)
        {
            dy += -cos(ang*PI/180) * step;
            dx += sin(ang*PI/180) * step;
        }
        else if (ang > 180 && ang <= 270)
        {
            dy += -cos(ang*PI/180) * step;
            dx -= -sin(ang*PI/180) * step;
        }
        else if (ang > 270 && ang <= 360)
        {
            dy -= cos(ang*PI/180) * step;
            dx -= -sin(ang*PI/180) * step;
        }
    }
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
