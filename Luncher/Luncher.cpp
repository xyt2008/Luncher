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
	// 检查更新，下载更新列表文件
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
		QString strVersion = SingleTon<UpdataXml>::ins()->getVersion();

		// 查找名称是否带.temp，若是则修改成正确的
		QString strFile = FileUtils::ins()->getApplicationPath("updatalist.xml");
		if (QFile::exists(strFile + ".temp"))
		{
			QFile::remove(strFile);
			QFile::rename(strFile + ".temp", strFile);
		}
		SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
		QString strVersionNew = SingleTon<UpdataXml>::ins()->getVersion();
	}
}
