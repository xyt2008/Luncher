#include "Luncher.h"
#include <QTcpSocket>
#include <QFile>
#include "NetCore/Client.h"
#include "NetCore/UpdataXml.h"
#include "NetCore/SingleTon.h"
#include "NetCore/FileUtils.h"

Luncher::Luncher(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

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
	// �����£����ظ����б��ļ�
	m_pClient->getFile("updatalist.xml");
	SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
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
						mapNew.erase(iter++);
						continue;
					}
				}

				m_mapUpdateList.insert(*iter);
				m_iTotalSize += iter->second.m_fSize;
				mapNew.erase(iter++);
			}

			// ����������mapNew��ʣ�����Ҫ���أ�mapOld��ʣ�����Ҫɾ��
			for (iter = mapOld.begin(); iter != mapNew.end(); ++iter)
			{
				m_mapUpdateList.insert(*iter);
				m_iTotalSize += iter->second.m_fSize;
			}

			for (iterOld = mapOld.begin(); iterOld != mapOld.end(); ++iterOld)
			{
				QFile::remove(FileUtils::ins()->getScenePath(iterOld->first));
			}

			QString str = QString("%1/%2").arg(QString::number(m_iReciveSize))
				.arg(QString::number(m_iTotalSize));
			ui.labelPro->setText(str);

			// ��ʼ���أ�һ������5��
			downloadFile(5);
		}
		else
		{
			// �Ѿ����£�����Ҫ����
		}
	}
}

void Luncher::slotReceiveSize(qint64 size)
{
	m_iReciveSize += size;
}

void Luncher::downloadFile(int count)
{
	int thredCount = count > m_mapUpdateList.size() ? m_mapUpdateList.size() : count;
	for (int i = 0; i < thredCount; ++i)
	{
	}
}
