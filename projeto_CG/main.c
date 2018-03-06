#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

GLfloat esq = 0.0f, dir = 50.0f, base = 0.0f, cima = 50.0f;
GLfloat largura = 500, altura = 500;
GLint qtd_buracos = 1;

void Inicializa (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (esq, dir, base, cima);

}

void CalculaBuracos(void)
{
    int i, j;

    GLfloat raizf = sqrt(qtd_buracos);
    GLint raizi = raizf, qtd = raizi * raizi;
    GLint rest = qtd_buracos - qtd;
    GLint linha_rest;
    GLfloat larg_buraco, alt_buraco;
    GLfloat dist_buraco_x, dist_buraco_y;
    GLint qtdx_aux, qtdy_aux, rest_ult_linha;

    GLfloat pos_x, pos_y;

    linha_rest = rest / raizi;
    rest_ult_linha = rest % raizi;

    larg_buraco = (dir - esq)/(raizi + 1);
    alt_buraco = (rest_ult_linha == 0) ? (cima - base)/(raizi + linha_rest + 1) : (cima - base)/(raizi + linha_rest + 2);

    dist_buraco_x = larg_buraco / (raizi + 1);
    dist_buraco_y = (rest_ult_linha == 0) ? alt_buraco / (raizi + linha_rest + 1) : alt_buraco / (raizi + linha_rest + 2);

    qtdy_aux = (rest_ult_linha == 0) ? raizi + linha_rest : raizi + linha_rest + 1;

    //printf("qtd_buracos %d | raizi %d | qtd %d | rest %d | linh_rest %d | rest_ult_linha %d | qtdy_aux %d | \n", qtd_buracos, raizi, qtd, rest, linha_rest, rest_ult_linha, qtdy_aux);

    qtdx_aux = raizi;
    for (i=0; i<qtdy_aux; i++)
    {
        if (i == qtdy_aux - 1)
            qtdx_aux = (rest_ult_linha > 0) ? rest_ult_linha : raizi;

        for (j=0; j<qtdx_aux; j++)
        {
            pos_x = (float)(j*larg_buraco+(j+1)*dist_buraco_x);
            pos_y = (float)(i*alt_buraco+(i+1)*dist_buraco_y);

            glBegin(GL_POLYGON);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(pos_x, pos_y, 0);
            glVertex3f(pos_x + larg_buraco, pos_y, 0);
            glVertex3f(pos_x + larg_buraco, pos_y + alt_buraco, 0);
            glVertex3f(pos_x, pos_y + alt_buraco, 0);
            glEnd();
        }
    }
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    CalculaBuracos();
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
    else if (key == 43)
        qtd_buracos++;
    else if (key == 45)
        qtd_buracos--;

    glutPostRedisplay();
}

void SetasTeclado(unsigned char key, int xp, int yp)
{
    //glutPostRedisplay();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    largura = w;
    altura = h;

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluOrtho2D (esq, dir, base, cima);
}

void GerenciaMouse(int button, int state, int x, int y)
{
    GLfloat new_x, new_y, x_aux, y_aux;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            x_aux = (float)x;
            y_aux = (float)y;

            new_x = (x_aux * (dir - esq))/largura;
            new_y = (y_aux * (cima - base))/altura;
        }
    }
}

int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    //glutSpecialFunc(SetasTeclado);
    glutMouseFunc(GerenciaMouse);
    Inicializa(esq, dir, base, cima);

    glutMainLoop();
}
