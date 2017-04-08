#ifndef LUNCHER_H
#define LUNCHER_H

#include <QtGui/QMainWindow>
#include "ui_Luncher.h"

class Luncher : public QMainWindow
{
	Q_OBJECT

public:
	Luncher(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Luncher();

private:
	Ui::LuncherClass ui;
};

#endif // LUNCHER_H
