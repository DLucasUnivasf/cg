#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#define NUM_PTS 10

void PlotPoint(int xc, int yc, float *x, float *y, int c, int r)
{
    int i;

    setcolor(c);
    for (i=0; i<NUM_PTS-1; i++)
    {
        line(x[i], y[i], x[i+1], y[i+1]);
        line(y[i], x[i], y[i+1], x[i+1]);
		line(y[i], yc-x[i], y[i+1], yc-x[i+1]);
		line(xc-x[i], yc-y[i], xc-x[i+1], yc-y[i+1]);
		line(xc-y[i], yc-x[i], xc-y[i+1], yc-x[i+1]);
		line(xc-y[i], x[i], xc-y[i+1], x[i+1]);
		line(x[i], yc-y[i], x[i+1], yc-y[i+1]);
    }
}

void CircleSimple(int xc, int yc, int r,int c)
{
    float x[NUM_PTS], y[NUM_PTS], aux=0;
    float step = M_PI/(4*(NUM_PTS-1));
    int i;

    for (i=0; i<NUM_PTS; i++)
    {
        x[i] = xc+r*cos(aux);
        y[i] = yc+r*sin(aux);
        aux = aux + step;
    }
    PlotPoint(xc, yc, x, y, c, r);
}

int main () {

  int x = 300,
      y = 300,
      r = 50,
      c = 10;

  initwindow(620, 620, "Questao 1");
  CircleSimple(x, y, r, c);
  getch();
  closegraph();

  return 0;
}
