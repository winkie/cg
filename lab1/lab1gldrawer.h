#ifndef LAB1GLWIDGET_H_
#define LAB1GLWIDGET_H_

#include <QtOpenGL>
#include <QDebug>

#include "lab1.h"

class Lab1GLDrawer : public QGLWidget
{
    Q_OBJECT

public:
    Lab1GLDrawer(QWidget *parent);
    virtual ~Lab1GLDrawer();

protected:

    int phi, psi;
    void printAngles();

    void keyPressEvent(QKeyEvent *e);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    /*inline void putPixel(const QPoint &p, const QRgb &color)
    {
        glBegin(GL_POINT);
            glColor3f(qRed(color) / 255.0f, qGreen(color) / 255.0f, qBlue(color) / 255.0f);
            glVertex2i(p.x(), p.y());
        glEnd();
    }*/
};

#endif /* LAB1GLWIDGET_H_ */
