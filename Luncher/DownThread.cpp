#include "DownThread.h"

DownThread::DownThread(QTcpSocket* socket, QObject *parent/* = 0*/)
	: QThread(parent)
{
	m_Socket.setSocket(socket);
	m_bIsFinished = false;
	connect(&m_Socket, SIGNAL(signalError(QTcpSocket::SocketError)), this, SLOT(slotError(QTcpSocket::SocketError)));
	connect(&m_Socket, SIGNAL(signalMessage(const QString&)), this, SLOT(slotMessage(const QString&)));
	connect(&m_Socket, SIGNAL(signalFinishedDownloadFile(const QString&)), this, SLOT(slotFinishedDownFile(const QString&)));
}

DownThread::~DownThread()
{

}

void DownThread::setDownLoadList(const std::map<QString, FileList>& mapUpdateList)
{
	m_mapUpdateList = mapUpdateList;
}

void DownThread::run()
{
	std::map<QString, FileList>::iterator iter = m_mapUpdateList.begin();
	while(iter != m_mapUpdateList.end())
	{
		m_bIsFinished = false;
		m_Socket.getFile(iter->first);
		ConnState state = Conn_End;
		while(true)
		{
			if (m_Socket.getState() == state && m_bIsFinished)
			{
				break;
			}
		}
		++iter;
	}
}

void DownThread::slotError(QTcpSocket::SocketError socketError)
{

}

void DownThread::slotMessage(const QString& strMsg)
{

}

void DownThread::slotFinishedDownFile(const QString& file)
{
	m_bIsFinished = true;
}
