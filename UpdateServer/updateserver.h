/*  	
 *@file   updateserver.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/08
 *@version V0.1.0
 *@note   更新程序服务器主窗口
 */
#ifndef UPDATESERVER_H
#define UPDATESERVER_H

#include <QDialog>
#include <QHostInfo>
#include "ui_updateserver.h"
#include "TCPServer.h"

class UpdateServer : public QDialog
{
	Q_OBJECT

public:
	UpdateServer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~UpdateServer();

	void initFileInfo();

private slots:
	void slotLookHost(const QHostInfo& info);

private:
	Ui::UpdateServerClass ui;
	TCPServer* m_pServer;
};

#endif // UPDATESERVER_H
