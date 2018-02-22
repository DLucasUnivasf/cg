#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <GL/glut.h>

#define PI 3.14159265

GLfloat dx, dy, step;
GLfloat ang, ang_step;
GLfloat p1x, p1y, p2x, p2y, p3x, p3y;

GLfloat r_obj, g_obj, b_obj;
GLfloat r_lab, g_lab, b_lab;
GLfloat r_win, g_win, b_win;

GLsizei width = 400, height = 400;

GLfloat left = -7.0f, right = 13.0f, bottom = -3.0f, top = 17.0f;

int status; /*0 - fail | 1 - playing | 2 - success*/

void Inicializa (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
{
    r_obj = g_obj = b_obj = r_lab = g_lab = b_lab = 0.0;
    r_win = g_win = b_win = 1.0;

    glClearColor(r_win, g_win, b_win, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (left, right, bottom, top);

    dx = dy = ang = 0.0;
    ang_step = 10;
    step = 0.3;

    p1x = p1y = p3y = -0.5;
    p2x = 0.0;
    p2y = p3x = 0.5;

    status = 1;

    srand(time(NULL));
}

void DesenhaLabirinto()
{
    glLineWidth(3.0);

    glBegin(GL_LINES);

    /*paredes escondidas*/
    glColor3f(r_win, g_win, b_win);

    glVertex2f(-0.75, -1.0);
    glVertex2f(-0.75, 0.5);

    glVertex2f(0.75, -1.0);
    glVertex2f(0.75, 0.5);

    glVertex2f(-0.75, -1.0);
    glVertex2f(0.75, -1.0);
    /*--------------------*/

    glColor3f(r_lab, g_lab, b_lab);

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

void DesenhaNovaTela(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat x, char *string)
{
    glClearColor(v1, v2, v3, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslatef(x, 7, 0);
    glScalef(0.01, 0.01, 0.01);
    glLineWidth(3);
    DesenhaTextoStroke(GLUT_STROKE_MONO_ROMAN, string);
    glPopMatrix();

    glTranslatef(-6.5, 5, 0);
    glScalef(0.008, 0.012, 1);
	DesenhaTextoStroke(GLUT_STROKE_MONO_ROMAN, "Right click to restart!");

	glutSwapBuffers();
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    switch(status)
    {
        case 0: DesenhaNovaTela(0.698, 0.133, 0.133, 0, "FAIL!"); break;
        case 1:
                DesenhaLabirinto();

                glTranslatef(dx, dy, 0.0);
                glRotatef(ang, 0.0f, 0.0f, 1.0f);

                glBegin(GL_TRIANGLES);
                glColor3f(r_obj, g_obj, b_obj);
                glVertex2f(-0.5, -0.5);
                glVertex2f(0.0, 0.5);
                glVertex2f(0.5, -0.5);
                glEnd();
                break;

        case 2: DesenhaNovaTela(0.133, 0.545, 0.133, -2, "CONGRATS!");
    }

    glFlush();
}

void DesenhaTextoStroke(void *font, char *string)
{
	while(*string)
		glutStrokeCharacter(font, *string++);
}

void Teclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void SetasTeclado(unsigned char key, int xp, int yp)
{
    GLfloat x, y;
    if (ang < 0) ang += 360;
    ang = fmod(ang, 360);

    if (key == GLUT_KEY_UP)
    {
        if (ang >= 0 && ang <= 90)
        {
            dy += cos(ang*PI/180) * step;
            dx -= sin(ang*PI/180) * step;

            x = -sin(ang*PI/180) * step;
            y = cos(ang*PI/180) * step;
        }
        else if (ang > 90 && ang <= 180)
        {
            dy -= -cos(ang*PI/180) * step;
            dx -= sin(ang*PI/180) * step;

            x = -sin(ang*PI/180) * step;
            y = cos(ang*PI/180) * step;
        }
        else if (ang > 180 && ang <= 270)
        {
            dy -= -cos(ang*PI/180) * step;
            dx += -sin(ang*PI/180) * step;

            x = -sin(ang*PI/180) * step;
            y = cos(ang*PI/180) * step;
        }
        else if (ang > 270 && ang <= 360)
        {
            dy += cos(ang*PI/180) * step;
            dx += -sin(ang*PI/180) * step;

            x = -sin(ang*PI/180) * step;
            y = cos(ang*PI/180) * step;
        }
    }
    else if (key == GLUT_KEY_DOWN)
    {
        if (ang >= 0 && ang <= 90)
        {
            dy -= cos(ang*PI/180) * step;
            dx += sin(ang*PI/180) * step;

            x = sin(ang*PI/180) * step;
            y = -cos(ang*PI/180) * step;
        }
        else if (ang > 90 && ang <= 180)
        {
            dy += -cos(ang*PI/180) * step;
            dx += sin(ang*PI/180) * step;

            x = sin(ang*PI/180) * step;
            y = -cos(ang*PI/180) * step;
        }
        else if (ang > 180 && ang <= 270)
        {
            dy += -cos(ang*PI/180) * step;
            dx -= -sin(ang*PI/180) * step;

            x = sin(ang*PI/180) * step;
            y = -cos(ang*PI/180) * step;
        }
        else if (ang > 270 && ang <= 360)
        {
            dy -= cos(ang*PI/180) * step;
            dx -= -sin(ang*PI/180) * step;

            x = sin(ang*PI/180) * step;
            y = -cos(ang*PI/180) * step;
        }
    }
    else if (key == GLUT_KEY_LEFT)
        ang += ang_step;
    else if (key == GLUT_KEY_RIGHT)
        ang -= ang_step;

    p1x += x;
    p2x += x;
    p3x += x;

    p1y += y;
    p2y += y;
    p3y += y;

    glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D (left, right, bottom, top);
}

void RestartGame(int op)
{
    if (op == 0)
    {
        Inicializa(0, 0, 0, 0);
        glutPostRedisplay();
    }
}

void GerenciaMouse(int button, int state, int x, int y)
{
    GLfloat new_x, new_y;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            printf("width: %d | height: %d\n", width, height);
            new_x = (float)((float)x*((float)width/20)/width) - (float)((float)((float)width/400)*7);
            new_y = (float)((float)((float)height/400)*17) - (float)((float)y*((float)height/20)/height);

            if (new_x >= p1x && new_x <= p3x && new_y <= p2y && new_y >= p1y)
            {
                r_obj = (double)(rand()%1001)/1000;
                g_obj = (double)(rand()%1001)/1000;
                b_obj = (double)(rand()%1001)/1000;
            }
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            glutCreateMenu(RestartGame);
            glutAddMenuEntry("Restart", 0);

            glutAttachMenu(GLUT_RIGHT_BUTTON);
        }
    }
    glutPostRedisplay();
}

int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(SetasTeclado);
    glutMouseFunc(GerenciaMouse);
    Inicializa(left, right, bottom, top);

    glutMainLoop();
}
