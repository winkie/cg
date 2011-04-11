#include <QColor>
#include <cmath>
#include <QGLContext>
//#include <QDebug>

#include "lab1.h"

struct Point2  // screen pont
{
    Point2() : x(0), y(0) {};
    Point2(int _x, int _y) : x(_x), y(_y) {};

    int x, y;
};

double f(double x, double y)
{
    double r = x * x + y * y;
    if (r < 1e-9)
        return 1;
    return cos(x * y / sqrt(r));
}

static int gH;
static int gW;

static void putpixel(int x, int y, QRgb c)
{
    glBegin(GL_POINTS);
    glColor3f(qRed(c) / 255.0f, qGreen(c) / 255.0f, qBlue(c) / 255.0f);
    glVertex2i(x, y);
    glEnd();
}

#include <vector>
#define NO_VALUE 7777
static std::vector<int> YMax(2000, NO_VALUE);
static std::vector<int> YMin(2000, NO_VALUE);
static QRgb UpColor = qRgb(208, 50, 208);
int DownColor = qRgb(0, 0, 0);

void DrawLine(const Point2 &pp1, const Point2 &pp2, bool fake = false,
              bool with_horizont = true, QRgb color = qRgb(255, 255, 255) )
{
    Point2 p1 = pp1, p2 = pp2;

    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = p2.x >= p1.x ? 1 : -1;
    int sy = p2.y >= p1.y ? 1 : -1;

    double err = dx - dy, e2;
    int x0 = p1.x, y0 = p1.y;
    bool stepped = false;

    while(true)
    {
        if (x0 >= 0 && x0 < gW)
        {
            if (!with_horizont)
                putpixel(x0, y0, color);
            else
            {
                if (YMin[x0] == NO_VALUE)
                {
                    if (!fake) putpixel(x0, y0, UpColor);
                    YMin[x0] = YMax[x0] = y0;
                }
                if (dx >= dy)
                {
                    if (y0 > YMax[x0])
                    {
                        if (!fake) putpixel(x0, y0, UpColor);
                            YMax[x0] = y0;
                    }
                    else if (y0 < YMin[x0])
                    {
                        if (!fake) putpixel(x0, y0, DownColor);
                            YMin[x0] = y0;
                    }
                }
                else
                {
                    if (y0 > YMax[x0])
                        if (!fake) putpixel(x0, y0, UpColor);

                    if (y0 < YMin[x0])
                        if (!fake) putpixel(x0, y0, DownColor);

                    if (stepped)
                    {
                        if (x0 - sx >= 0 && x0 - sx < gW)
                        {
                            if (y0 > YMax[x0 - sx])
                                YMax[x0 - sx] = y0;
                            else if (y0 < YMin[x0 - sx])
                                YMin[x0 - sx] = y0;
                        }
                        stepped = false;
                    }
                }
            }
        }
        
        if (x0 == p2.x && y0 == p2.y) break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err = err - dy;
            x0 = x0 + sx;
            stepped = true;
        }
        if (e2 < dx)
        {
            err = err + dx;
            y0 = y0 + sy;
        }
    }
}

void PlotSurface(double x1, double y1, double x2, double y2,
                 double (*f)(double, double),
                 double step,
                 double aPhi, double aPsi, eMode aM,
                 int w, int h,
                 double zoom,
                 bool center,
                 bool fake)
{
    gH = h;
    gW = w;
    Point2 *CurLine;
    double phi = aPhi*3.1415926/180;
    double psi = aPsi*3.1415926/180;
    double sphi = sin ( phi );
    double cphi = cos ( phi );
    double spsi = sin ( psi );
    double cpsi = cos ( psi );
    double e1[] = {cphi, sphi, 0};
    double e2[] = {sphi * spsi, -cphi * spsi, cpsi};
    double e3[] = {sphi * cpsi, -cphi * cpsi, -spsi};
    double x, y;

    double vu[4][1] = {
        {x1 * e3[0] + y1 * e3[1]},
        {x2 * e3[0] + y1 * e3[1]},
        {x2 * e3[0] + y2 * e3[1]},
        {x1 * e3[0] + y2 * e3[1]}
    };

    int y_min_ind = 0;
    for (int i = 1; i < 4; i++)
        if (vu[i][0] < vu[y_min_ind][0])
            y_min_ind = i;
    //int y_min_ind2 = (y_min_ind + 1) % 4;
    //for (int i = 0; i < 4; i++)
    //    if (i != y_min_ind && vu[i][0] < vu[y_min_ind2][0])
    //        y_min_ind2 = i;

    //qDebug() << "Min: " << y_min_ind;

    if (y_min_ind == 1)
    {
        std::swap(x1, x2);
    }
    else if (y_min_ind == 2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    else if (y_min_ind == 3)
    {
        std::swap(y1, y2);
    }

    int n1 = static_cast<int>(fabs(x2 - x1) / step);
    double hx = (x2 - x1) / (n1 - 1);
    int n2 = static_cast<int>(fabs(y2 - y1) / step);
    double hy = (y2 - y1) / (n2 - 1);

    int i, j;

    double ax = w >> 1; // - (w - 30) * xmin / (xmax - xmin);
    double bx = zoom; //(w - 30) / (xmax - xmin);
    double ay = h >> 1; // - ((h - 20) >> 1) * ymin / (ymax - ymin);
    double by = zoom; //((h - 20) >> 1) / (ymax - ymin);


    YMin.assign(w, NO_VALUE);
    YMax.assign(w, NO_VALUE);

    DrawLine(Point2(ax, ay), Point2(ax + bx * cphi, ay + by * sphi * spsi), false, false, qRgb(255, 0, 0));
    DrawLine(Point2(ax, ay), Point2(ax + bx * sphi, ay - by * cphi * spsi), false, false, qRgb(0, 255, 0));
    DrawLine(Point2(ax, ay), Point2(ax, ay + by * cpsi), false, false, qRgb(0, 0, 255));

    double xC = 0, yC = 0;
    if (center)
    {
        xC = (x1 + x2) / 2;
        yC = (y1 + y2) / 2;
    }

#define PROJ_X(x, y) (int)(ax + bx * ((x) * e1[0] + (y) * e1[1]))
#define PROJ_Y(x, y, add) (int)(ay + by * ((x) * e2[0] + (y) * e2[1] + (add)))

    if (aM == LINE_Y)
    {
        CurLine = new Point2[n1];
        Point2 prev1, prev2;
        for (i = 0; i < n2; i++)
        {
            for (j = 0; j < n1; j++)
            {
                x = x1 + j * hx;
                y = y1 + i * hy;
                CurLine[j].x = PROJ_X(x - xC, y - yC);
                CurLine[j].y = PROJ_Y(x - xC, y - yC, f(x, y) * e2[2]);
            }

            if (i > 0 && fake)
            {
                DrawLine(CurLine[0], prev1, true);
                //DrawLine(CurLine[n1 - 1], prev2, true);
            }

            for (j = 0; j < n1 - 1; j++)
                DrawLine(CurLine[j], CurLine[j + 1]);

            prev1 = CurLine[0];
            prev2 = CurLine[n1 - 1];
        }
    }
    else if (aM == LINE_X)
    {
        CurLine = new Point2[n2];
        Point2 prev1, prev2;
        for (i = 0; i < n1; i++)
        {
            for (j = 0; j < n2; j++)
            {
                x = x1 + i * hx;
                y = y1 + j * hy;
                CurLine[j].x = PROJ_X(x - xC, y - yC);
                CurLine[j].y = PROJ_Y(x - xC, y - yC, f(x, y) * e2[2]);
            }

            if (i > 0 && fake)
            {
                DrawLine(CurLine[0], prev1, true);
                //DrawLine(CurLine[n2 - 1], prev2, true);
            }

            for (j = 0; j < n2 - 1; j++)
                DrawLine(CurLine[j], CurLine[j + 1]);

            prev1 = CurLine[0];
            prev2 = CurLine[n2 - 1];
        }
    }
    else if (aM == LINE_XY)
    {
        if ((aPhi >= 0 && aPhi <= 45) || (aPhi >= 135 && aPhi <= 225) || (aPhi >= 315))
        {
            CurLine = new Point2[n1];
            Point2 *NextLine = new Point2[n1];

            for (i = 0; i < n1; i++)
            {
                x = x1 + i * hx;
                y = y1;
                CurLine[i].x = PROJ_X(x - xC, y - yC);
                CurLine[i].y = PROJ_Y(x - xC, y - yC, f(x, y) * e2[2]);
            }
            for (i = 1; i < n2 + 1; i++)
            {
                for (j = 0; j < n1 - 1; j++)
                    DrawLine(CurLine[j], CurLine[j + 1]);
                if (i != n2)
                    for (j = 0; j < n1; j++)
                    {
                        x = x1 + j * hx;
                        y = y1 + i * hy;
                        NextLine[j].x = PROJ_X(x - xC, y - yC);
                        NextLine[j].y = PROJ_Y(x - xC, y - yC, f(x, y) * e2[2]);
                        DrawLine(CurLine[j], NextLine[j]);
                        CurLine[j] = NextLine[j];
                    }
            }
            delete[] NextLine;
        }
        else
        {
            CurLine = new Point2[n2];
            Point2 *NextLine = new Point2[n2];

            for (i = 0; i < n2; i++)
            {
                x = x1;
                y = y1 + i * hy;
                CurLine[i].x = PROJ_X(x - xC, y - yC);
                CurLine[i].y = PROJ_Y(x - xC, y - yC, f(x, y) * e2[2]);
            }
            for (i = 1; i < n1 + 1; i++)
            {
                for (j = 0; j < n2 - 1; j++)
                    DrawLine(CurLine[j], CurLine[j + 1]);
                if (i != n1)
                    for (j = 0; j < n2; j++)
                    {
                        x = x1 + i * hx;
                        y = y1 + j * hy;
                        NextLine[j].x = PROJ_X(x - xC, y - yC);
                        NextLine[j].y = PROJ_Y(x - xC, y - yC, f(x, y) * e2[2]);
                        DrawLine(CurLine[j], NextLine[j]);
                        CurLine[j] = NextLine[j];
                    }
            }
            delete[] NextLine;
        }
    }
    delete[] CurLine;
}
