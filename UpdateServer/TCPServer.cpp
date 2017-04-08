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
	ui.textEdit->append(QString::fromLocal8Bit("新接入客户端：%1 名称：%2 端口号：%3").arg(addr.toString()).arg(pSocket->peerName()).arg(pSocket->peerPort()));
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
