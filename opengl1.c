#include <windows.h>
#include <GL/glut.h>

/*Por: Daniele Silva Reis*/

void Inicializa1 (void)
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,20.0,0.0,20.0);
}

void Desenha1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(12.0, 14.0);
    glVertex2i(10.0, 16.0);
    glVertex2i(8.0, 14.0);
    glVertex2i(10.0, 12.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.5f);
    glVertex2i(9.0, 11.0);
    glVertex2i(7.0, 13.0);
    glVertex2i(5.0, 11.0);
    glVertex2i(7.0, 9.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2i(12.0, 8.0);
    glVertex2i(10.0, 10.0);
    glVertex2i(8.0, 8.0);
    glVertex2i(10.0, 6.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(15.0, 11.0);
    glVertex2i(13.0, 13.0);
    glVertex2i(11.0, 11.0);
    glVertex2i(13.0, 9.0);
    glEnd();

    glFlush();
}

void Inicializa2 (void)
{
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,20.0,0.0,20.0);
}

void Desenha2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(10.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(17.0, 17.0);
    glVertex2i(3.0, 17.0);
    glVertex2i(3.0, 3.0);
    glVertex2i(17.0, 3.0);
    glEnd();

    /*glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(16.0, 17.0);
    glVertex2i(3.0, 17.0);
    glVertex2i(3.0, 3.0);
    glVertex2i(17.0, 3.0);
    glEnd();*/

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(10.0, 20.0);
    glVertex2i(10.0, 0.0);

    glVertex2i(0.0, 10.0);
    glVertex2i(20.0, 10.0);
    glEnd();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2i(10.0, 10.0);
    glEnd();

    glFlush();
}

void Inicializa3(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,20.0,0.0,20.0);
}

void Desenha3(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.5f, 1.0f, 0.0f);
    glVertex2i(12.0, 10.0);
    glVertex2i(9.0, 14.0);

    glVertex2i(10.0, 14.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(8.0, 10.0);

    glVertex2i(8.0, 10.0);
    glVertex2i(5.0, 6.0);

    glVertex2i(5.0, 6.0);
    glColor3f(0.0f, 0.0f, 0.804f);
    glVertex2i(10.0, 7.5);

    glVertex2i(10.0, 7.5);
    glVertex2i(15.0, 6.0);

    glVertex2i(15.0, 6.0);
    glColor3f(0.5f, 1.0f, 0.0f);
    glVertex2i(12.0, 10.0);
    glEnd();

    glFlush();
}

int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Primeiro Programa");

    glutDisplayFunc(Desenha1);
    Inicializa1();

    //glutDisplayFunc(Desenha2);
    //Inicializa2();

    //glutDisplayFunc(Desenha3);
    //Inicializa3();

    glutMainLoop();
}
