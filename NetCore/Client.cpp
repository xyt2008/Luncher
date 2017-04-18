#include "Client.h"
#include <QHostAddress>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "FileUtils.h"

Client::Client(QObject *parent)
	: QObject(parent)
{
	m_iPageSize = 4 * 1024;
	m_iTotalSize = 0;
	m_iWrittenSize = 0;
	m_iToWriteSize = 0;
	m_iReceiveSize = 0;
	m_bIsHeadMsg = false;

	m_strFileName.clear();
	m_pFileWrite = 0;
	m_pFileRead = 0;
	m_pSocket = 0;
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

ConnState Client::getState()
{
	return m_enState;
}

void Client::connectToHost(const QString& addr, int port)
{
	if (m_pSocket == 0 || m_enState == Conn_DisConn)
	{
		setSocket(new QTcpSocket);
	}
	if (!addr.isEmpty())
	{
		m_pSocket->connectToHost(QHostAddress(addr), port);
	}
}

void Client::slotConnect()
{
	m_enState = Conn_Conn;
}

void Client::slotDisConnect()
{
	m_enState = Conn_DisConn;
	m_pSocket->close();
	emit signalMessage(QString::fromLocal8Bit("客户端断开"));
	m_pSocket->deleteLater();
	m_pSocket == 0;
}

void Client::slotReadRady()
{
	QByteArray baData = m_pSocket->readAll();
	if (!m_bIsHeadMsg)
	{
		dispatchHead(baData);
	}
	else
	{
		if (m_iTotalSize > 0)
		{
			qint64 count = m_pFileRead->write(baData);
			m_iReceiveSize += count;
			emit signalReceiveSize(count);

			if (m_iReceiveSize >= m_iTotalSize)
			{
				downLoadFinished();
			}
		}
	}
}

void Client::slotWritten(qint64 byte)
{
	// 已经发送数据的大小
	m_iWrittenSize += (int)byte;

	if (m_iTotalSize > 0)
	{
		if(m_iToWriteSize > 0)
		{
			// 每次发送m_iPageSize大小的数据，这里设置为8KB，如果剩余的数据不足8KB，
			// 发送完一次数据后还剩余数据的大小
			m_iToWriteSize -= (int)m_pSocket->write(m_pFileWrite->read(qMin(m_iToWriteSize, m_iPageSize)));
		}

		if(m_iWrittenSize >= m_iTotalSize)
		{
			//发送完毕
			m_iTotalSize = 0;
			m_iWrittenSize = 0;
			m_iToWriteSize = 0;
			m_pFileWrite->close();
			m_pFileWrite = 0;

			m_enState = Conn_End;
		}
	}
}

void Client::sendFile(const QString& file)
{
	if (m_pFileWrite == 0)
	{
		m_pFileWrite = new QFile();
	}
	m_pFileWrite->setFileName(FileUtils::ins()->getScenePath(file));
	if(!m_pFileWrite->open(QFile::ReadOnly))
	{
		return;
	}

	// 文件总大小
	m_iTotalSize = m_pFileWrite->size();
	m_iToWriteSize = m_iTotalSize;

	/*
	 数据头数据信息，格式：
	 Push:File
	 Value:xxxx.txt
	 ContentLength:12345456
	 */
	QString strContent = QString("%1:%2\r\n"
								"%3:%4\r\n"
								"%5:%6\r\n"
								"\r\n")
								.arg(QString(g_strPush)).arg(QString(g_strFile))
								.arg(QString(g_strValue)).arg(file)
								.arg(QString(g_strLength)).arg(QString::number(m_iTotalSize));

	m_pSocket->write(strContent.toLocal8Bit().data());

	m_enState = Conn_Write;
}

void Client::getFile(const QString& file)
{
	/*
	 数据头数据信息，格式：
	 Pull:File
	 Value:xxxx.txt
	 */
	QString strContent = QString("%1:%2\r\n"
								"%3:%4\r\n"
								"\r\n")
								.arg(QString(g_strPull)).arg(QString(g_strFile))
								.arg(QString(g_strValue)).arg(file);

	int state =  m_pSocket->state();
	qint64 len =  m_pSocket->write(strContent.toLocal8Bit().data());
	m_enState = Conn_Read;
}

void Client::sendData(const QString& data)
{
	if (!data.isEmpty())
	{
		m_pSocket->write(data.toLocal8Bit().data());
	}
}

void Client::dispatchHead(const QByteArray& baData)
{
	m_byteArray.append(baData);
	int nPos = m_byteArray.indexOf("\r\n\r\n");
	if (-1 == nPos)
	{
		return;
	}
	// 取出真正的数据头
	QByteArray head = m_byteArray.left(nPos);

	// 剩余的数据，是需要写入文件的部分
	m_byteArray = m_byteArray.right(m_byteArray.length() - nPos - strlen(g_strEnding) * 2);

	QString strFileName;
	QString strLenght;
	int rPos;

	// 查找命令信息
	nPos = head.indexOf(g_strPush);
	if (-1 != nPos)
	{
		// 上传，即接收
		rPos = head.indexOf(g_strEnding, nPos);
		QString strState = head.mid(nPos + strlen(g_strPush) + 1, rPos - nPos - strlen(g_strPush) - 1);
		if (strState == QString(g_strFile))
		{
			// 接收类型：文件
			nPos = head.indexOf(g_strValue);
			if (-1 != nPos)
			{
				rPos = head.indexOf(g_strEnding, nPos);
				strFileName = head.mid(nPos + strlen(g_strValue) + 1, rPos - nPos - strlen(g_strValue) - 1);
			}
			nPos = head.indexOf(g_strLength);
			if (-1 != nPos)
			{
				rPos = head.indexOf(g_strEnding, nPos);
				strLenght = head.mid(nPos + strlen(g_strLength) + 1, rPos - nPos - strlen(g_strLength) - 1);
			}

			m_iTotalSize = strLenght.toLongLong();
			m_iReceiveSize = 0;

			// 如果<=0则表示没数据可接收
			if (m_iTotalSize > 0)
			{
				QString strFile = FileUtils::ins()->getScenePath(strFileName);
				QFileInfo info(strFile);
				if (!info.exists() && !info.dir().exists())
				{
					info.dir().mkpath(info.absolutePath());
				}

				m_strFileName = strFileName;
				if (m_pFileRead == 0)
				{
					m_pFileRead = new QFile();
				}

				m_pFileRead->setFileName(strFile.append(".temp"));
				m_pFileRead->open(QIODevice::WriteOnly);
				if (!m_byteArray.isEmpty())
				{
					qint64 count = m_pFileRead->write(m_byteArray);
					m_iReceiveSize += count;
					emit signalReceiveSize(count);
					if (m_iReceiveSize >= m_iTotalSize)
					{
						m_bIsHeadMsg = false;
						downLoadFinished();
						return;
					}
				}
			}
		}
		else if (strState == QString(g_strData))
		{
			// 接收类型：数据
		}
	}

	nPos = head.indexOf(g_strPull);
	if (-1 != nPos)
	{
		// 下载，即发送
		rPos = head.indexOf(g_strEnding, nPos);
		QString strState = head.mid(nPos + strlen(g_strPull) + 1, rPos - nPos - strlen(g_strPull) - 1);
		if (strState == QString(g_strFile))
		{
			// 发送类型：文件
			nPos = head.indexOf(g_strValue);
			if (-1 != nPos)
			{
				rPos = head.indexOf(g_strEnding, nPos);
				strFileName = head.mid(nPos + strlen(g_strValue) + 1, rPos - nPos - strlen(g_strValue) - 1);
			}
			
			if (!strFileName.isEmpty())
			{
				sendFile(strFileName);
				m_bIsHeadMsg = false;

				return;
			}
		}
		else if (strState == QString(g_strData))
		{
			// 发送类型：数据
		}
	}

	m_bIsHeadMsg = true;
}

void Client::downLoadFinished()
{
	m_pFileRead->close();
	m_pFileRead = 0;
	m_iTotalSize = 0;
	m_iReceiveSize = 0;

	// 更改文件名称，去掉.temp
	QString strFile = FileUtils::ins()->getScenePath(m_strFileName);
	QFile::remove(strFile);
	QFile::rename(strFile + ".temp", strFile);

	m_enState = Conn_End;

	QString strRet = m_strFileName;
	m_strFileName.clear();
	emit signalFinishedDownloadFile(strRet);
}
