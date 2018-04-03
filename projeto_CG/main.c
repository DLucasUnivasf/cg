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
int qtd_digletts = 8;
GLfloat martelo_angulo;
GLfloat new_x, new_y;

GLfloat largura = 700,
        altura  = 500;


GLuint texture_id[NUMERO_DE_TEXTURAS]; //armazena referencia as texturas

int textura_animacao_diglett = 0; //de acordo com o valor desta variavel, seleciona textura do diglett
short hit = -1; //flag que sinaliza quando diglett e atingido
short erros_consecutivos = 0;
short pausa = 0;

Mix_Music *music = NULL; //- música de fundo
Mix_Chunk *diglett_sound = NULL; // efeito sonoro do diglett
Mix_Chunk *diglett_out_sound = NULL; //efeito de saida do buraco
Mix_Chunk *not_effective = NULL; //efeito de saida do buraco


void CarregadorDeTextura ( char *file_name, int width, int height, int depth,GLenum colour_type, GLenum filter_type ){

/*
Carrega textura de arquivo no formato RAW.
*/

    GLubyte *raw_bitmap ;
    FILE *file;

    if (( file = fopen(file_name, "rb"))==NULL ){
        printf ( "Arquivo de textura não Encontrado : %s\n", file_name );
        exit ( 1 );
    }

    raw_bitmap = (GLubyte *)malloc(width * height * depth * (sizeof(GLubyte)));

    if ( raw_bitmap == NULL ){
        printf ( "Nao foi possivel alocar espaço de memória para a textura\n" );
        fclose ( file );
        exit ( 1 );
    }

    fread (raw_bitmap , width * height * depth, 1 , file );
    fclose (file);

    // Define o tipo de filtro a ser utilizado
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_type );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_type );
    // Define o ambiente de Textura
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    // Construção dos MipMaps
    gluBuild2DMipmaps ( GL_TEXTURE_2D, colour_type, width, height, colour_type,
    GL_UNSIGNED_BYTE, raw_bitmap );
    // Libera a memoria alocada para o array
    free (raw_bitmap);

}

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
             //glColor4f(1, 1, 1,1);
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

void geradorDeDigletts()
{
    static clock_t ult_chamada_t, cham_atual_t, total_t;

    cham_atual_t = clock();
    total_t = (double)(cham_atual_t - ult_chamada_t) / (CLOCKS_PER_SEC/1000);
    /*Em ms*/

    if(total_t >= 2000){
        hit = -1;
        int i,j;
        int audio_troll, anti_loop_eterno = 0;
        /*Vetor auxiliar para evitar que digletts sejam colocados no mesmo buraco consecutivamente*/
        int* aux_posicao_digletts = (int *)malloc(sizeof(int) * qtd_digletts);

        for(i = 0; i < qtd_digletts; i++){
            aux_posicao_digletts[i] = posicao_digletts[i];
        }

        for ( i = 0; i < qtd_digletts; i++ ){
            audio_troll = (int)rand()%qtd_buracos;

            for(j = 0 ; j < qtd_digletts ; j++)
                if (audio_troll == posicao_digletts[j] || audio_troll == aux_posicao_digletts[j]){
                    audio_troll = -1;
                    break;}

            if( audio_troll != -1 )
                posicao_digletts[i] = audio_troll;
            else
                i--;

            anti_loop_eterno++;

            if( anti_loop_eterno > 5000 ){
                printf("Nem a Coração De Ouro conseguiria algo tao improvavel, voce nao merece esse jogo. Adeus!");
                getchar();
                exit(1);
            }
        }

        free(aux_posicao_digletts);
        ult_chamada_t = clock();
        }
}

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
    char *string = "Pontos", pts[qtd];
    sprintf(pts, "%d", pontos);

    glPushMatrix();
    glTranslatef(dir + 5, cimag-6, 0);
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

    glTranslatef(dir + deslocamento, cimag-14, 0);
    glScalef(0.07, 0.05, 0.1);

    for (i = 0; i < qtd; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, pts[i]);

    glPopMatrix();
    glutSwapBuffers();
}

void DesenhaCard(){
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);glVertex2f(70, 0);
            glTexCoord2f(1.0f, 0.0f);glVertex2f(100, 0);
            glTexCoord2f(1.0f, 1.0f);glVertex2f(100, 20);
            glTexCoord2f(0.0f, 1.0f);glVertex2f(70, 20);
        glEnd();
}

void DesenhaPainelLateral()
{
    static short audio_troll = 1, hunter_master = 1;

    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, texture_id[4]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);glVertex2f(70, 30);
        glTexCoord2f(1.0f, 0.0f);glVertex2f(100, 30);
        glTexCoord2f(1.0f, 1.0f);glVertex2f(100, 50);
        glTexCoord2f(0.0f, 1.0f);glVertex2f(70, 50);
    glEnd();
    glDisable(GL_TEXTURE_2D);

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
    DesenhaPainelLateral();
    DesenhaPontos();
    CalculaBuracos();
    DesenhaMartelo();


    glFlush();
    //glutSwapBuffers();
}

void AnimaDigletts(int value)
{
    if(!pausa){

        textura_animacao_diglett = value;
        Desenha();
        glFlush();

        /*Gambiarra, consertar quando definir regras de jogo*/
        if(value == 2){
        geradorDeDigletts();
        glutTimerFunc(300,AnimaDigletts, 3);
        Mix_PlayChannel( -1, diglett_out_sound, 0 );} //som de saida de digletts
        else
        glutTimerFunc(300,AnimaDigletts, 2);
    }
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

    srand(time(NULL));

    /*Habilita a transparencia*/
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /*Impede manter memoria alocada desnecessariamente cada vez que o game for reiniciado*/
    free(posicao_digletts);
    posicao_digletts = (int *)malloc(sizeof(int) * qtd_digletts);

    glEnable ( GL_TEXTURE_2D );
    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
    glGenTextures ( NUMERO_DE_TEXTURAS, texture_id );

    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
    CarregadorDeTextura ( "textures/lawn_1024.raw", 1024,1024, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    CarregadorDeTextura ( "textures/lawn_hole_128.raw", 128, 128, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    CarregadorDeTextura ( "textures/diglett_getting_out_128.raw", 128, 128, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
    CarregadorDeTextura ( "textures/diglett_outside_128.raw", 128, 128, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
    CarregadorDeTextura ( "textures/board_512x256.raw", 512, 256, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[5] );
    CarregadorDeTextura ( "textures/diglett_smash_128.raw", 128, 128, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[6] );
    CarregadorDeTextura ( "textures/marreta_128_512.raw", 122, 50, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[7] );
    CarregadorDeTextura ( "textures/not_effective_256.raw", 256, 256, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[8] );
    CarregadorDeTextura ( "textures/digllet_hunter_master_256.raw", 256, 256, 3, GL_RGB, GL_NEAREST );
    glBindTexture ( GL_TEXTURE_2D, texture_id[9] );
    CarregadorDeTextura ( "textures/paused_256.raw", 256, 256, 3, GL_RGB, GL_NEAREST );

    geradorDeDigletts();


    if( SDL_Init(SDL_INIT_AUDIO ) < 0 ){
       printf( "Erro ao inicializar SDL! -> %s\n", SDL_GetError() );
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
       printf( "Erro ao inicializar SDL_Mixer! -> %s\n", Mix_GetError() );
    }

     music = Mix_LoadMUS("sounds/music/pokemon.mp3");
     diglett_out_sound = Mix_LoadWAV("sounds/wav/diglett_out.wav");
     diglett_sound = Mix_LoadWAV("sounds/wav/diglett_smash.wav");
     not_effective = Mix_LoadWAV("sounds/wav/not_effective.wav");

     /*Volume varia entre 0 e 128*/
     Mix_VolumeMusic(15);
     Mix_VolumeChunk(diglett_sound,MIX_MAX_VOLUME);
     Mix_VolumeChunk(not_effective,MIX_MAX_VOLUME/4);
     Mix_VolumeChunk(diglett_out_sound,MIX_MAX_VOLUME/2);
     Mix_FadeInMusic(music, -1, 2000);

}

void ReiniciaJogo(int opcao)
{
    switch(opcao)
    {
        case 0:
            qtd_buracos = 4;
            qtd_digletts = 1;
            break;
        case 1:
            qtd_buracos = 9;
            qtd_digletts = 2;
            break;
        case 2:
            qtd_buracos = 16;
            qtd_digletts = 3;
            break;
        case 3:
            qtd_buracos = 25;
            qtd_digletts = 4;
            audio_troll = 1;
    }

    //Inicializa(0, 0, 0, 0);
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
    GLfloat x_aux, y_aux;
    int pos_clicada,i;
    short acertou_diglett = 0;

    if (button == GLUT_LEFT_BUTTON && !pausa)
    {
        if (state == GLUT_DOWN)
        {
            x_aux = (float)x;
            y_aux = (float)y;

            new_x =         (x_aux * (dirg  - esq))/largura;
            new_y = cimag - (y_aux * (cimag - base))/altura;

            pos_clicada = buracoAcertado(new_x, new_y);

            for (i = 0 ; i < qtd_digletts; i++){
                if(pos_clicada == posicao_digletts[i]){
                    if(pos_clicada != hit)
                        pontos++;
                    hit = pos_clicada;
                    acertou_diglett = 1;
                    erros_consecutivos = 0;
                    Mix_PlayChannel( -1, diglett_sound, 0 );}
            }

            /*Verifica se jogador clicou em buraco sem diglett*/
            if(!acertou_diglett && pos_clicada != -1){
                if(pontos > 0)
                    pontos--;
                    erros_consecutivos++;
            }

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
    static int mute = 0;

    if (key == 27)
        exit(0);

    if (key == 80 || key == 112){
        if(!pausa){
            pausa = 1;
            Desenha();}
        else{
            pausa = 0;
            AnimaDigletts(2);}
    }
    if (key == 77 || key == 109){
            printf("here");

        if(!mute){
            Mix_Volume(-1,0);
            Mix_VolumeMusic(0);
            mute = 1;
        }
        else{
            mute = 0;
            Mix_Volume(-1,MIX_MAX_VOLUME/4);
            Mix_VolumeMusic(MIX_MAX_VOLUME/16);
        }
    }
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

int main(int argc, char* argv[])
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("Diglett WAR! Computacao Grafica - Daniel e Daniele");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);

    glutPassiveMotionFunc(PosicaoMouse);
    glutMouseFunc(GerenciaMouse);
    glutTimerFunc(500, AnimaDigletts, 2);

    Inicializa(esq, dirg, base, cimag);

    glutMainLoop();

    return 0;
}
