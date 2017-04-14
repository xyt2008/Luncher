#include "DownThread.h"

DownThread::DownThread(QTcpSocket* socket, QObject *parent/* = 0*/)
	: QThread(parent)
{
	m_strFilePath.clear();
	m_Socket.setSocket(socket);
	connect(&m_Socket, SIGNAL(signalError(QTcpSocket::SocketError)), this, SLOT(slotError(QTcpSocket::SocketError)));
	connect(&m_Socket, SIGNAL(signalMessage(const QString&)), this, SLOT(slotMessage(const QString&)));
}

DownThread::~DownThread()
{

}

void DownThread::setDownloadFile(const QString& filePath)
{
	m_strFilePath = filePath;
}

void DownThread::run()
{
	if (!m_strFilePath.isEmpty())
	{
		m_Socket.getFile(m_strFilePath);
		ConnState state = Conn_Read;
		while(state == m_Socket.getState())
		{
			continue;
		}
	}
}

void DownThread::slotError(QTcpSocket::SocketError socketError)
{

}

void DownThread::slotMessage(const QString& strMsg)
{

}
