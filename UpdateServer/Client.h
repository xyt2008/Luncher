/*  	
 *@file   Client.h
 *@brief  brief  description  
 *@author louyk
 *@date   2017/03/29
 *@version 1.0.0
 *@note   ���������յ��Ŀͻ�������
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
	QFile* m_pFile;               // Ҫ���͵��ļ�
	qint64 m_iTotalSize;          // �����ܴ�С
	qint64 m_iWrittenSize;        // �Ѿ��������ݴ�С
	qint64 m_iPageSize;           // ÿ�η������ݵĴ�С
	qint64 m_iToWriteSize;        // ��δ�������ݵĴ�С
	QString m_strFileName;        // �����ļ�·��
	QByteArray m_byteArray;       // ���ݻ�����
	qint64 m_iReceiveSize;        // �Ѿ��������ݴ�С
	bool m_bIsHeadMsg;            // �Ƿ��Ѿ���������ͷ��Ϣ
};

#endif // CLIENT_H
