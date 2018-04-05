#include "Digletts.h"

void geradorDeDigletts()
{
    static clock_t ult_chamada_t, cham_atual_t, total_t;

    cham_atual_t = clock();
    total_t = (double)(cham_atual_t - ult_chamada_t) / (CLOCKS_PER_SEC/1000);
    /*Em ms*/

    if(total_t >= tempo_animacao){
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

void AnimaDigletts(int value)
{
    if(!pausa){

        textura_animacao_diglett = value;
        Desenha();
        glFlush();

        if(value == 2){
        geradorDeDigletts();
        glutTimerFunc(tempo_animacao2, AnimaDigletts, 3);
        Mix_PlayChannel( -1, diglett_out_sound, 0 );} //som de saida de digletts
        else
        glutTimerFunc(tempo_animacao2, AnimaDigletts, 2);
    }
}
