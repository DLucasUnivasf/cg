#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <GL/glut.h>

GLfloat r_buraco, g_buraco, b_buraco;
GLfloat **buracos_pos;
int *objetos_pos;
GLfloat larg_buraco, alt_buraco;
GLfloat dist_buraco_x, dist_buraco_y;
GLfloat desloc_x, desloc_y;

GLfloat dirg    = 100.0f,
        cimag   = 50.0f;

GLfloat esq     = 0.0f,
        dir     = 70.0f,
        base    = 0.0f,
        cima    = 50.0f;

int pontos = 0;
int aux = 0;
int qtd_buracos = 4;
int qtd_objetos = 1;
GLfloat martelo_angulo;
GLfloat new_x, new_y;

GLfloat largura = 700,
        altura  = 500;


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

    GLfloat raizf   = sqrt(qtd_buracos);
    GLint raizi     = raizf;
    GLint qtd       = raizi * raizi;
    GLint rest      = qtd_buracos - qtd;

    GLint linha_rest;
    GLint qtdx_aux, qtdy_aux, rest_ult_linha;

    GLfloat pos_x, pos_y;

    linha_rest      = rest / raizi;
    rest_ult_linha  = rest % raizi;

    larg_buraco     = (dir - esq)/(raizi + 1);
    alt_buraco      = (rest_ult_linha == 0) ? (cima - base)/(raizi + linha_rest + 1) : (cima - base)/(raizi + linha_rest + 2);

    dist_buraco_x   = larg_buraco / (raizi + 1);
    dist_buraco_y   = (rest_ult_linha == 0) ? alt_buraco / (raizi + linha_rest + 1) : alt_buraco / (raizi + linha_rest + 2);

    qtdy_aux        = (rest_ult_linha == 0) ? raizi + linha_rest : raizi + linha_rest + 1;

    qtdx_aux        = raizi;

    for (i = 0; i < qtdy_aux; i++)
    {
        if (i == qtdy_aux - 1)
            qtdx_aux = (rest_ult_linha > 0) ? rest_ult_linha : raizi;

        for (j = 0; j < qtdx_aux; j++)
        {
            pos_x = (float)(j * larg_buraco + (j + 1) * dist_buraco_x);
            pos_y = (float)(i * alt_buraco  + (i + 1) * dist_buraco_y);

            glBegin(GL_POLYGON);
            glColor3f(r_buraco, g_buraco, b_buraco);
            glVertex3f(pos_x              , pos_y             , 0);
            glVertex3f(pos_x + larg_buraco, pos_y             , 0);
            glVertex3f(pos_x + larg_buraco, pos_y + alt_buraco, 0);
            glVertex3f(pos_x              , pos_y + alt_buraco, 0);
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
        if((x > buracos_pos[i][0] && x < buracos_pos[i][1]) &&
           (y > buracos_pos[i][2] && y < buracos_pos[i][3]))
                return i;
    }

    return -1;
}

void objetoAcertado(int buraco)
{
    int i;

    for(i = 0; i < qtd_objetos; i++)
    {
        if (objetos_pos[i] == buraco)
        {
            pontos += qtd_buracos * qtd_objetos;
            AlocaObjetos();

            if (aux && (pontos > qtd_buracos * qtd_objetos * 10))
            {
                qtd_buracos = (qtd_buracos == 81) ? 81 : pow(sqrt(qtd_buracos) + 1, 2);
                qtd_objetos = (qtd_objetos == 10) ? 10 : qtd_objetos+1;

            }
        }
    }
    glutPostRedisplay();
}

void AlocaObjetos()
{
    int i;

    objetos_pos = (int *)malloc(sizeof(int) * qtd_objetos);

    for (i = 0; i < qtd_objetos; i++)
        objetos_pos[i] = (int)rand()%qtd_buracos;
}

int ContemObjeto(int buraco)
{
    int i, j;

    for (i = 0; i < qtd_buracos; i++)
    {
        for (j = 0; j < qtd_objetos; j++)
        {
            if (objetos_pos[j] == i) return 1;
        }
    }

    return 0;
}

void DesenhaObjeto()
{
    int i;

    desloc_x = larg_buraco/7;
    desloc_y = alt_buraco/7;

    for (i = 0; i < qtd_buracos; i++)
    {
        glPushMatrix();
        glColor3f(0.5, 0, 0);

        glTranslatef(buracos_pos[i][0] + desloc_x, buracos_pos[i][2] + desloc_y, 0);
        glScalef(0.7, 0.7, 0.7);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(larg_buraco, 0);
        glVertex2f(larg_buraco, alt_buraco);
        glVertex2f(0, alt_buraco);
        glEnd();
        glPopMatrix();
    }
}

void DesenhaMartelo()
{
    glPushMatrix();
    glTranslatef(new_x, new_y, 0);
    glRotatef(martelo_angulo, 0, 0, 1);

    glBegin(GL_QUADS);
    glColor3f(0.545f, 0.271f, 0.075f);
    glVertex2f(-larg_buraco/10, -alt_buraco/3);
    glVertex2f( larg_buraco/2 , -alt_buraco/3);
    glVertex2f( larg_buraco/2 ,  alt_buraco/3);
    glVertex2f(-larg_buraco/10,  alt_buraco/3);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-larg_buraco/10  +   larg_buraco/5, -alt_buraco/3);
    glVertex2f( larg_buraco/10  +   larg_buraco/5, -alt_buraco/3);
    glVertex2f( larg_buraco/10  +   larg_buraco/5, -alt_buraco);
    glVertex2f(-larg_buraco/10  +   larg_buraco/5, -alt_buraco);
    glEnd();
    glPopMatrix();
}

void DesenhaPontos()
{
    int i, qtd = (pontos == 0) ? 1: floor(log10(abs(pontos)))+1;
    char *string = "Pontos", pts[qtd];
    sprintf(pts, "%d", pontos);

    glPushMatrix();
    glTranslatef(dir, cimag-6, 0);
    glScalef(0.07, 0.05, 0.1);
    glLineWidth(2);

	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(dir, cimag-12, 0);
    glScalef(0.07, 0.05, 0.1);

    for (i = 0; i < qtd; i++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, pts[i]);

    glPopMatrix();
    glutSwapBuffers();
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

    DesenhaPontos();
    CalculaBuracos();
    //AlocaObjetos();
    DesenhaObjeto();
    DesenhaMartelo();
    glFlush();
}

void Inicializa(GLfloat e, GLfloat d, GLfloat b, GLfloat c)
{
    r_buraco        = 0.5;
    g_buraco        = 0.5;
    b_buraco        = 0.5;
    martelo_angulo  = 45;

    pontos = 0;

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (e, d, b, c);

    AlocaObjetos();
    srand(time(NULL));
}

void ReiniciaJogo(int opcao)
{
    switch(opcao)
    {
        case 0:
            qtd_buracos = 4;
            qtd_objetos = 1;
            break;
        case 1:
            qtd_buracos = 9;
            qtd_objetos = 2;
            break;
        case 2:
            qtd_buracos = 16;
            qtd_objetos = 3;
            break;
        case 3:
            qtd_buracos = 25;
            qtd_objetos = 4;
            aux = 1;
    }

    Inicializa(0, 0, 0, 0);
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
    GLfloat x_aux, y_aux;
    int pos, hit;

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            x_aux = (float)x;
            y_aux = (float)y;

            new_x =         (x_aux * (dirg  - esq))/largura;
            new_y = cimag - (y_aux * (cimag - base))/altura;

            pos = buracoAcertado(new_x, new_y);
            objetoAcertado(pos);
            martelo_angulo = 90;
        }
    }

    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            glutCreateMenu(ReiniciaJogo);
            glutAddMenuEntry("Fácil", 0);
            glutAddMenuEntry("Intermediário", 1);
            glutAddMenuEntry("Difícil", 2);
            glutAddMenuEntry("Avançado", 3);

            glutAttachMenu(GLUT_RIGHT_BUTTON);
        }
    }
    glutPostRedisplay();
}

void PosicaoMouse(int x, int y)
{
    GLfloat x_aux, y_aux;

    x_aux = (float)x;
    y_aux = (float)y;
    new_x =         (x_aux * (dirg - esq))/largura;
    new_y = cimag - (y_aux * (cimag - base))/altura;

    if (martelo_angulo == 90) martelo_angulo = 45;
    glutPostRedisplay();
}

void Teclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
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

int main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    glutPassiveMotionFunc(PosicaoMouse);
    glutMouseFunc(GerenciaMouse);
    Inicializa(esq, dirg, base, cimag);
    glutMainLoop();
}
