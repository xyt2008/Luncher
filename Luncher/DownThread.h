/*  	
 *@file   DownThread.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/04/14
 *@version V0.1.0
 *@note   下载文件线程
 */
#ifndef DOWNTHREAD_H
#define DOWNTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "NetCore/Client.h"

class DownThread : public QThread
{
	Q_OBJECT

public:
	DownThread(QTcpSocket* socket, QObject *parent = 0);
	virtual ~DownThread();

	void setDownLoadList(const std::map<QString, FileList>& mapUpdateList);

protected:
	virtual void run();

private slots:
	void slotError(QTcpSocket::SocketError socketError);
	void slotMessage(const QString& strMsg);
	void slotFinishedDownFile(const QString& file);

signals:
	void signalError(QTcpSocket::SocketError socketError);
	void signalMessage(const QString& strMsg);

public:
	Client m_Socket;
	bool m_bIsFinished;
	std::map<QString, FileList> m_mapUpdateList;
};

#endif // DOWNTHREAD_H
