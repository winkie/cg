#include <cmath>
#include <vector>
#include <QColor>
#include <QKeyEvent>

#include "lab1gldrawer.h"
#include "lab1widget.h"

Lab1GLDrawer::Lab1GLDrawer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setFocusPolicy(Qt::StrongFocus);
    phi = 15;
    psi = 15;
}

void Lab1GLDrawer::initializeGL()
{
    glClearColor(0.831, 0.815, 0.784, 0.0);
    glDisable(GL_DEPTH_TEST);
}

void Lab1GLDrawer::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //qDebug() << "(w, h) = (" << w << ", " << h << ")";
}

Lab1GLDrawer::~Lab1GLDrawer()
{
}

inline static void rbound(int &v, int l, int r)
{
    v = (v - l) % (r - l) + l;
    if (v < 0)
        v = r + v;
}

inline static void bound(int &v, int l, int r)
{
    if (v < l)
        v = l;
    if (v > r)
        v = r;
}



void Lab1GLDrawer::printAngles()
{
    Lab1Widget *p = static_cast<Lab1Widget*>(parentWidget());
    QString str;
    str.sprintf("Phi: %d", phi);
    p->ui->label->setText(str);
    QString str2;
    str2.sprintf("Psi: %d", psi);
    p->ui->label_2->setText(str2);
}

void Lab1GLDrawer::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Left:
        rbound(phi += 5, 0, 360);
        break;
    case Qt::Key_Right:
        rbound(phi -= 5, 0, 360);
        break;
    case Qt::Key_Up:
        bound(psi += 5, -90, 90);
        break;
    case Qt::Key_Down:
        bound(psi -= 5, -90, 90);
        break;
    }
    updateGL();
}

void Lab1GLDrawer::paintGL()
{
    printAngles();
    glClear(GL_COLOR_BUFFER_BIT);

    Lab1Widget *p = static_cast<Lab1Widget*>(parentWidget());
    int i = p->ui->comboBox->currentIndex();
    eMode mode;
    if (i == 0)
        mode = LINE_X;
    else if (i == 1)
        mode = LINE_Y;
    else
        mode = LINE_XY;

    double step = p->ui->doubleSpinBox->value();

    double x1 = p->ui->doubleSpinBox_1->value();
    double x2 = p->ui->doubleSpinBox_2->value();
    double y1 = p->ui->doubleSpinBox_3->value();
    double y2 = p->ui->doubleSpinBox_7->value();

    bool center = p->ui->checkBox->isChecked();
    double zoom = p->ui->doubleSpinBox_4->value();

    bool fake = p->ui->checkBox_2->isChecked();

    PlotSurface(x1, y1, x2, y2,
                f,
                step,
                phi, psi, mode,
                width(), height(),
                zoom,
                center,
                fake);

}
