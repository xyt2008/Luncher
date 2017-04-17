#include "DownLoad.h"
#include "DownThread.h"

DownLoad::DownLoad(QObject *parent)
	: QObject(parent)
{
	m_mapUpdateList.clear();
}

DownLoad::~DownLoad()
{

}

void DownLoad::setDownLoadList(const std::map<QString, FileList>& mapUpdateList)
{
	m_mapUpdateList = mapUpdateList;
}

void DownLoad::start(QString strIp, int port)
{
	int size = m_mapUpdateList.size();
	if (size <= 0)
	{
		return;
	}
	
	m_strIp = strIp;
	m_iPort = port;
	int thredCount = qMin(1, size);
	for (int i = 0; i < thredCount; ++i)
	{
		doThread();
	}
}

void DownLoad::slotFinishedDownFile(const QString& file)
{
	doThread();
}

void DownLoad::doThread()
{
	if (m_mapUpdateList.size() > 0)
	{
		DownThread* pThread = new DownThread(new QTcpSocket);
		pThread->m_Socket.connectToHost(m_strIp, m_iPort);
		connect(&pThread->m_Socket, SIGNAL(signalFinishedDownloadFile(const QString&)), this, SLOT(slotFinishedDownFile(const QString&)));
		connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
		pThread->setDownloadFile(m_mapUpdateList.begin()->first);
		m_mapUpdateList.erase(m_mapUpdateList.begin());
		pThread->start();
	}
}
