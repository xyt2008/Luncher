#include "Luncher.h"
#include <QTcpSocket>
#include <QFile>
#include "NetCore/Client.h"
#include "NetCore/UpdataXml.h"
#include "NetCore/SingleTon.h"
#include "NetCore/FileUtils.h"
#include "DownLoad.h"
#include "DownThread.h"

Luncher::Luncher(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	m_pDownLoad = 0;
	m_pClient = new Client;
	m_pClient->setSocket(new QTcpSocket);

	m_mapUpdateList.clear();
	m_iReciveSize = 0;
	m_iTotalSize = 0;

	connect(m_pClient, SIGNAL(signalFinishedDownloadFile(const QString&)), this, SLOT(slotFinishedDownFile(const QString&)));
	connect(ui.pushButtonConn, SIGNAL(clicked()), this, SLOT(slotConnectToServer()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotCheckeUpdate()));
}

Luncher::~Luncher()
{

}

void Luncher::slotConnectToServer()
{
	QString strIp = ui.lineEditIp->text();
	int port = ui.lineEditPort->text().toInt();
	m_pClient->connectToHost(strIp, port);
}

void Luncher::slotCheckeUpdate()
{
	QString strText = ui.pushButton->text();
	if (strText == QString::fromLocal8Bit("������"))
	{
		// �����£����ظ����б��ļ�
		m_pClient->getFile("updatalist.xml");
		SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
	}
	else if (strText == QString::fromLocal8Bit("����"))
	{
		// ��ʼ���أ�һ������5��
		if (m_mapUpdateList.size() > 0)
		{
			DownThread* pThread = new DownThread(new QTcpSocket);
			pThread->m_Socket.connectToHost(ui.lineEditIp->text(), ui.lineEditPort->text().toInt());
			connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
			pThread->setDownLoadList(m_mapUpdateList);
			pThread->start();
		}
	}
}

void Luncher::slotFinishedDownFile(const QString& file)
{
	if (file.isEmpty())
	{
		return;
	}

	if (file == QString("updatalist.xml"))
	{
		m_iReciveSize = 0;
		m_iTotalSize = 0;

		QString strVersion = SingleTon<UpdataXml>::ins()->getVersion();

		// ���������Ƿ��.temp���������޸ĳ���ȷ��
		QString strFile = FileUtils::ins()->getApplicationPath("updatalist.xml");
		if (QFile::exists(strFile + ".temp"))
		{
			QFile::remove(strFile + ".old");
			QFile::rename(strFile, strFile + ".old");
			QFile::rename(strFile + ".temp", strFile);
		}
		SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
		QString strVersionNew = SingleTon<UpdataXml>::ins()->getVersion();

		// ������
		if (strVersionNew != strVersion)
		{
			// �������ļ�
			UpdataXml xml;
			m_mapUpdateList.clear();
			xml.praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml.old"));
			std::map<QString, FileList> mapOld =  xml.getFileLists();
			std::map<QString, FileList> mapNew =  SingleTon<UpdataXml>::ins()->getFileLists();
			std::map<QString, FileList>::iterator iter = mapNew.begin();
			std::map<QString, FileList>::iterator iterOld;
			while(iter != mapNew.end())
			{
				iterOld = mapOld.find(iter->first);
				if (iterOld != mapOld.end())
				{
					// ���ҵ���ͬ�����ļ�
					if (iter->second.m_strMd5 == iterOld->second.m_strMd5)
					{
						// �����ļ���ͬ�����������ˣ����б���ɾ��
						mapOld.erase(iterOld);
						++iter;
						continue;
					}
				}

				m_mapUpdateList.insert(*iter);
				m_iTotalSize += iter->second.m_fSize;
				++iter;
			}

			// ����������mapOld��ʣ�����Ҫɾ��
			for (iterOld = mapOld.begin(); iterOld != mapOld.end(); ++iterOld)
			{
				QFile::remove(FileUtils::ins()->getScenePath(iterOld->first));
			}

			QString str = QString("0/%2")
				.arg(FileUtils::ins()->getFileSize(m_iTotalSize));
			ui.labelPro->setText(str);

			ui.pushButton->setText(QString::fromLocal8Bit("����"));
		}
		else
		{
			// �Ѿ����£�����Ҫ����
		}
	}
	else
	{

	}
}

void Luncher::slotReceiveSize(qint64 size)
{
	m_iReciveSize += size;
}

void Luncher::downloadFile(int count)
{
}
