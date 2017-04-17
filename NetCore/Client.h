/*  	
 *@file   Client.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/29
 *@version V0.1.0
 *@note   客户端实例
 */
#ifndef NETCORE_CLIENT_H
#define NETCORE_CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Export.h"
#include "Global.h"

class QFile;

class NETCORE_EXPORT Client : public QObject
{
	Q_OBJECT

public:
	Client(QObject *parent = 0);
	~Client();

	void setSocket(QTcpSocket* socket);
	ConnState getState();

	void connectToHost(const QString& addr, int port);
	void sendFile(const QString& file);
	void getFile(const QString& file);
	void sendData(const QString& data);

private slots:
	void slotConnect();
	void slotDisConnect();
	void slotReadRady();
	void slotWritten(qint64 byte);

private:
	void dispatchHead(const QByteArray& baData);
	void downLoadFinished();
	
signals:
	void signalError(QTcpSocket::SocketError socketError);
	void signalMessage(const QString& strMsg);
	void signalReceiveSize(qint64 size);
	void signalFinishedDownloadFile(const QString& strFile);

private:
	QTcpSocket* m_pSocket;
	ConnState m_enState;
	QFile* m_pFileWrite;          // 要发送的文件
	QFile* m_pFileRead;           // 要接收的文件
	qint64 m_iTotalSize;          // 数据总大小
	qint64 m_iWrittenSize;        // 已经发送数据大小
	qint64 m_iPageSize;           // 每次发送数据的大小
	qint64 m_iToWriteSize;        // 尚未发送数据的大小
	QString m_strFileName;        // 下载文件路径
	QByteArray m_byteArray;       // 数据缓冲区
	qint64 m_iReceiveSize;        // 已经接收数据大小
	bool m_bIsHeadMsg;            // 是否已经接收数据头信息
};

#endif // NETCORE_CLIENT_H
