#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat f = QGLFormat::defaultFormat();
    f.setSampleBuffers(true);
    QGLFormat::setDefaultFormat(f);
    if (!QGLFormat::hasOpenGL()) {
        QMessageBox::information(0, "OpenGL samplebuffers",
                                 "This system does not support OpenGL.");
        return 0;
    }


    MainWindow w;
    w.show();
    return a.exec();
}
