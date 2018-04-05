#ifndef BURACOS_H_INCLUDED
#define BURACOS_H_INCLUDED
#include "ConfigGerais.h"

void salvaPosicao(GLfloat pos_x, GLfloat pos_y, GLfloat larg_buraco, GLfloat alt_buraco, int ctr);
void CalculaBuracos();
int buracoAcertado(GLfloat x, GLfloat y);

#endif // BURACOS_H_INCLUDED
