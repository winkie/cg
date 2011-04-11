#ifndef LAB1WIDGET_H_
#define LAB1WIDGET_H_

#include <QtGui/QWidget>
#include "ui_lab1.h"

class Lab1Widget : public QWidget
{
	Q_OBJECT

public:
	Lab1Widget(QWidget *parent);
	virtual ~Lab1Widget();
        Ui::Lab1 *ui;
};

#endif /* LAB1WIDGET_H_ */
