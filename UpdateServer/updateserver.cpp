#include "updateserver.h"
#include <QNetworkInterface>
#include "NetCore/UpdataXml.h"
#include "NetCore/FileUtils.h"
#include "NetCore/SingleTon.h"
#include "MakeList.h"

UpdateServer::UpdateServer(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	m_pMakeList = 0;
	connect(ui.pushButtonMakeList, SIGNAL(clicked()), this, SLOT(slotMakeList()));

	initServerSocket();
}

UpdateServer::~UpdateServer()
{

}

void UpdateServer::initFileInfo()
{
	SingleTon<UpdataXml>::ins()->praseXmlFile(FileUtils::ins()->getApplicationPath("updatalist.xml"));
}

void UpdateServer::slotMakeList()
{
	if (m_pMakeList == 0)
	{
		m_pMakeList = new MakeList;
	}

	m_pMakeList->show();
}

void UpdateServer::slotLookHost(const QHostInfo& info)
{
	if (!info.addresses().isEmpty())
	{
		foreach(QHostAddress addr, info.addresses())
		{
			ui.textEdit->append(QString::fromLocal8Bit("服务器IP:%1, port:%2")
				.arg(addr.toString())
				.arg(m_pServer->serverPort()));
		}
	}
}

void UpdateServer::initServerSocket()
{
	m_pServer = new TCPServer(ui, this);
	if (!m_pServer->listen(QHostAddress::Any, 24732))
	{
		ui.textEdit->append(QString::fromLocal8Bit("服务器错误"));
		close();
		return;
	}

	QHostInfo::lookupHost(QHostInfo::localHostName(), this, SLOT(slotLookHost(const QHostInfo&)));
	QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address())
		{
			ipAddress = ipAddressesList.at(i).toString();
			break;
		}
	}

	if (ipAddress.isEmpty())
	{
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	}
	ui.textEdit->append(QString::fromLocal8Bit("服务器IP:%1, port:%2").arg(ipAddress).arg(m_pServer->serverPort()));
}
