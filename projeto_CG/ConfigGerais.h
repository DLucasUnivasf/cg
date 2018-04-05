#ifndef CONFIGGERAIS_H_INCLUDED
#define CONFIGGERAIS_H_INCLUDED

#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <GL/glut.h>
#include <stdio.h>
#include <SDL_mixer.h>

#define NUMERO_DE_TEXTURAS 10

GLfloat r_buraco, g_buraco, b_buraco;
GLfloat **buracos_pos;

int *posicao_digletts;

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
int audio_troll = 0;
int qtd_buracos = 25;
int qtd_digletts = 4;
GLfloat martelo_angulo;
GLfloat new_x, new_y;

GLfloat largura = 800,
        altura  = 500;

GLfloat r_bonus1 = 1,
        g_bonus1 = 1,
        b_bonus1 = 1,
        r_bonus2 = 1,
        g_bonus2 = 1,
        b_bonus2 = 1;

GLuint texture_id[NUMERO_DE_TEXTURAS]; //armazena referencia as texturas

int textura_animacao_diglett = 0; //de acordo com o valor desta variavel, seleciona textura do diglett
short hit = -1; //flag que sinaliza quando diglett e atingido
short erros_consecutivos = 0;
short acertos_consecutivos = 0;
short bonus_pontos_dobrados = -1;
short bonus_desacelera = -1;
short tempo_default = 1500;
short novo_tempo = 2000;
short tempo_animacao;
short acerto_passado = 0;
short pausa = 0;

Mix_Music *music = NULL; //- música de fundo
Mix_Chunk *diglett_sound = NULL; // efeito sonoro do diglett
Mix_Chunk *diglett_out_sound = NULL; //efeito de saida do buraco
Mix_Chunk *not_effective = NULL; //efeito de saida do buraco

void CarregadorDeTextura ( char *file_name, int width, int height, int depth, GLenum colour_type, GLenum filter_type );
void Inicializa(GLfloat e, GLfloat d, GLfloat b, GLfloat c);
void ReiniciaJogo(int opcao);
void GerenciaMouse(int button, int state, int x, int y);
void PosicaoMouse(int x, int y);
void Teclado(unsigned char key, int x, int y);
void TeclasEspeciais(unsigned char key, int x, int y);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);

#endif // CONFIGGERAIS_H_INCLUDED
