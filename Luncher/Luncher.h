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

#include <QDialog>
#include "ui_Luncher.h"

class Client;

class Luncher : public QDialog
{
	Q_OBJECT

public:
	Luncher(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Luncher();

private slots:
	void slotConnectToServer();
	void slotCheckeUpdate();
	void slotFinishedDownFile(const QString& file);

private:
	Ui::LuncherClass ui;
	Client* m_pClient;
};

#endif // LUNCHER_H
