/*  	
 *@file   Client.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/29
 *@version 1.0.0
 *@note   服务器接收到的客户机交互
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QFile>

class Client : public QObject
{
	Q_OBJECT

public:
	Client(QObject *parent = 0);
	~Client();

	enum ConnState{
		Conn_Init,
		Conn_Read,
		Conn_Write,
		Conn_Conn,
		Conn_DisConn,
		Conn_End
	};

	void setSocket(QTcpSocket* socket);
	ConnState getState();

private slots:
	void slotConnect();
	void slotDisConnect();
	void slotReadRady();
	void slotWritten(qint64 byte);

private:
	void sendFile(const QString& file);
	void dispatchHead(const QByteArray& baData);
	
signals:
	void signalErrorP(QTcpSocket::SocketError socketError);
	void signalMessageP(const QString& strMsg);

private:
	QTcpSocket* m_pSocket;
	ConnState m_enState;
	QFile* m_pFile;               // 要发送的文件
	qint64 m_iTotalSize;          // 数据总大小
	qint64 m_iWrittenSize;        // 已经发送数据大小
	qint64 m_iPageSize;           // 每次发送数据的大小
	qint64 m_iToWriteSize;        // 尚未发送数据的大小
	QString m_strFileName;        // 保存文件路径
	QByteArray m_byteArray;       // 数据缓冲区
	qint64 m_iReceiveSize;        // 已经接收数据大小
	bool m_bIsHeadMsg;            // 是否已经接收数据头信息
};

#endif // CLIENT_H
