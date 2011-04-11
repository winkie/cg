#include "lab1widget.h"

Lab1Widget::Lab1Widget(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::Lab1();
    ui->setupUi(this);
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), ui->widget, SLOT(updateGL()));
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), ui->widget, SLOT(updateGL()));
    connect(ui->doubleSpinBox_1, SIGNAL(valueChanged(double)), ui->widget, SLOT(updateGL()));
    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)), ui->widget, SLOT(updateGL()));
    connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)), ui->widget, SLOT(updateGL()));
    connect(ui->doubleSpinBox_7, SIGNAL(valueChanged(double)), ui->widget, SLOT(updateGL()));

    connect(ui->doubleSpinBox_4, SIGNAL(valueChanged(double)), ui->widget, SLOT(updateGL()));
    connect(ui->checkBox, SIGNAL(clicked()), ui->widget, SLOT(updateGL()));
    connect(ui->checkBox_2, SIGNAL(clicked()), ui->widget, SLOT(updateGL()));
}

Lab1Widget::~Lab1Widget()
{
}
