/*  	
 *@file   Client.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/29
 *@version V0.1.0
 *@note   �ͻ���ʵ��
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

private slots:
	void slotConnect();
	void slotDisConnect();
	void slotReadRady();
	void slotWritten(qint64 byte);

private:
	void sendFile(const QString& file);
	void dispatchHead(const QByteArray& baData);
	
signals:
	void signalError(QTcpSocket::SocketError socketError);
	void signalMessage(const QString& strMsg);
	void signalFinishedDownloadFile(const QString& strFile);

private:
	QTcpSocket* m_pSocket;
	ConnState m_enState;
	QFile* m_pFileWrite;          // Ҫ���͵��ļ�
	QFile* m_pFileRead;           // Ҫ���յ��ļ�
	qint64 m_iTotalSize;          // �����ܴ�С
	qint64 m_iWrittenSize;        // �Ѿ��������ݴ�С
	qint64 m_iPageSize;           // ÿ�η������ݵĴ�С
	qint64 m_iToWriteSize;        // ��δ�������ݵĴ�С
	QString m_strFileName;        // �����ļ�·��
	QByteArray m_byteArray;       // ���ݻ�����
	qint64 m_iReceiveSize;        // �Ѿ��������ݴ�С
	bool m_bIsHeadMsg;            // �Ƿ��Ѿ���������ͷ��Ϣ
};

#endif // NETCORE_CLIENT_H
