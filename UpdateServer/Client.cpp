#include "Client.h"
#include <QHostAddress>

Client::Client(QObject *parent)
	: QObject(parent)
{
	m_iPageSize = 4 * 1024;
	m_iTotalSize = 0;
	m_iWrittenSize = 0;
	m_iToWriteSize = 0;
	m_iReceiveSize = 0;
	m_bIsHeadMsg = false;
}

Client::~Client()
{
	
}

void Client::setSocket(QTcpSocket* socket)
{
	m_pSocket = socket;
	m_enState = Conn_Init;

	connect(m_pSocket, SIGNAL(connected()), this, SLOT(slotConnect()));
	connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(slotReadRady()));
	connect(m_pSocket, SIGNAL(disconnected()), this, SLOT(slotDisConnect()));
	connect(m_pSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(slotWritten(qint64)));
}

Client::ConnState Client::getState()
{
	return m_enState;
}

void Client::slotConnect()
{
	m_enState = Conn_Conn;
}

void Client::slotDisConnect()
{
	m_enState = Conn_DisConn;
	m_pSocket->close();
	emit signalMessageP(QString::fromLocal8Bit("�ͻ��˶Ͽ�"));
	m_pSocket->deleteLater();
}

void Client::slotReadRady()
{
	m_enState = Conn_Read;

	QByteArray baData = m_pSocket->readAll();

	if (!m_bIsHeadMsg)
	{
		dispatchHead(baData);
	}
	else
	{
		m_iReceiveSize += m_pFile->write(baData);
		if (m_iReceiveSize >= m_iTotalSize)
		{
			m_pFile->close();
			m_pFile = 0;
			m_bIsHeadMsg = false;
			QString str = QString::fromLocal8Bit("�������");
		}
	}
}

void Client::slotWritten(qint64 byte)
{
	// �Ѿ��������ݵĴ�С
	m_iWrittenSize += (int)byte;

	if(m_iToWriteSize > 0)
	{
		// ÿ�η���m_iPageSize��С�����ݣ���������Ϊ8KB�����ʣ������ݲ���8KB��
		// �ͷ���ʣ�����ݵĴ�С
		// ������һ�����ݺ�ʣ�����ݵĴ�С
		m_iToWriteSize -= (int)m_pSocket->write(m_pFile->read(qMin(m_iToWriteSize, m_iPageSize)));
	}

	if(m_iWrittenSize == m_iTotalSize) //�������
	{
		m_pFile->close();
		m_pFile = 0;
	}
}

void Client::sendFile(const QString& file)
{
	m_pFile = new QFile(file);
	if(!m_pFile->open(QFile::ReadOnly))
	{
		return;
	}

	// �ļ��ܴ�С
	m_iTotalSize = m_pFile->size();
	m_iToWriteSize = m_iTotalSize;

	QString currentFileName = file.right(file.size() - file.lastIndexOf('/') - 1);

	QString strContent = QString("Command:DownFile\r\nParameter:%1\r\nContentLength:%2\r\n\r\n")
		.arg(file).arg(m_iTotalSize);
	// ������ͷ���ݺ�ʣ�����ݵĴ�С
	m_pSocket->write(strContent.toLocal8Bit().data());
}

void Client::dispatchHead(const QByteArray& baData)
{
	m_byteArray.append(baData);
	int nPos = m_byteArray.indexOf("\r\n\r\n");
	if (-1 == nPos)
	{
		return;
	}
	// ȡ������������ͷ
	QByteArray head = m_byteArray.left(nPos);

	// ʣ������ݣ�����Ҫд���ļ��Ĳ���
	m_byteArray = m_byteArray.right(m_byteArray.length() - nPos - 4);

	QString strCommand;
	QString strParam;
	QString strLenght;
	int rPos;
	// ����������Ϣ
	nPos = head.indexOf("Command");
	if (-1 != nPos)
	{
		rPos = head.indexOf("\r\n", nPos);
		strCommand = head.mid(nPos + 8, rPos - nPos - 8);
	}

	nPos = head.indexOf("Parameter");
	if (-1 != nPos)
	{
		rPos = head.indexOf("\r\n", nPos);
		strParam = head.mid(nPos + 10, rPos - nPos - 10);
	}
	nPos = head.indexOf("ContentLength");
	if (-1 != nPos)
	{
		rPos = head.indexOf("\r\n", nPos);
		strLenght = head.mid(nPos + 14, rPos - nPos - 14);
	}

	m_iTotalSize = strLenght.toLongLong();
	m_iReceiveSize = 0;

	if (m_pFile == 0)
	{
		m_pFile = new QFile(strParam.append(".temp"));
		m_pFile->open(QIODevice::WriteOnly);
		if (!m_byteArray.isEmpty())
		{
			m_iReceiveSize += m_pFile->write(m_byteArray);
		}
	}

	m_bIsHeadMsg = true;
}
