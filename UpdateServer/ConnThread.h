/*  	
 *@file   ConnThread.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/28
 *@version V0.1.0
 *@note   �����ӵ��߳�
 */
#ifndef CONNTHREAD_H
#define CONNTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "NetCore/Client.h"

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
	Client m_Socket;
};

#endif // CONNTHREAD_H
