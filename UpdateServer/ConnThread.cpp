#include "ConnThread.h"

ConnThread::ConnThread(QTcpSocket* socket, QObject *parent)
	: QThread(parent)
{
	m_Socket.setSocket(socket);
	connect(&m_Socket, SIGNAL(signalErrorP(QTcpSocket::SocketError)), this, SLOT(slotError(QTcpSocket::SocketError)));
	connect(&m_Socket, SIGNAL(signalMessageP(const QString&)), this, SLOT(slotMessage(const QString&)));
}

ConnThread::~ConnThread()
{

}

void ConnThread::run()
{
	while(SocketInstant::Conn_DisConn != m_Socket.getState())
	{
		continue;
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
