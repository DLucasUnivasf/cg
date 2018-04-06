#include "Buracos.c"
#include "Digletts.c"
#include "ConfigGerais.c"
#include "Desenhos.c"

int main(int argc, char* argv[])
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(largura, altura);
    glutCreateWindow("Diglett WAR! Computacao Grafica - Daniel e Daniele");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(TeclasEspeciais);

    glutPassiveMotionFunc(PosicaoMouse);
    glutMouseFunc(GerenciaMouse);
    glutTimerFunc(500, AnimaDigletts, 2);

    Inicializa(esq, dirg, base, cimag);

    glutMainLoop();

    return 0;
}
