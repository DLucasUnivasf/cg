#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

GLfloat dirg = 100.0f, cimag = 50.0f;
GLfloat esq = 0.0f, dir = 70.0f, base = 0.0f, cima = 50.0f;
GLfloat largura = 700, altura = 500;
int qtd_buracos = 1;
GLfloat r_buraco, g_buraco, b_buraco;
GLfloat **buracos_pos;

void Inicializa ()
{
    r_buraco = 0.5;
    g_buraco = 0.5;
    b_buraco = 0.5;
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (esq, dirg, base, cimag);

    //srand(time(NULL));
}

void salvaPosicao(GLfloat pos_x, GLfloat pos_y, GLfloat larg_buraco, GLfloat alt_buraco, int ctr)
{
    buracos_pos[ctr][0] = pos_x;
    buracos_pos[ctr][1] = pos_x + larg_buraco;
    buracos_pos[ctr][2] = pos_y;
    buracos_pos[ctr][3] = pos_y + alt_buraco;
}

void CalculaBuracos(void)
{
    int i, j, ctr = 0;
    buracos_pos = (GLfloat **)malloc(sizeof(GLfloat *) * qtd_buracos);

    for (i = 0; i < qtd_buracos; i++)
        buracos_pos[i] = (GLfloat *)malloc(sizeof(GLfloat) * 4);

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
            glColor3f(r_buraco, g_buraco, b_buraco);
            glVertex3f(pos_x, pos_y, 0);
            glVertex3f(pos_x + larg_buraco, pos_y, 0);
            glVertex3f(pos_x + larg_buraco, pos_y + alt_buraco, 0);
            glVertex3f(pos_x, pos_y + alt_buraco, 0);
            glEnd();

            salvaPosicao(pos_x, pos_y, larg_buraco, alt_buraco, ctr);
            ctr++;
        }
    }
}

int buracoAcertado(GLfloat x, GLfloat y)
{
    int i;

    for (i=0; i<qtd_buracos; i++)
    {
        if((x > buracos_pos[i][0] && x < buracos_pos[i][1]) && (y > buracos_pos[i][2] && y < buracos_pos[i][3]))
            return i;
    }

    return -1;
}

void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(esq, base);
    glVertex2f(dir, base);
    glVertex2f(dir, cima);
    glVertex2f(esq, cima);
    glEnd();
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
        qtd_buracos = (qtd_buracos == 1) ? 1 : qtd_buracos-1;

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

    gluOrtho2D (esq, dirg, base, cimag);
}

void GerenciaMouse(int button, int state, int x, int y)
{
    GLfloat new_x, new_y, x_aux, y_aux;
    int pos;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            x_aux = (float)x;
            y_aux = (float)y;

            new_x = (x_aux * (dirg - esq))/largura;
            new_y = cimag - (y_aux * (cimag - base))/altura;
            pos = buracoAcertado(new_x, new_y);
            //if(pos != -1) faz algo
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
    Inicializa();

    glutMainLoop();
}