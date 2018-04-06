#include "Buracos.h"

void salvaPosicao(GLfloat pos_x, GLfloat pos_y, GLfloat larg_buraco, GLfloat alt_buraco, int ctr)
{
    buracos_pos[ctr][0] = pos_x;
    buracos_pos[ctr][1] = pos_x + larg_buraco;
    buracos_pos[ctr][2] = pos_y;
    buracos_pos[ctr][3] = pos_y + alt_buraco;
}

void CalculaBuracos()
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


            glEnable(GL_TEXTURE_2D);

            int posicao = i * raizi + j;

            int audio_troll;
            for (audio_troll = 0 ; audio_troll < qtd_digletts; audio_troll++){
                if(posicao == posicao_digletts[audio_troll]){
                        if(posicao == hit)
                            glBindTexture ( GL_TEXTURE_2D, texture_id[5]);
                        else if(textura_animacao_diglett == 2)
                            glBindTexture ( GL_TEXTURE_2D, texture_id[2]);
                        else
                            glBindTexture ( GL_TEXTURE_2D, texture_id[3]);
                    break;
                }
                else
                    glBindTexture ( GL_TEXTURE_2D, texture_id[1]);
            }

             glBegin(GL_POLYGON);
             glTexCoord2f(0.0f, 0.0f);glVertex3f(pos_x               , pos_y             , 0);
             glTexCoord2f(1.0f, 0.0f); glVertex3f(pos_x + larg_buraco, pos_y             , 0);
             glTexCoord2f(1.0f, 1.0f); glVertex3f(pos_x + larg_buraco, pos_y + alt_buraco, 0);
             glTexCoord2f(0.0f, 1.0f);glVertex3f(pos_x               , pos_y + alt_buraco, 0);
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
