/*  	
 *@file   Luncher.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/08
 *@version V0.1.0
 *@note   客户端程序主窗口
 */
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
