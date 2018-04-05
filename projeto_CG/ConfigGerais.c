#include "ConfigGerais.h"

void CarregadorDeTextura ( char *file_name, int width, int height, int depth, GLenum colour_type, GLenum filter_type ){

/*
Carrega textura de arquivo no formato RAW.
*/

    GLubyte *raw_bitmap ;
    FILE *file;

    if (( file = fopen(file_name, "rb"))==NULL ){
        printf ( "Arquivo de textura n�o Encontrado : %s\n", file_name );
        exit ( 1 );
    }
    tempo_animacao = tempo_default;

    raw_bitmap = (GLubyte *)malloc(width * height * depth * (sizeof(GLubyte)));

    if ( raw_bitmap == NULL ){
        printf ( "Nao foi possivel alocar espa�o de mem�ria para a textura\n" );
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
    // Constru��o dos MipMaps
    gluBuild2DMipmaps ( GL_TEXTURE_2D, colour_type, width, height, colour_type,
    GL_UNSIGNED_BYTE, raw_bitmap );
    // Libera a memoria alocada para o array
    free (raw_bitmap);

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
            acertos_consecutivos = 0;
            pontos = 0;
            break;
        case 1:
            qtd_buracos = 9;
            qtd_digletts = 2;
            acertos_consecutivos = 0;
            pontos = 0;
            break;
        case 2:
            qtd_buracos = 16;
            qtd_digletts = 3;
            acertos_consecutivos = 0;
            pontos = 0;
            break;
        case 3:
            qtd_buracos = 25;
            qtd_digletts = 4;
            acertos_consecutivos = 0;
            pontos = 0;
            audio_troll = 1;
    }

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
                    {
                        if (bonus_pontos_dobrados == 1) pontos += 2;
                        else pontos++;

                        if(pontos > qtd_buracos * 5)
                        {
                            qtd_buracos = (qtd_buracos == 144) ? 144 : pow(sqrt(qtd_buracos) + 1, 2);
                            qtd_digletts = (qtd_digletts == 4)  ?   4 : qtd_digletts + 1;
                        }

                    }
                    hit = pos_clicada;
                    acertou_diglett = 1;
                    erros_consecutivos = 0;
                    Mix_PlayChannel( -1, diglett_sound, 0 );
                    }
                }

            /*Verifica se jogador clicou em buraco sem diglett*/
            if(!acertou_diglett && pos_clicada != -1){
                if(pontos > 0)
                    pontos--;
                    erros_consecutivos++;
            }
            if (acertou_diglett)
            {
                if (acerto_passado) acertos_consecutivos++;
                acerto_passado = 1;
            }
            else
            {
                acerto_passado = 0;
                acertos_consecutivos = 0;
                bonus_pontos_dobrados = -1;
                bonus_desacelera = -1;
                r_bonus1 = g_bonus1 = b_bonus1 = r_bonus2 = g_bonus2 = b_bonus2 = 1;
                tempo_animacao = tempo_default;
            }

            if (acertos_consecutivos == 10)
            {
                bonus_pontos_dobrados = 0;
                r_bonus1 = g_bonus1 = b_bonus1 = 0.6;
            }
            if (acertos_consecutivos == 20)
            {
                bonus_desacelera = 0;
                r_bonus2 = g_bonus2 = b_bonus2 = 0.6;
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

    if (key == 82 || key == 114)
    {
        pontos = 0;
        erros_consecutivos = 0;
        acertos_consecutivos = 0;
        tempo_animacao = tempo_default;
        Desenha();
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

void TeclasEspeciais(unsigned char key, int x, int y)
{
    if (key == GLUT_KEY_F1)
    {
        if (bonus_pontos_dobrados == 0)
        {
            bonus_pontos_dobrados = 1;
            r_bonus1 = g_bonus1 = b_bonus1 = 1;
            acertos_consecutivos -= 10;
            if (acertos_consecutivos < 10) r_bonus1 = g_bonus1 = b_bonus1 = 1;
            if (acertos_consecutivos < 20) r_bonus2 = g_bonus2 = b_bonus2 = 1;
        }
    }

    if (key == GLUT_KEY_F2)
    {
        if (bonus_desacelera == 0)
        {
            bonus_desacelera = 1;
            r_bonus2 = g_bonus2 = b_bonus2 = 1;
            tempo_animacao = novo_tempo;
            acertos_consecutivos -= 20;
            if (acertos_consecutivos < 10) r_bonus1 = g_bonus1 = b_bonus1 = 1;
            if (acertos_consecutivos < 20) r_bonus2 = g_bonus2 = b_bonus2 = 1;
        }
    }
    glutPostRedisplay();
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
