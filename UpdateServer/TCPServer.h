/*  	
 *@file   TCPServer.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/28
 *@version 1.0.0
 *@note   服务器TCP入口
 */
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTCPServer>
#include <QTcpSocket>
#include "ui_updateserver.h"

class TCPServer : public QTcpServer
{
	Q_OBJECT

public:
	TCPServer(Ui::UpdateServerClass uiM, QObject *parent);
	virtual ~TCPServer();

private slots:
	void slotNewConnect();
	void slotError(QTcpSocket::SocketError socketError);
	void slotMessage(const QString& strMsg);

private:
	Ui::UpdateServerClass ui;
};

#endif // TCPSERVER_H
