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
	if (strText == QString::fromLocal8Bit("检查更新"))
	{
		// 检查更新，下载更新列表文件
		m_pClient->getFile("updatalist.xml");
		SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
	}
	else if (strText == QString::fromLocal8Bit("下载"))
	{
		// 开始下载，一次下载5个
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

		// 查找名称是否带.temp，若是则修改成正确的
		QString strFile = FileUtils::ins()->getApplicationPath("updatalist.xml");
		if (QFile::exists(strFile + ".temp"))
		{
			QFile::remove(strFile + ".old");
			QFile::rename(strFile, strFile + ".old");
			QFile::rename(strFile + ".temp", strFile);
		}
		SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
		QString strVersionNew = SingleTon<UpdataXml>::ins()->getVersion();

		// 检查更新
		if (strVersionNew != strVersion)
		{
			// 解析旧文件
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
					// 查找到有同名的文件
					if (iter->second.m_strMd5 == iterOld->second.m_strMd5)
					{
						// 两个文件相同，不用下载了，从列表中删除
						mapOld.erase(iterOld);
						++iter;
						continue;
					}
				}

				m_mapUpdateList.insert(*iter);
				m_iTotalSize += iter->second.m_fSize;
				++iter;
			}

			// 遍历结束，mapOld中剩余的需要删除
			for (iterOld = mapOld.begin(); iterOld != mapOld.end(); ++iterOld)
			{
				QFile::remove(FileUtils::ins()->getScenePath(iterOld->first));
			}

			QString str = QString("0/%2")
				.arg(FileUtils::ins()->getFileSize(m_iTotalSize));
			ui.labelPro->setText(str);

			ui.pushButton->setText(QString::fromLocal8Bit("下载"));
		}
		else
		{
			// 已经最新，不需要更新
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
