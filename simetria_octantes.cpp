#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define NUM_PTS 10

/*                  SIMETRIA DE OCTANTES
                     Daniele Silva Reis
*/


void PlotPoint(int xc, int yc, float *x, float *y, int c)
{
    int i;
    setcolor(c);

    for (i=NUM_PTS-1; i>0; i--)
    {
        line(xc + x[i], yc + y[i], xc + x[i-1], yc + y[i-1]);
        line(xc + y[i], yc + x[i], xc + y[i-1], yc + x[i-1]);
		line(xc + y[i], yc - x[i], xc + y[i-1], yc - x[i-1]);
		line(xc - x[i], yc + y[i], xc - x[i-1], yc + y[i-1]);
		line(xc - x[i], yc - y[i], xc - x[i-1], yc - y[i-1]);
		line(xc - y[i], yc - x[i], xc - y[i-1], yc - x[i-1]);
		line(xc - y[i], yc + x[i], xc - y[i-1], yc + x[i-1]);
        line(xc + x[i], yc - y[i], xc + x[i-1], yc - y[i-1]);
    }
}

void CircleSimple(int xc, int yc, int r,int c)
{
    float x[NUM_PTS], y[NUM_PTS], aux=0;
    float step = M_PI/(4*(NUM_PTS-1));
    int i, x1 = 0, y1 = 0;

    for (i=0; i<NUM_PTS; i++)
    {
        x[i] = x1+r*cos(aux);
        y[i] = y1+r*sin(aux);
        aux = aux + step;
    }
    PlotPoint(xc, yc, x, y, c);
}

int main () {

  int x = 300,
      y = 300,
      r = 100,
      c = 10;

  initwindow(620, 620, "Questao 1");
  CircleSimple(x, y, r, c);
  getch();
  closegraph();

  return 0;
}
