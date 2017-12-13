#include <stdio.h>
#include <graphics.h>

void PlotPoint(int xc, int yc, float x, float y, int c)
{
    putpixel(xc+x,yc+y,c);
    putpixel(xc+y,yc+x,c);
    putpixel(xc+y,yc-x,c);
    putpixel(xc-x,yc+y,c);
    putpixel(xc-x,yc-y,c);
    putpixel(xc-y,yc-x,c);
    putpixel(xc-y,yc+x,c);
    putpixel(xc+x,yc-y,c);
}

void CircleMidPoint(int xc, int yc, int r, int c)
{
    float x1 = 0,
          y1 = r;
    int p = 1 - r;
    PlotPoint(xc, yc, x1, y1, c);

    while (x1 < y1)
    {
        x1++;
        if (p<0) p=p+2*x1+1;
        else p=p+2*x1+1-2*y1;
        PlotPoint(xc, yc, x1, y1, c);
    }

}

int main()
{
    int xc = 300,
        yc = 300,
        r = 100,
        c = 8;

    initwindow(620, 620, "Questao 2");
    CircleMidPoint(xc, yc, r, c);
    getch();
    closegraph();

    return 0;
}
