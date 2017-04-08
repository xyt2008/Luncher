#include "TCPServer.h"
#include "ConnThread.h"

TCPServer::TCPServer(Ui::UpdateServerClass uiM, QObject *parent)
	: ui(uiM), QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnect()));
}

TCPServer::~TCPServer()
{

}

void TCPServer::slotNewConnect()
{
	QTcpSocket* pSocket = nextPendingConnection();
	QHostAddress addr = pSocket->peerAddress();
	QString str = addr.toString();
	ui.textEdit->append(QString::fromLocal8Bit("�½���ͻ��ˣ�%1 ���ƣ�%2 �˿ںţ�%3").arg(addr.toString()).arg(pSocket->peerName()).arg(pSocket->peerPort()));
	ConnThread* pThread = new ConnThread(pSocket, this);
	connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
	connect(pThread, SIGNAL(signalMessage(const QString&)), this, SLOT(slotMessage(const QString&)));
	pThread->start();
}

void TCPServer::slotError(QTcpSocket::SocketError socketError)
{
	
}

void TCPServer::slotMessage(const QString& strMsg)
{
	ui.textEdit->append(strMsg);
}
