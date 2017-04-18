#include "ConnThread.h"
#include "NetCore/Global.h"

ConnThread::ConnThread(QTcpSocket* socket, QObject *parent)
	: QThread(parent)
{
	m_Socket.setSocket(socket);
	connect(&m_Socket, SIGNAL(signalError(QTcpSocket::SocketError)), this, SLOT(slotError(QTcpSocket::SocketError)));
	connect(&m_Socket, SIGNAL(signalMessage(const QString&)), this, SLOT(slotMessage(const QString&)));
}

ConnThread::~ConnThread()
{

}

void ConnThread::run()
{
	ConnState state;
	while(true)
	{
		state = m_Socket.getState();
		if (Conn_DisConn == state)
		{
			break;
		}
		else
		{
			continue;
		}
	}
}

void ConnThread::slotError(QTcpSocket::SocketError socketError)
{
	emit signalError(socketError);
}

void ConnThread::slotMessage(const QString& strMsg)
{
	emit signalMessage(strMsg);
}
