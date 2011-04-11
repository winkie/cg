#ifndef LAB1_H
#define LAB1_H

enum eMode
{
    LINE_X,
    LINE_Y,
    LINE_XY
};

void PlotSurface ( double x1, double y1, double x2, double y2,
                   double (*f)( double, double ),
                   double step,
                   double aPhi, double aPsi, eMode aM,
                   int w, int h,
                   double zoom,
                   bool center,
                   bool fake);

double f(double, double);
#endif // LAB1_H
