/*  	
 *@file   ConnThread.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/28
 *@version 1.0.0
 *@note   新连接的线程
 */
#ifndef CONNTHREAD_H
#define CONNTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "SocketInstant.h"

class ConnThread : public QThread
{
	Q_OBJECT

public:
	ConnThread(QTcpSocket* socket, QObject *parent = 0);
	virtual ~ConnThread();

protected:
	virtual void run();

private slots:
	void slotError(QTcpSocket::SocketError socketError);
	void slotMessage(const QString& strMsg);

signals:
	void signalError(QTcpSocket::SocketError socketError);
	void signalMessage(const QString& strMsg);

private:
	SocketInstant m_Socket;
};

#endif // CONNTHREAD_H
