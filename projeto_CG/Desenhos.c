#include "Desenhos.h"

void DesenhaMartelo()
{
    glPushMatrix();
    glTranslatef(new_x, new_y, 0);
    glRotatef(martelo_angulo, 0, 0, 1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[6] );

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(-larg_buraco/10, -alt_buraco/3);
        glTexCoord2f(1.0f, 0.0f);glVertex2f( larg_buraco/2 , -alt_buraco/3);
        glTexCoord2f(1.0f, 1.0f);glVertex2f( larg_buraco/2 ,  alt_buraco/3);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(-larg_buraco/10,  alt_buraco/3);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(-larg_buraco/10  +   larg_buraco/5, -alt_buraco/3);
        glVertex2f( larg_buraco/10  +   larg_buraco/5, -alt_buraco/3);
        glVertex2f( larg_buraco/10  +   larg_buraco/5, -alt_buraco);
        glVertex2f(-larg_buraco/10  +   larg_buraco/5, -alt_buraco);
    glEnd();
    glPopMatrix();

}

void DesenhaPontos()
{

    glColor3f(1, 1, 1);
    int i, qtd = (pontos == 0) ? 1: floor(log10(abs(pontos)))+1;
    char *string = "Pontos", *info[4], pts[qtd];
    short desloc = 20;
    sprintf(pts, "%d", pontos);

    info[0] = "(M)ute (R)estart";
    info[1] = "(P)ause ESC sair";
    info[2] = "F1 Pts dobrados";
    info[3] = "F2 Slow";

    glPushMatrix();
    glTranslatef(dir + 5, cimag - 5, 0);
    glScalef(0.05, 0.03, 0.1);
    glLineWidth(2);

    while(*string)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *string++);

    glPopMatrix();

    glPushMatrix();

    short deslocamento = 12;

    if(pontos >= 10 && pontos < 100)
        deslocamento = 10;
    else if (pontos >= 100)
        deslocamento = 7;

    glTranslatef(dir + deslocamento, cimag - 12, 0);
    glScalef(0.07, 0.05, 0.1);

    for (i = 0; i < qtd; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, pts[i]);

    glPopMatrix();

    for (i = 0; i < 2; i++)
    {
        glPushMatrix();

        glTranslatef(dir + 1.5, cimag - desloc, 0);
        glScalef(0.025, 0.02, 0.08);

        while(*info[i])
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *info[i]++);

        glPopMatrix();
        desloc += 3;
    }

    glPushMatrix();
    glColor3f(r_bonus1, g_bonus1, b_bonus1);
    glTranslatef(dir + 1.5, cimag - desloc, 0);
    glScalef(0.025, 0.02, 0.08);
    while(*info[2])
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *info[2]++);
    glPopMatrix();
    desloc += 3;

    glPushMatrix();
    glColor3f(r_bonus2, g_bonus2, b_bonus2);
    glTranslatef(dir + 1.5, cimag - desloc, 0);
    glScalef(0.025, 0.02, 0.08);
    while(*info[3])
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *info[3]++);
    glPopMatrix();

    glutSwapBuffers();
}

void DesenhaCard(){
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(dir, base);
        glTexCoord2f(1.0f, 0.0f);glVertex2f(dirg, base);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(dirg, base + 20);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(dir, base + 20);
    glEnd();
}

void DesenhaPainelLateral()
{
    static short audio_troll = 1, hunter_master = 1;

    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[4]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(dir, cimag - 15);
        glTexCoord2f(1.0f, 0.0f);glVertex2f(dirg, cimag - 15);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(dirg, cimag);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(dir, cimag);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[4]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(dir, base);
        glTexCoord2f(1.0f, 0.0f);glVertex2f(dirg, base);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(dirg, cimag - 15);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(dir, cimag - 15);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    DesenhaPontos();

    if (erros_consecutivos >= 5){
        if(audio_troll){
            Mix_PlayChannel( -1, not_effective, 0 );
            audio_troll = 0;}
        glEnable(GL_TEXTURE_2D);
        glBindTexture ( GL_TEXTURE_2D, texture_id[7]);
        DesenhaCard();
    }

    if (pontos >= 100 && hunter_master < 150){
        glEnable(GL_TEXTURE_2D);
        glBindTexture ( GL_TEXTURE_2D, texture_id[8]);
        DesenhaCard();
        hunter_master++;
    }

    if(pausa){
        glEnable(GL_TEXTURE_2D);
        glBindTexture ( GL_TEXTURE_2D, texture_id[9]);
        DesenhaCard();
    }

}

void DesenhaTelaPrincipal()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[0]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(esq, base);
        glTexCoord2f(1.0f, 0.0f);glVertex2f(dir, base);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(dir, cima);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(esq, cima);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void Desenha()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DesenhaTelaPrincipal();
    CalculaBuracos();
    DesenhaPainelLateral();
    DesenhaMartelo();
    glFlush();
}
